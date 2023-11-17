#ifndef SIMPLE_CV_CORE_H_
#define SIMPLE_CV_CORE_H_
#include <common.h>
#include <intrinsic.h>
namespace cv {
void resize_bilinear_c1(const uint8_t* src, int srcw, int srch, uint8_t* dst, int w, int h);

void resize_bilinear_c2(const uint8_t* src, int srcw, int srch, uint8_t* dst, int w, int h);

void resize_bilinear_c3(const uint8_t* src, int srcw, int srch, uint8_t* dst, int w, int h);

void resize_bilinear_c4(const uint8_t* src, int srcw, int srch, uint8_t* dst, int w, int h);

void resize_bilinear_yuv420sp(const uint8_t* src, int srcw, int srch, uint8_t* dst, int w, int h);

void get_rotation_matrix(float angle, float scale, float dx, float dy, float* tm);

void get_affine_transform(const float* points_from,
                          const float* points_to,
                          int num_point,
                          float* tm);

void warpaffine_bilinear_c1(const uint8_t* src,
                            int srcw,
                            int srch,
                            uint8_t* dst,
                            int w,
                            int h,
                            const float* tm,
                            int type,
                            unsigned int v);

void warpaffine_bilinear_c2(const uint8_t* src,
                            int srcw,
                            int srch,
                            uint8_t* dst,
                            int w,
                            int h,
                            const float* tm,
                            int type,
                            unsigned int v);

void warpaffine_bilinear_c3(const uint8_t* src,
                            int srcw,
                            int srch,
                            uint8_t* dst,
                            int w,
                            int h,
                            const float* tm,
                            int type,
                            unsigned int v);

void warpaffine_bilinear_c4(const uint8_t* src,
                            int srcw,
                            int srch,
                            uint8_t* dst,
                            int w,
                            int h,
                            const float* tm,
                            int type,
                            unsigned int v);

void warpaffine_bilinear_yuv420sp(const uint8_t* src,
                                  int srcw,
                                  int srch,
                                  uint8_t* dst,
                                  int w,
                                  int h,
                                  const float* tm,
                                  int type,
                                  unsigned int v);

int rgb2bgr(const uint8_t* rgb, int w, int h, int stride, uint8_t* bgr);

void yuv420sp2rgb(const uint8_t* yuv420sp, int w, int h, uint8_t* rgb);

void convert_bgr_to_rgb_packed(const uint8_t* src,
                               uint32_t w,
                               uint32_t h,
                               uint32_t stride,
                               uint8_t* dst);

void convert_bgr_to_gray_packed(const uint8_t* src,
                                uint32_t w,
                                uint32_t h,
                                uint32_t stride,
                                uint8_t* dst,
                                bool rgb_mode);

void convert_package_to_planar_c3(const uint8_t* src,
                                  uint32_t w,
                                  uint32_t h,
                                  uint32_t stride,
                                  uint8_t* dst);

void convert_planar_to_package_c3(const uint8_t* src,
                                  uint32_t w,
                                  uint32_t h,
                                  uint32_t stride,
                                  uint8_t* dst);

bool normalize_8uc3_packed(const uint8_t* rgb,
                           int w,
                           int h,
                           float mean[3],
                           float std[3],
                           float* norm);

bool normalize_8uc3_planner(const uint8_t* image,
                            int w,
                            int h,
                            float mean[3],
                            float std[3],
                            float* norm);
} // namespace cv
#endif // SIMPLE_CV_CORE_H_