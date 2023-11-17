#include "cv/core.h"

namespace cv {

bool normalize_8uc1(const uint8_t* image,
                    uint32_t w,
                    uint32_t h,
                    float mean[3],
                    float std[3],
                    float* norm) {
    if (!image || !norm || !std[0]) {
        return false;
    }

#ifdef __ARM_NEON
    int nn     = (w * h) >> 3;
    int remain = (w * h) - (nn << 3);
#elif defined(USE_AVX)
    int nn               = (w * h) >> 4;        // Calculate 16 pixel data per cycle.
    int remain           = (w * h) - (nn << 4); // Calculate the remain pixel.
#else
    int remain = w * h;
#endif
    float* ptr_dst         = norm;
    const uint8_t* ptr_src = image;

#ifdef __ARM_NEON
    printf("pass\n");
    remain = w
#elif defined(USE_AVX)
    __m256 mean_factor_0 = _mm256_set1_ps(mean[0]);
    __m256 std_factor_0  = _mm256_set1_ps(1.f / std[0]);

    __m256 dst_product_f32_0;
    for (; nn > 0; --nn) {
        __m128i v_src_b_u8    = _mm_loadu_si128((__m128i*)(ptr_src));
        __m256i v_src_b_l_s32 = _mm256_cvtepu8_epi32(v_src_b_u8);
        __m256i v_src_b_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_b_u8, 0b01001110));

        __m256 src_c0_f32_l = _mm256_cvtepi32_ps(v_src_b_l_s32);
        __m256 src_c0_f32_h = _mm256_cvtepi32_ps(v_src_b_h_s32);

        // process low half data
        dst_product_f32_0 = _mm256_mul_ps(std_factor_0, _mm256_sub_ps(src_c0_f32_l, mean_factor_0));
        _mm256_storeu_si256((__m256i*)(ptr_dst), _mm256_castps_si256(dst_product_f32_0));

        // process hight half data
        dst_product_f32_0 = _mm256_mul_ps(std_factor_0, _mm256_sub_ps(src_c0_f32_h, mean_factor_0));
        _mm256_storeu_si256((__m256i*)(ptr_dst + 8), _mm256_castps_si256(dst_product_f32_0));

        ptr_src += 16;
        ptr_dst += 16;
    }
#endif
        for (int i = 0; i < remain; ++i) {
        ptr_dst[0] = ((float)ptr_src[0] - mean[0]) / std[0];
        ptr_src++;
        ptr_dst++;
    }
    return true;
}

