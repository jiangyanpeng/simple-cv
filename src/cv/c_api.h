#ifndef SIMPLE_CV_C_API_H_
#define SIMPLE_CV_C_API_H_
#include <common.h>
#include <intrinsic.h>

namespace cv {

void resize_bilinear_c1(const uint8_t* src,
                        uint32_t srcw,
                        uint32_t srch,
                        uint8_t* dst,
                        uint32_t w,
                        uint32_t h);

void resize_bilinear_c2(const uint8_t* src,
                        uint32_t srcw,
                        uint32_t srch,
                        uint8_t* dst,
                        uint32_t w,
                        uint32_t h);

void resize_bilinear_c3(const uint8_t* src,
                        uint32_t srcw,
                        uint32_t srch,
                        uint8_t* dst,
                        uint32_t w,
                        uint32_t h);

void resize_bilinear_c4(const uint8_t* src,
                        uint32_t srcw,
                        uint32_t srch,
                        uint8_t* dst,
                        uint32_t w,
                        uint32_t h);

void resize_bilinear_yuv420sp(const uint8_t* src,
                              uint32_t srcw,
                              uint32_t srch,
                              uint8_t* dst,
                              uint32_t w,
                              uint32_t h);

void get_rotation_matrix(float angle, float scale, float dx, float dy, float* tm);

void get_affine_transform(const float* points_from,
                          const float* points_to,
                          uint32_t num_point,
                          float* tm);

void warpaffine_bilinear_c1(const uint8_t* src,
                            uint32_t srcw,
                            uint32_t srch,
                            uint8_t* dst,
                            uint32_t w,
                            uint32_t h,
                            const float* tm,
                            uint32_t type,
                            unsigned int v);

void warpaffine_bilinear_c2(const uint8_t* src,
                            uint32_t srcw,
                            uint32_t srch,
                            uint8_t* dst,
                            uint32_t w,
                            uint32_t h,
                            const float* tm,
                            uint32_t type,
                            unsigned int v);

void warpaffine_bilinear_c3(const uint8_t* src,
                            uint32_t srcw,
                            uint32_t srch,
                            uint8_t* dst,
                            uint32_t w,
                            uint32_t h,
                            const float* tm,
                            uint32_t type,
                            unsigned int v);

void warpaffine_bilinear_c4(const uint8_t* src,
                            uint32_t srcw,
                            uint32_t srch,
                            uint8_t* dst,
                            uint32_t w,
                            uint32_t h,
                            const float* tm,
                            uint32_t type,
                            unsigned int v);

void warpaffine_bilinear_yuv420sp(const uint8_t* src,
                                  uint32_t srcw,
                                  uint32_t srch,
                                  uint8_t* dst,
                                  uint32_t w,
                                  uint32_t h,
                                  const float* tm,
                                  uint32_t type,
                                  unsigned int v);

void convert_rgb_to_bgr_planner(const uint8_t* rgb,
                                uint32_t w,
                                uint32_t h,
                                uint32_t stride,
                                uint8_t* bgr);

void convert_yuv420sp_to_rgb_packed(const uint8_t* yuv420sp, uint32_t w, uint32_t h, uint8_t* rgb);

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
                           uint32_t w,
                           uint32_t h,
                           float mean[3],
                           float std[3],
                           float* norm);

bool normalize_8uc3_planner(const uint8_t* image,
                            uint32_t w,
                            uint32_t h,
                            float mean[3],
                            float std[3],
                            float* norm);
} // namespace cv
#endif // SIMPLE_CV_C_API_H_