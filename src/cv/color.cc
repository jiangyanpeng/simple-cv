#include "cv/c_api.h"
#include <common.h>
namespace cv {

SIMPLE_INLINE void swap_element_u8(uint8_t* data, int index_a, int index_b) {
    uint8_t tmp   = data[index_a];
    data[index_a] = data[index_b];
    data[index_b] = tmp;
}

void convert_rgb_to_bgr_planner(const uint8_t* rgb,
                                uint32_t w,
                                uint32_t h,
                                uint32_t stride,
                                uint8_t* bgr) {
    if (!rgb || !bgr) {
        bgr = nullptr;
        return;
    }

    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

    uint8_t* ptr0 = bgr;
    uint8_t* ptr1 = bgr + w;
    uint8_t* ptr2 = bgr + 2 * w;

    for (int y = 0; y < h; y++) {
#if __ARM_NEON
        int nn     = w >> 3;
        int remain = w - (nn << 3);
#else
        int remain = w;
#endif // __ARM_NEON

#if __ARM_NEON
#if __aarch64__
        for (; nn > 0; nn--) {
            uint8x8x3_t _rgb = vld3_u8(rgb);
            uint16x8_t _r16  = vmovl_u8(_rgb.val[0]);
            uint16x8_t _g16  = vmovl_u8(_rgb.val[1]);
            uint16x8_t _b16  = vmovl_u8(_rgb.val[2]);

            float32x4_t _rlow  = vcvtq_f32_u32(vmovl_u16(vget_low_u16(_r16)));
            float32x4_t _rhigh = vcvtq_f32_u32(vmovl_u16(vget_high_u16(_r16)));
            float32x4_t _glow  = vcvtq_f32_u32(vmovl_u16(vget_low_u16(_g16)));
            float32x4_t _ghigh = vcvtq_f32_u32(vmovl_u16(vget_high_u16(_g16)));
            float32x4_t _blow  = vcvtq_f32_u32(vmovl_u16(vget_low_u16(_b16)));
            float32x4_t _bhigh = vcvtq_f32_u32(vmovl_u16(vget_high_u16(_b16)));

            vst1q_f32(ptr2, _rlow);
            vst1q_f32(ptr2 + 4, _rhigh);
            vst1q_f32(ptr1, _glow);
            vst1q_f32(ptr1 + 4, _ghigh);
            vst1q_f32(ptr0, _blow);
            vst1q_f32(ptr0 + 4, _bhigh);

            rgb += 3 * 8;
            ptr0 += 8;
            ptr1 += 8;
            ptr2 += 8;
        }
#else
        if (nn > 0) {
            asm volatile("0:                             \n"
                         "pld        [%1, #256]          \n"
                         "vld3.u8    {d0-d2}, [%1]!      \n"
                         "vmovl.u8   q8, d0              \n"
                         "vmovl.u8   q9, d1              \n"
                         "vmovl.u8   q10, d2             \n"
                         "vmovl.u16  q0, d16             \n"
                         "vmovl.u16  q1, d17             \n"
                         "vmovl.u16  q2, d18             \n"
                         "vmovl.u16  q3, d19             \n"
                         "vmovl.u16  q8, d20             \n"
                         "vmovl.u16  q9, d21             \n"
                         "vcvt.f32.u32   q0, q0          \n"
                         "vcvt.f32.u32   q1, q1          \n"
                         "vcvt.f32.u32   q2, q2          \n"
                         "vcvt.f32.u32   q3, q3          \n"
                         "vcvt.f32.u32   q8, q8          \n"
                         "subs       %0, #1              \n"
                         "vst1.f32   {d0-d3}, [%4]!      \n"
                         "vcvt.f32.u32   q9, q9          \n"
                         "vst1.f32   {d4-d7}, [%3]!      \n"
                         "vst1.f32   {d16-d19}, [%2]!    \n"
                         "bne        0b                  \n"
                         : "=r"(nn),   // %0
                           "=r"(rgb),  // %1
                           "=r"(ptr0), // %2
                           "=r"(ptr1), // %3
                           "=r"(ptr2)  // %4
                         : "0"(nn), "1"(rgb), "2"(ptr0), "3"(ptr1), "4"(ptr2)
                         : "cc", "memory", "q0", "q1", "q2", "q3", "q8", "q9", "q10");
        }
#endif // __aarch64__

#endif
        for (; remain > 0; remain--) {
            *ptr0 = rgb[2];
            *ptr1 = rgb[1];
            *ptr2 = rgb[0];

            rgb += 3;
            ptr0++;
            ptr1++;
            ptr2++;
        }

        rgb += wgap;
    }
}

void convert_bgr_to_rgb_packed(const uint8_t* src,
                               uint32_t w,
                               uint32_t h,
                               uint32_t stride,
                               uint8_t* dst) {
    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

#if __ARM_NEON
    int nn     = w >> 3;
    int remain = w - (nn << 3);
#elif defined(USE_AVX)
    int nn = w / 32;
    int remain = w - (nn * 32);
#else
    int remain = w;
#endif // __ARM_NEON

    const uint8_t* ptr_cur_src_bgr = src;
    uint8_t* ptr_cur_dst_rgb       = dst;
    for (int y = 0; y < h; y++) {
#ifdef __ARM_NEON
        printf("pass\n");
        remain = w
#elif defined(USE_AVX)
        int8_t mask_1[32] = {2, 1, 0, 5, 4, 3, 8, 7, 6,  11, 10, 9,  14, 13, 12, 15,
                             0, 1, 4, 3, 2, 7, 6, 5, 10, 9,  8,  13, 12, 11, 14, 15};
        int8_t mask_2[32] = {0, 3, 2, 1, 6, 5, 4, 9, 8, 7,  12, 11, 10, 15, 14, 13,
                             2, 1, 0, 5, 4, 3, 8, 7, 6, 11, 10, 9,  14, 13, 12, 15};
        int8_t mask_3[32] = {0, 1, 4, 3, 2, 7, 6, 5, 10, 9, 8,  13, 12, 11, 14, 15,
                             0, 3, 2, 1, 6, 5, 4, 9, 8,  7, 12, 11, 10, 15, 14, 13};
        __m256i vec_mask_1 = _mm256_loadu_si256((__m256i const*)mask_1);
        __m256i vec_mask_2 = _mm256_loadu_si256((__m256i const*)mask_2);
        __m256i vec_mask_3 = _mm256_loadu_si256((__m256i const*)mask_3);
        for (; nn > 0; --nn) {
            __m256i vec_src_1 = _mm256_loadu_si256((__m256i const*)ptr_cur_src_bgr);
            __m256i vec_src_2 = _mm256_loadu_si256((__m256i const*)(ptr_cur_src_bgr + 32));
            __m256i vec_src_3 = _mm256_loadu_si256((__m256i const*)(ptr_cur_src_bgr + 64));

            __m256i vec_dst_1 = _mm256_shuffle_epi8(vec_src_1, vec_mask_1);
            __m256i vec_dst_2 = _mm256_shuffle_epi8(vec_src_2, vec_mask_2);
            __m256i vec_dst_3 = _mm256_shuffle_epi8(vec_src_3, vec_mask_3);

            _mm256_storeu_si256((__m256i*)(ptr_cur_dst_rgb), vec_dst_1);
            _mm256_storeu_si256((__m256i*)(ptr_cur_dst_rgb + 32), vec_dst_2);
            _mm256_storeu_si256((__m256i*)(ptr_cur_dst_rgb + 64), vec_dst_3);

            // Handling boundary data
            swap_element_u8(ptr_cur_dst_rgb, 15, 17);
            swap_element_u8(ptr_cur_dst_rgb, 30, 32);
            swap_element_u8(ptr_cur_dst_rgb, 63, 65);
            swap_element_u8(ptr_cur_dst_rgb, 78, 80);

            ptr_cur_src_bgr += 96;
            ptr_cur_dst_rgb += 96;
        }
#endif
            for (int j = 0; j < remain; j++) {
            uint8_t b00 = ptr_cur_src_bgr[0];
            uint8_t g00 = ptr_cur_src_bgr[1];
            uint8_t r00 = ptr_cur_src_bgr[2];

            ptr_cur_dst_rgb[0] = r00;
            ptr_cur_dst_rgb[1] = g00;
            ptr_cur_dst_rgb[2] = b00;

            ptr_cur_src_bgr += 3;
            ptr_cur_dst_rgb += 3;
        }

        ptr_cur_src_bgr += wgap;
    }
}

void convert_bgr_to_gray_packed(const uint8_t* src,
                                uint32_t w,
                                uint32_t h,
                                uint32_t stride,
                                uint8_t* dst,
                                bool rgb_mode) {
    // coeffs for r g b = 0.299f, 0.587f, 0.114f
    uint8_t Y_shift = 8; // 14
    uint8_t R2Y     = 77;
    uint8_t G2Y     = 150;
    uint8_t B2Y     = 29;
    if (rgb_mode) {
        R2Y = 29;
        B2Y = 77;
    }
    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

#if __ARM_NEON
    int nn     = w >> 3;
    int remain = w - (nn << 3);
#elif defined(USE_AVX)
    int nn = w >> 4;
    int remain = w - (nn << 4);
#else
    int remain = w;
#endif

    const uint8_t* bgr_ptr = src;
    uint8_t* gray_ptr      = dst;
    for (int y = 0; y < h; y++) {
#ifdef __ARM_NENO
#if __aarch64__
        uint8x8_t _R2Y = vdup_n_u8(R2Y);
        uint8x8_t _G2Y = vdup_n_u8(G2Y);
        uint8x8_t _B2Y = vdup_n_u8(B2Y);
        for (; nn > 0; nn--) {
            uint8x8x3_t _rgb = vld3_u8(rgb);

            uint16x8_t _y16 = vmull_u8(_rgb.val[0], _R2Y);
            _y16            = vmlal_u8(_y16, _rgb.val[1], _G2Y);
            _y16            = vmlal_u8(_y16, _rgb.val[2], _B2Y);
            _y16            = vshrq_n_u16(_y16, Y_shift);

            float32x4_t _ylow  = vcvtq_f32_u32(vmovl_u16(vget_low_u16(_y16)));
            float32x4_t _yhigh = vcvtq_f32_u32(vmovl_u16(vget_high_u16(_y16)));

            vst1q_f32(ptr, _ylow);
            vst1q_f32(ptr + 4, _yhigh);

            rgb += 3 * 8;
            ptr += 8;
        }
#else
        if (nn > 0) {
            asm volatile("vdup.u8    d16, %6             \n"
                         "vdup.u8    d17, %7             \n"
                         "vdup.u8    d18, %8             \n"
                         "0:                             \n"
                         "pld        [%1, #256]          \n"
                         "vld3.u8    {d0-d2}, [%1]!      \n"
                         "vmull.u8   q2, d0, d16         \n"
                         "vmlal.u8   q2, d1, d17         \n"
                         "vmlal.u8   q2, d2, d18         \n"
                         "vshr.u16   q2, q2, #8          \n" // Y_shift
                         "vmovl.u16  q0, d4              \n"
                         "vmovl.u16  q1, d5              \n"
                         "vcvt.f32.u32   q0, q0          \n"
                         "vcvt.f32.u32   q1, q1          \n"
                         "subs       %0, #1              \n"
                         "vst1.f32   {d0-d3}, [%2]!      \n"
                         "bne        0b                  \n"
                         : "=r"(nn),  // %0
                           "=r"(rgb), // %1
                           "=r"(ptr)  // %2
                         : "0"(nn),
                           "1"(rgb),
                           "2"(ptr),
                           "r"(R2Y), // %6
                           "r"(G2Y), // %7
                           "r"(B2Y)  // %8
                         : "cc", "memory", "q0", "q1", "q2", "q8", "q9");
        }
#endif // __aarch64__
#elif defined(USE_AVX)
        // set const params
        __m256i vec_b_factor = _mm256_set1_epi16(B2Y);
        __m256i vec_g_factor = _mm256_set1_epi16(G2Y);
        __m256i vec_r_factor = _mm256_set1_epi16(R2Y);
        const __m256i VEC_HALF = _mm256_set1_epi16(128);
        __m256i vec_zero = _mm256_setzero_si256();
        const int SPLIT_MASK = 0b01111000;
        for (; nn > 0; --nn) {
            __m128i vec_b_u8;
            __m128i vec_g_u8;
            __m128i vec_r_u8;
            vld3_u8x16_avx(bgr_ptr, &vec_b_u8, &vec_g_u8, &vec_r_u8);

            __m256i vec_b_u16 = _mm256_cvtepu8_epi16(vec_b_u8);
            __m256i vec_g_u16 = _mm256_cvtepu8_epi16(vec_g_u8);
            __m256i vec_r_u16 = _mm256_cvtepu8_epi16(vec_r_u8);

            __m256i vec_b_product = _mm256_mullo_epi16(vec_b_u16, vec_b_factor);
            __m256i vec_g_product = _mm256_mullo_epi16(vec_g_u16, vec_g_factor);
            __m256i vec_r_product = _mm256_mullo_epi16(vec_r_u16, vec_r_factor);

            __m256i vec_sum =
                _mm256_add_epi16(_mm256_add_epi16(vec_b_product, vec_g_product), vec_r_product);
            __m256i vec_y_u16 = _mm256_srli_epi16(_mm256_add_epi16(vec_sum, VEC_HALF), Y_shift);
            // __m256i vec_y_u16 = _mm256_srli_epi16(vec_sum, Y_shift);

            __m256i vec_blend_u8 = _mm256_packus_epi16(vec_y_u16, vec_zero);
            __m256i vec_split_u8 = _mm256_permute4x64_epi64(vec_blend_u8, SPLIT_MASK);

            // store final results
            _mm_storeu_si128((__m128i*)gray_ptr, _mm256_castsi256_si128(vec_split_u8));

            bgr_ptr += 48;
            gray_ptr += 16;
        }
#endif
        for (; remain > 0; remain--) {
            *gray_ptr =
                (uint8_t)((bgr_ptr[0] * B2Y + bgr_ptr[1] * G2Y + bgr_ptr[2] * R2Y) >> Y_shift);

            bgr_ptr += 3;
            gray_ptr++;
        }

        bgr_ptr += wgap;
    }
}

void convert_package_to_planar_c3(const uint8_t* src,
                                  uint32_t w,
                                  uint32_t h,
                                  uint32_t stride,
                                  uint8_t* dst) {
    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

#if __ARM_NEON
    int nn     = w >> 3;
    int remain = w - (nn << 3);
#elif defined(USE_AVX)
    int nn = w / 32;
    int remain = w - (nn * 32);
#else
    int remain = w;
#endif

    const uint8_t* packed_ptr  = src;
    uint8_t* ptr_cur_dst_pl_c0 = dst;
    uint8_t* ptr_cur_dst_pl_c1 = dst + w;
    uint8_t* ptr_cur_dst_pl_c2 = dst + 2 * w;

    for (int y = 0; y < h; ++y) {
#ifdef __ARM_NENO
        printf("pass\n");
        remain = w
#elif defined(USE_AVX)
        for (; nn > 0; --nn) {
            __m256i vec_b;
            __m256i vec_g;
            __m256i vec_r;
            vld3_u8x32_avx(packed_ptr, &vec_b, &vec_g, &vec_r);
            _mm256_storeu_si256((__m256i*)ptr_cur_dst_pl_c0, vec_b);
            _mm256_storeu_si256((__m256i*)ptr_cur_dst_pl_c1, vec_g);
            _mm256_storeu_si256((__m256i*)ptr_cur_dst_pl_c2, vec_r);
            packed_ptr += 96;
            ptr_cur_dst_pl_c0 += 32;
            ptr_cur_dst_pl_c1 += 32;
            ptr_cur_dst_pl_c2 += 32;
        }
#endif
            for (; remain > 0; --remain) {
            *ptr_cur_dst_pl_c0 = packed_ptr[0];
            *ptr_cur_dst_pl_c1 = packed_ptr[1];
            *ptr_cur_dst_pl_c2 = packed_ptr[2];

            packed_ptr += 3;
            ++ptr_cur_dst_pl_c0;
            ++ptr_cur_dst_pl_c1;
            ++ptr_cur_dst_pl_c2;
        }

        packed_ptr += wgap;
    }
}

void convert_planar_to_package_c3(const uint8_t* src,
                                  uint32_t w,
                                  uint32_t h,
                                  uint32_t stride,
                                  uint8_t* dst) {
    const int wgap = stride - w * 3;
    if (wgap == 0) {
        w = w * h;
        h = 1;
    }

#if __ARM_NEON
    int nn     = w >> 3;
    int remain = w - (nn << 3);
#elif defined(USE_AVX)
    int nn = w / 32;
    int remain = w - (nn * 32);
#else
    int remain = w;
#endif

    const uint8_t* ptr_cur_src_pl_c0 = src;
    const uint8_t* ptr_cur_src_pl_c1 = src + w;
    const uint8_t* ptr_cur_src_pl_c2 = src + 2 * w;
    uint8_t* ptr_cur_dst_packed      = dst;

    for (int y = 0; y < h; ++y) {
#ifdef __ARM_NENO
        printf("pass\n");
        remain = w
#elif defined(USE_AVX)
        for (; nn > 0; --nn) {
            __m256i vec_b = _mm256_loadu_si256((__m256i const*)ptr_cur_src_pl_c0);
            __m256i vec_g = _mm256_loadu_si256((__m256i const*)ptr_cur_src_pl_c1);
            __m256i vec_r = _mm256_loadu_si256((__m256i const*)ptr_cur_src_pl_c2);
            vst3_u8x32_avx(vec_b, vec_g, vec_r, ptr_cur_dst_packed);
            ptr_cur_src_pl_c0 += 32;
            ptr_cur_src_pl_c1 += 32;
            ptr_cur_src_pl_c2 += 32;
            ptr_cur_dst_packed += 96;
        }
#endif
            for (; remain > 0; --remain) {
            ptr_cur_dst_packed[0] = (*ptr_cur_src_pl_c0);
            ptr_cur_dst_packed[1] = (*ptr_cur_src_pl_c1);
            ptr_cur_dst_packed[2] = (*ptr_cur_src_pl_c2);
            ++ptr_cur_src_pl_c0;
            ++ptr_cur_src_pl_c1;
            ++ptr_cur_src_pl_c2;
            ptr_cur_dst_packed += 3;
        }

        src += wgap;
    }
}

void convert_yuv420sp_to_rgb_packed(const uint8_t* yuv420sp, uint32_t w, uint32_t h, uint8_t* rgb) {
    const uint8_t* yptr  = yuv420sp;
    const uint8_t* vuptr = yuv420sp + w * h;

#if __ARM_NEON
    uint8x8_t _v128 = vdup_n_u8(128);
    int8x8_t _v90   = vdup_n_s8(90);
    int8x8_t _v46   = vdup_n_s8(46);
    int8x8_t _v22   = vdup_n_s8(22);
    int8x8_t _v113  = vdup_n_s8(113);
#endif // __ARM_NEON

    for (int y = 0; y < h; y += 2) {
        const uint8_t* yptr0 = yptr;
        const uint8_t* yptr1 = yptr + w;
        uint8_t* rgb0        = rgb;
        uint8_t* rgb1        = rgb + w * 3;

#if __ARM_NEON
        int nn     = w >> 3;
        int remain = w - (nn << 3);
#else
        int remain = w;
#endif // __ARM_NEON

#if __ARM_NEON
#if __aarch64__
        for (; nn > 0; nn--) {
            int16x8_t _yy0 = vreinterpretq_s16_u16(vshll_n_u8(vld1_u8(yptr0), 6));
            int16x8_t _yy1 = vreinterpretq_s16_u16(vshll_n_u8(vld1_u8(yptr1), 6));

            int8x8_t _vvuu       = vreinterpret_s8_u8(vsub_u8(vld1_u8(vuptr), _v128));
            int8x8x2_t _vvvvuuuu = vtrn_s8(_vvuu, _vvuu);
            int8x8_t _vv         = _vvvvuuuu.val[0];
            int8x8_t _uu         = _vvvvuuuu.val[1];

            int16x8_t _r0 = vmlal_s8(_yy0, _vv, _v90);
            int16x8_t _g0 = vmlsl_s8(_yy0, _vv, _v46);
            _g0           = vmlsl_s8(_g0, _uu, _v22);
            int16x8_t _b0 = vmlal_s8(_yy0, _uu, _v113);

            int16x8_t _r1 = vmlal_s8(_yy1, _vv, _v90);
            int16x8_t _g1 = vmlsl_s8(_yy1, _vv, _v46);
            _g1           = vmlsl_s8(_g1, _uu, _v22);
            int16x8_t _b1 = vmlal_s8(_yy1, _uu, _v113);

            uint8x8x3_t _rgb0;
            _rgb0.val[0] = vqshrun_n_s16(_r0, 6);
            _rgb0.val[1] = vqshrun_n_s16(_g0, 6);
            _rgb0.val[2] = vqshrun_n_s16(_b0, 6);

            uint8x8x3_t _rgb1;
            _rgb1.val[0] = vqshrun_n_s16(_r1, 6);
            _rgb1.val[1] = vqshrun_n_s16(_g1, 6);
            _rgb1.val[2] = vqshrun_n_s16(_b1, 6);

            vst3_u8(rgb0, _rgb0);
            vst3_u8(rgb1, _rgb1);

            yptr0 += 8;
            yptr1 += 8;
            vuptr += 8;
            rgb0 += 24;
            rgb1 += 24;
        }
#else
        if (nn > 0) {
            asm volatile(
                "0:                             \n"
                "pld        [%3, #128]          \n"
                "vld1.u8    {d2}, [%3]!         \n"
                "vsub.s8    d2, d2, %12         \n"
                "pld        [%1, #128]          \n"
                "vld1.u8    {d0}, [%1]!         \n"
                "pld        [%2, #128]          \n"
                "vld1.u8    {d1}, [%2]!         \n"
                "vshll.u8   q2, d0, #6          \n"
                "vorr       d3, d2, d2          \n"
                "vshll.u8   q3, d1, #6          \n"
                "vorr       q9, q2, q2          \n"
                "vtrn.s8    d2, d3              \n"
                "vorr       q11, q3, q3         \n"
                "vmlsl.s8   q9, d2, %14         \n"
                "vorr       q8, q2, q2          \n"
                "vmlsl.s8   q11, d2, %14        \n"
                "vorr       q10, q3, q3         \n"
                "vmlal.s8   q8, d2, %13         \n"
                "vmlal.s8   q2, d3, %16         \n"
                "vmlal.s8   q10, d2, %13        \n"
                "vmlsl.s8   q9, d3, %15         \n"
                "vmlal.s8   q3, d3, %16         \n"
                "vmlsl.s8   q11, d3, %15        \n"
                "vqshrun.s16 d24, q8, #6        \n"
                "vqshrun.s16 d26, q2, #6        \n"
                "vqshrun.s16 d4, q10, #6        \n"
                "vqshrun.s16 d25, q9, #6        \n"
                "vqshrun.s16 d6, q3, #6         \n"
                "vqshrun.s16 d5, q11, #6        \n"
                "subs       %0, #1              \n"
                "vst3.u8    {d24-d26}, [%4]!    \n"
                "vst3.u8    {d4-d6}, [%5]!      \n"
                "bne        0b                  \n"
                : "=r"(nn),    // %0
                  "=r"(yptr0), // %1
                  "=r"(yptr1), // %2
                  "=r"(vuptr), // %3
                  "=r"(rgb0),  // %4
                  "=r"(rgb1)   // %5
                : "0"(nn),
                  "1"(yptr0),
                  "2"(yptr1),
                  "3"(vuptr),
                  "4"(rgb0),
                  "5"(rgb1),
                  "w"(_v128), // %12
                  "w"(_v90),  // %13
                  "w"(_v46),  // %14
                  "w"(_v22),  // %15
                  "w"(_v113)  // %16
                : "cc", "memory", "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "d26");
        }
#endif // __aarch64__
#endif // __ARM_NEON

#define SATURATE_CAST_UCHAR(X) (uint8_t) std::min(std::max((int)(X), 0), 255);
        for (; remain > 0; remain -= 2) {
            // R = 1.164 * yy + 1.596 * vv
            // G = 1.164 * yy - 0.813 * vv - 0.391 * uu
            // B = 1.164 * yy              + 2.018 * uu

            // R = Y + (1.370705 * (V-128))
            // G = Y - (0.698001 * (V-128)) - (0.337633 * (U-128))
            // B = Y + (1.732446 * (U-128))

            // R = ((Y << 6) + 87.72512 * (V-128)) >> 6
            // G = ((Y << 6) - 44.672064 * (V-128) - 21.608512 * (U-128)) >> 6
            // B = ((Y << 6) + 110.876544 * (U-128)) >> 6

            // R = ((Y << 6) + 90 * (V-128)) >> 6
            // G = ((Y << 6) - 46 * (V-128) - 22 * (U-128)) >> 6
            // B = ((Y << 6) + 113 * (U-128)) >> 6

            // R = (yy + 90 * vv) >> 6
            // G = (yy - 46 * vv - 22 * uu) >> 6
            // B = (yy + 113 * uu) >> 6

            int v = vuptr[0] - 128;
            int u = vuptr[1] - 128;

            int ruv = 90 * v;
            int guv = -46 * v + -22 * u;
            int buv = 113 * u;

            int y00 = yptr0[0] << 6;
            rgb0[0] = SATURATE_CAST_UCHAR((y00 + ruv) >> 6);
            rgb0[1] = SATURATE_CAST_UCHAR((y00 + guv) >> 6);
            rgb0[2] = SATURATE_CAST_UCHAR((y00 + buv) >> 6);

            int y01 = yptr0[1] << 6;
            rgb0[3] = SATURATE_CAST_UCHAR((y01 + ruv) >> 6);
            rgb0[4] = SATURATE_CAST_UCHAR((y01 + guv) >> 6);
            rgb0[5] = SATURATE_CAST_UCHAR((y01 + buv) >> 6);

            int y10 = yptr1[0] << 6;
            rgb1[0] = SATURATE_CAST_UCHAR((y10 + ruv) >> 6);
            rgb1[1] = SATURATE_CAST_UCHAR((y10 + guv) >> 6);
            rgb1[2] = SATURATE_CAST_UCHAR((y10 + buv) >> 6);

            int y11 = yptr1[1] << 6;
            rgb1[3] = SATURATE_CAST_UCHAR((y11 + ruv) >> 6);
            rgb1[4] = SATURATE_CAST_UCHAR((y11 + guv) >> 6);
            rgb1[5] = SATURATE_CAST_UCHAR((y11 + buv) >> 6);

            yptr0 += 2;
            yptr1 += 2;
            vuptr += 2;
            rgb0 += 6;
            rgb1 += 6;
        }
#undef SATURATE_CAST_UCHAR

        yptr += 2 * w;
        rgb += 2 * 3 * w;
    }
}

} // namespace cv