bool normalize_8uc3_packed(const uint8_t* image,
                           int w,
                           int h,
                           float mean[3],
                           float std[3],
                           float* norm) {
    if (!image || !norm) {
        return false;
    }
    if (std[0] == 0 || std[1] == 0 || std[2] == 0) {
        return false;
    }

#ifdef __ARM_NEON
    int nn     = (w * h) >> 3;
    int remain = (w * h) - (nn << 3);
#elif defined(USE_AVX)
    int nn               = (w * h) >> 4;        // Calculate 16 pixel data per cycle.
    int remain           = (w * h) - (nn << 4); // Calculate the remain pixel.
#else
    int remain = w * h;
#endif

    float* ptr_dst         = norm;
    const uint8_t* ptr_src = image;
#ifdef __ARM_NEON
    printf("pass\n");
    remain = w
#elif defined(USE_AVX)
    __m256 sub_factor_0  = _mm256_set1_ps(mean[0]);
    __m256 sub_factor_1  = _mm256_set1_ps(mean[1]);
    __m256 sub_factor_2  = _mm256_set1_ps(mean[2]);
    __m256 mult_factor_0 = _mm256_set1_ps(1.f / std[0]);
    __m256 mult_factor_1 = _mm256_set1_ps(1.f / std[1]);
    __m256 mult_factor_2 = _mm256_set1_ps(1.f / std[2]);

    __m256 dst_product_f32_0;
    __m256 dst_product_f32_1;
    __m256 dst_product_f32_2;
    for (; nn > 0; --nn) {
        __m128i v_src_b_u8;
        __m128i v_src_g_u8;
        __m128i v_src_r_u8;
        vld3_u8x16_avx(ptr_src, &v_src_b_u8, &v_src_g_u8, &v_src_r_u8);

        // u8 to s32
        __m256i v_src_b_l_s32 = _mm256_cvtepu8_epi32(v_src_b_u8);
        __m256i v_src_b_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_b_u8, 0b01001110));
        __m256i v_src_g_l_s32 = _mm256_cvtepu8_epi32(v_src_g_u8);
        __m256i v_src_g_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_g_u8, 0b01001110));
        __m256i v_src_r_l_s32 = _mm256_cvtepu8_epi32(v_src_r_u8);
        __m256i v_src_r_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_r_u8, 0b01001110));

        // s32 to f32
        __m256 src_c0_f32_l = _mm256_cvtepi32_ps(v_src_b_l_s32);
        __m256 src_c0_f32_h = _mm256_cvtepi32_ps(v_src_b_h_s32);
        __m256 src_c1_f32_l = _mm256_cvtepi32_ps(v_src_g_l_s32);
        __m256 src_c1_f32_h = _mm256_cvtepi32_ps(v_src_g_h_s32);
        __m256 src_c2_f32_l = _mm256_cvtepi32_ps(v_src_r_l_s32);
        __m256 src_c2_f32_h = _mm256_cvtepi32_ps(v_src_r_h_s32);

        // process low half data
        dst_product_f32_0 = _mm256_mul_ps(mult_factor_0, _mm256_sub_ps(src_c0_f32_l, sub_factor_0));
        dst_product_f32_1 = _mm256_mul_ps(mult_factor_1, _mm256_sub_ps(src_c1_f32_l, sub_factor_1));
        dst_product_f32_2 = _mm256_mul_ps(mult_factor_2, _mm256_sub_ps(src_c2_f32_l, sub_factor_2));
        vst3_f32x8_avx(dst_product_f32_0, dst_product_f32_1, dst_product_f32_2, ptr_dst);

        // process high half data
        dst_product_f32_0 = _mm256_mul_ps(mult_factor_0, _mm256_sub_ps(src_c0_f32_h, sub_factor_0));
        dst_product_f32_1 = _mm256_mul_ps(mult_factor_1, _mm256_sub_ps(src_c1_f32_h, sub_factor_1));
        dst_product_f32_2 = _mm256_mul_ps(mult_factor_2, _mm256_sub_ps(src_c2_f32_h, sub_factor_2));
        vst3_f32x8_avx(dst_product_f32_0, dst_product_f32_1, dst_product_f32_2, ptr_dst + 24);

        ptr_src += 48; // 16 * 3
        ptr_dst += 48; // 16 * 3
    }
#endif

        for (; remain > 0; --remain) {
        ptr_dst[0] = ((float)ptr_src[0] - mean[0]) / std[0];
        ptr_dst[1] = ((float)ptr_src[1] - mean[1]) / std[1];
        ptr_dst[2] = ((float)ptr_src[2] - mean[2]) / std[2];
        ptr_src += 3;
        ptr_dst += 3;
    }
    return true;
}

