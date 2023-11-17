#ifndef SIMPLE_CV_PARAMTER_H_
#define SIMPLE_CV_PARAMTER_H_

#include "utils.h"

namespace cv {

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    None            = 0,
    ColorCvt        = 1,
    Crop            = 2,
    Resize          = 3,
    CropResize      = 4,
    WarpAffine      = 5,
    MultiWarpAffine = 6,
    Pad             = 7,
    MeadStd         = 8,
    PixelNorm       = 9,
    ZScoreNorm      = 10,
    WaitDone        = 11,
    ChannelSplit    = 12,
    ChannelMerge    = 13,
    Stitching       = 14,
    TransPlateform  = 15,
    ConvertTo       = 16,
    Remap           = 17,
    WarpPerspective = 18,
    Flip            = 19,
    Rotate          = 20,
    CopyMakeBorder  = 21,
    RangeNorm       = 22,

    WISP_OP_TYPE_MAKE_ENUM_32_BIT = 0xffffffff,
} OpType;

///@brief param for ColorCvt
PACKED_STRUCT({
    enum ColorCvtType {
        GRAY8                     = 1,  /**< gray8  */
        RGBA8888                  = 2,  /**< rgba8888 */
        RGB888                    = 3,  /**< rgb888 */
        RGB888_PLANAR             = 4,  /**< rgb888 RRRRRR:GGGGGG:BBBBBB */
        BGRA8888                  = 5,  /**< bgra8888 */
        BGR888                    = 6,  /**< bgr888 */
        BGR888_PLANAR             = 7,  /**< bgr888 BBBBBB:GGGGGG:RRRRRR */
        YUV420P                   = 8,  /**< yuv420p */
        NV12                      = 9,  /**< YUV  4:2:0 YYYY:UV */
        NV21                      = 10, /**< YUV  4:2:0 YYYY:VU */
        GRAY32                    = 11, /**< gray32*/
        RGB323232                 = 12, /**< rgb323232 fp32*/
        RGB323232_PLANAR          = 13, /**< rgb323232 fp32  RRRRRR:GGGGGG:BBBBBB*/
        BGR323232                 = 14, /**< bgr323232 fp32*/
        BGR323232_PLANAR          = 15, /**< bgr323232 fp32 BBBBBB:GGGGGG:RRRRRR*/
        GRAY16                    = 16, /**< gray16*/
        RGB161616                 = 17, /**< rgb161616 fp16*/
        RGB161616_PLANAR          = 18, /**< rgb161616 fp16  RRRRRR:GGGGGG:BBBBBB*/
        BGR161616                 = 19, /**< bgr161616 fp16*/
        BGR161616_PLANAR          = 20, /**< bgr161616 fp16 BBBBBB:GGGGGG:RRRRRR*/
        FLOAT32C4                 = 21, /**< fp32 channel ==4 */
        NV12_DETACH               = 22, /**< Y/UV not Contiguous memory*/
        NV21_DETACH               = 23, /**< Y/UV not Contiguous memory*/
        YUYV                      = 24, /**< YUV422 PACKED*/
        UYVY                      = 25, /**< YUV422 PACKED*/
        YV12                      = 26, /**< YUV  4:2:0 YYYYYYYY:VVUU */
        YU12                      = 27, /**< YUV  4:2:0 YYYYYYYY:UUVV */
        COLORCVT_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    ColorCvtType src_type; // Optional : Can be automatically detected by op input
    ColorCvtType dst_type;
} ColorCvtParam)

///@brief param for Crop
PACKED_STRUCT({
    unsigned int left;
    unsigned int top;
    unsigned int height;
    unsigned int width;
} CropParam)

PACKED_STRUCT({
    unsigned int flip_code; /**< 0: x-axis flip, 1: y-axis flip */
} FlipParam)

///@brief param for Rotate
PACKED_STRUCT({ unsigned int rotate_degree; } RotateParam)

///@brief param for CopyMakeBorder
PACKED_STRUCT({
    int top;
    int left;
    int bottom;
    int right;
    enum BorderType {
        CONSTANT,
        REPLICATE,
        REFLECT,
        WRAP,
        REFLECT_101,
        BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    BorderType type;
    float border_val;
} CopyMakeBorderParam)

///@brief param for Resize
PACKED_STRUCT({
    enum ResizeType {
        NEAREST,
        LINEAR,
        AREA,
        RESIZE_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    ResizeType type;
    unsigned int height;
    unsigned int width;
} ResizeParam)

///@brief param for CropResize
PACKED_STRUCT({
    enum ResizeType {
        NEAREST,
        LINEAR,
        AREA,
        RESIZE_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    ResizeType type;
    unsigned int crop_left;
    unsigned int crop_top;
    unsigned int crop_height;
    unsigned int crop_width;
    unsigned int resize_height;
    unsigned int resize_width;
} CropResizeParam)

///@brief param for warpaffine
PACKED_STRUCT({
    enum WarpAffineType {
        NEAREST,
        LINEAR,
        WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    enum WarpAffineBorderType {
        CONSTANT,
        BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    WarpAffineType type;
    WarpAffineBorderType border_type;
    float affine_mat[6];
    unsigned int height;
    unsigned int width;
    unsigned char border_val;
    unsigned char rsv1; // need align
    unsigned char rsv2; // need align
    unsigned char rsv3; // need align
} WarpAffineParam)

///@brief param for WarpPerspective
PACKED_STRUCT({
    enum WarpPerspectiveType {
        NEAREST,
        LINEAR,
        WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    enum WarpPerspectiveBorderType {
        CONSTANT                = 0,
        REPLICATE               = 1,
        TRANSPARENT             = 5,
        BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    WarpPerspectiveType type;
    WarpPerspectiveBorderType border_type;
    float affine_mat[9]; // 3x3 matrix
    unsigned int height;
    unsigned int width;
    unsigned char border_val;
    unsigned char rsv1; // need align
    unsigned char rsv2; // need align
    unsigned char rsv3; // need align
} WarpPerspectiveParam)

///@brief param for Pad
PACKED_STRUCT({
    unsigned int left;
    unsigned int top;
    unsigned int height;
    unsigned int width;
    float pad_val;
    unsigned char rsv1; // need align
    unsigned char rsv2; // need align
    unsigned char rsv3; // need align
} PadParam)

///@brief param for Norm
PACKED_STRUCT({
    float mean[3]; // GRAY: mean[0] , BGR : mean[0-2]
    float std[3];  // GRAY: std[0] , BGR : std[0-2]
} PixelNormParam)

///@brief param for range Norm
PACKED_STRUCT({
    float min; // min value for norm
    float max; // max value for norm
} RangeNormParam)


///@brief param for ConvertTo
PACKED_STRUCT({
    enum ConvertType {
        U8_TO_FP32,
        FP32_TO_U8,
        CVT_MAKE_ENUM_32_BIT = 0xffffffff,
    };
    ConvertType type;
} ConvertToParam)

#ifdef __cplusplus
} // extern "C"
#endif
} // namespace cv
#endif // SIMPLE_CV_PARAMTER_H_