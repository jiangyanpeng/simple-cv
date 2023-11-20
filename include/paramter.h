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
    CV_TYPE_MAX     = 23,
} OpType;

PACKED_STRUCT({
    enum ColorCvtType {
        BGR2NV21     = 0,
        NV212BGR     = 1,
        RGB2NV21     = 2,
        NV212RGB     = 3,
        RGB2NV12     = 4,
        NV122RGB     = 5,
        BGR2NV12     = 6,
        NV122BGR     = 7,
        BGR2GRAY     = 8,
        GRAY2BGR     = 9,
        BGR2BGRA     = 10,
        BGRA2BGR     = 11,
        RGB2GRAY     = 12,
        GRAY2RGB     = 13,
        BGR2RGB      = 14,
        RGB2BGR      = 15,
        RGB2YV12     = 16,
        BGR2YV12     = 17,
        YUV2GRAY_420 = 18,
        NV122NV21    = 19,
        NV212NV12    = 20,
    };
    ColorCvtType convect_type;
} ColorCvtParam)


PACKED_STRUCT({
    unsigned int left;
    unsigned int top;
    unsigned int height;
    unsigned int width;
} CropParam)

// clang-format off
PACKED_STRUCT({
    unsigned int flip_code;
} FlipParam)

PACKED_STRUCT({ 
    unsigned int rotate_degree; 
} RotateParam)

// clang-format on
PACKED_STRUCT({
    int top;
    int left;
    int bottom;
    int right;
    enum BorderType {
        CONSTANT    = 0,
        REPLICATE   = 1,
        REFLECT     = 2,
        WRAP        = 3,
        REFLECT_101 = 4,
        BORDER_MAX  = 5,
    };
    BorderType type;
    float border_val;
} CopyMakeBorderParam)

PACKED_STRUCT({
    enum ResizeType {
        NEAREST    = 0,
        LINEAR     = 1,
        AREA       = 2,
        RESIZE_MAX = 3,
    };
    ResizeType type;
    unsigned int height;
    unsigned int width;
} ResizeParam)

PACKED_STRUCT({
    enum ResizeType {
        NEAREST    = 0,
        LINEAR     = 1,
        AREA       = 2,
        RESIZE_MAX = 3,
    };
    ResizeType type;
    unsigned int crop_left;
    unsigned int crop_top;
    unsigned int crop_height;
    unsigned int crop_width;
    unsigned int resize_height;
    unsigned int resize_width;
} CropResizeParam)

PACKED_STRUCT({
    enum WarpAffineType {
        NEAREST         = 0,
        LINEAR          = 1,
        WARP_AFFINE_MAX = 2,
    };
    enum WarpAffineBorderType {
        CONSTANT        = 0,
        BORDER_TYPE_MAX = 1,
    };
    WarpAffineType type;
    WarpAffineBorderType border_type;
    float affine_mat[6];
    unsigned int height;
    unsigned int width;
    unsigned char border_val;
} WarpAffineParam)

///@brief param for WarpPerspective
PACKED_STRUCT({
    enum WarpPerspectiveType {
        NEAREST         = 0,
        LINEAR          = 1,
        WARP_AFFINE_MAX = 2,
    };
    enum WarpPerspectiveBorderType {
        CONSTANT        = 0,
        REPLICATE       = 1,
        TRANSPARENT     = 2,
        BORDER_TYPE_MAX = 3,
    };
    WarpPerspectiveType type;
    WarpPerspectiveBorderType border_type;
    float affine_mat[9];
    unsigned int height;
    unsigned int width;
    unsigned char border_val;
} WarpPerspectiveParam)

PACKED_STRUCT({
    unsigned int left;
    unsigned int top;
    unsigned int height;
    unsigned int width;
    float pad_val;
} PadParam)


PACKED_STRUCT({
    float mean[3];
    float std[3];
} PixelNormParam)


PACKED_STRUCT({
    float min;
    float max;
} RangeNormParam)


PACKED_STRUCT({
    enum ConvertType {
        U8_TO_FP32   = 0,
        FP32_TO_U8   = 1,
        CVT_MAX_TYPE = 2,
    };
    ConvertType type;
} ConvertToParam)
#ifdef __cplusplus
} // extern "C"
#endif

} // namespace cv
#endif // SIMPLE_CV_PARAMTER_H_