bool normalize_8uc3_planner(const uint8_t* image,
                            int w,
                            int h,
                            float mean[3],
                            float std[3],
                            float* norm) {
    if (!image || !norm) {
        return false;
    }
    if (std[0] == 0 || std[1] == 0 || std[2] == 0) {
        return false;
    }

#ifdef __ARM_NEON
    int nn     = (w * h) >> 3;
    int remain = (w * h) - (nn << 3);
#elif defined(USE_AVX)
    int nn               = (w * h) >> 4;        // Calculate 16 pixel data per cycle.
    int remain           = (w * h) - (nn << 4); // Calculate the remain pixel.
#else
    int remain = w * h;
#endif
    float* ptr_dst_c0      = norm;
    float* ptr_dst_c1      = norm + w * h;
    float* ptr_dst_c2      = norm + 2 * w * h;
    const uint8_t* ptr_src = image;

#ifdef __ARM_NEON
    printf("pass\n");
    remain = w
#elif defined(USE_AVX)
    __m256 sub_factor_0  = _mm256_set1_ps(mean[0]);
    __m256 sub_factor_1  = _mm256_set1_ps(mean[1]);
    __m256 sub_factor_2  = _mm256_set1_ps(mean[2]);
    __m256 mult_factor_0 = _mm256_set1_ps(1.f / std[0]);
    __m256 mult_factor_1 = _mm256_set1_ps(1.f / std[1]);
    __m256 mult_factor_2 = _mm256_set1_ps(1.f / std[2]);

    __m256 dst_product_f32_0;
    __m256 dst_product_f32_1;
    __m256 dst_product_f32_2;
    for (; nn > 0; --nn) {
        __m128i v_src_b_u8;
        __m128i v_src_g_u8;
        __m128i v_src_r_u8;
        vld3_u8x16_avx(ptr_src, &v_src_b_u8, &v_src_g_u8, &v_src_r_u8);

        // u8 to s32
        __m256i v_src_b_l_s32 = _mm256_cvtepu8_epi32(v_src_b_u8);
        __m256i v_src_b_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_b_u8, 0b01001110));
        __m256i v_src_g_l_s32 = _mm256_cvtepu8_epi32(v_src_g_u8);
        __m256i v_src_g_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_g_u8, 0b01001110));
        __m256i v_src_r_l_s32 = _mm256_cvtepu8_epi32(v_src_r_u8);
        __m256i v_src_r_h_s32 = _mm256_cvtepu8_epi32(_mm_shuffle_epi32(v_src_r_u8, 0b01001110));

        // s32 to f32
        __m256 src_c0_f32_l = _mm256_cvtepi32_ps(v_src_b_l_s32);
        __m256 src_c0_f32_h = _mm256_cvtepi32_ps(v_src_b_h_s32);
        __m256 src_c1_f32_l = _mm256_cvtepi32_ps(v_src_g_l_s32);
        __m256 src_c1_f32_h = _mm256_cvtepi32_ps(v_src_g_h_s32);
        __m256 src_c2_f32_l = _mm256_cvtepi32_ps(v_src_r_l_s32);
        __m256 src_c2_f32_h = _mm256_cvtepi32_ps(v_src_r_h_s32);

        // process low half data
        dst_product_f32_0 = _mm256_mul_ps(mult_factor_0, _mm256_sub_ps(src_c0_f32_l, sub_factor_0));
        dst_product_f32_1 = _mm256_mul_ps(mult_factor_1, _mm256_sub_ps(src_c1_f32_l, sub_factor_1));
        dst_product_f32_2 = _mm256_mul_ps(mult_factor_2, _mm256_sub_ps(src_c2_f32_l, sub_factor_2));

        _mm256_storeu_si256((__m256i*)(ptr_dst_c0), _mm256_castps_si256(dst_product_f32_0));
        _mm256_storeu_si256((__m256i*)(ptr_dst_c1), _mm256_castps_si256(dst_product_f32_1));
        _mm256_storeu_si256((__m256i*)(ptr_dst_c2), _mm256_castps_si256(dst_product_f32_2));

        // process high half data
        dst_product_f32_0 = _mm256_mul_ps(mult_factor_0, _mm256_sub_ps(src_c0_f32_h, sub_factor_0));
        dst_product_f32_1 = _mm256_mul_ps(mult_factor_1, _mm256_sub_ps(src_c1_f32_h, sub_factor_1));
        dst_product_f32_2 = _mm256_mul_ps(mult_factor_2, _mm256_sub_ps(src_c2_f32_h, sub_factor_2));

        _mm256_storeu_si256((__m256i*)(ptr_dst_c0 + 8), _mm256_castps_si256(dst_product_f32_0));
        _mm256_storeu_si256((__m256i*)(ptr_dst_c1 + 8), _mm256_castps_si256(dst_product_f32_1));
        _mm256_storeu_si256((__m256i*)(ptr_dst_c2 + 8), _mm256_castps_si256(dst_product_f32_2));

        ptr_src += 48;
        ptr_dst_c0 += 16;
        ptr_dst_c1 += 16;
        ptr_dst_c2 += 16;
    }
#endif
        for (; remain > 0; --remain) {
        *ptr_dst_c0 = ((float)ptr_src[0] - mean[0]) / std[0];
        *ptr_dst_c1 = ((float)ptr_src[1] - mean[1]) / std[1];
        *ptr_dst_c2 = ((float)ptr_src[2] - mean[2]) / std[2];
        ptr_dst_c0++;
        ptr_dst_c1++;
        ptr_dst_c2++;
        ptr_src += 3;
    }
    return true;
}

} // namespace cv