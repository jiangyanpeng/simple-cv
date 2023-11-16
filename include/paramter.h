// #ifndef SIMPLE_CV_PARAMTER_H_
// #define SIMPLE_CV_PARAMTER_H_

// #include "common.h"

// namespace cv {
// #ifdef __cplusplus
// extern "C" {
// #endif

// typedef enum {
//     None            = 0,
//     ColorCvt        = 1,
//     Crop            = 2,
//     Resize          = 3,
//     CropResize      = 4,
//     WarpAffine      = 5,
//     MultiWarpAffine = 6,
//     Pad             = 7,
//     MeadStd         = 8,
//     PixelNorm       = 9,
//     ZScoreNorm      = 10,
//     WaitDone        = 11,
//     ChannelSplit    = 12,
//     ChannelMerge    = 13,
//     Stitching       = 14,
//     TransPlateform  = 15,
//     ConvertTo       = 16,
//     Remap           = 17,
//     WarpPerspective = 18,
//     Flip            = 19,
//     Rotate          = 20,
//     CopyMakeBorder  = 21,
//     RangeNorm       = 22,
//     MaxPool,
//     Prelu,
//     Concat,
//     Sub,
//     Abs,
//     ArgMax,
//     Sigmoid,
//     RemoveFirstNChannel,
//     Rescale,
//     GenAnchor,
//     GetBboxesNmsPre,
//     Delta2Bbox,
//     Softmax,
//     Nms,
//     RetinaFusion,
//     MaxPooling,
//     Argmax,
//     MatchTrpletaction,
//     TopK,
//     DistMatrix,
//     PickDataByIndex,
//     IndexToPos,
//     CalcHoiCombineScore,
//     Rodrigues,
//     SolvePnP,
//     WispOpMax,
//     WISP_OP_TYPE_MAKE_ENUM_32_BIT = 0xffffffff,
// } WispOpType;


// ///@brief param for ColorCvt
// PACKED_STRUCT({
//     enum ColorCvtType {
//         GRAY8                     = 1,  /**< gray8  */
//         RGBA8888                  = 2,  /**< rgba8888 */
//         RGB888                    = 3,  /**< rgb888 */
//         RGB888_PLANAR             = 4,  /**< rgb888 RRRRRR:GGGGGG:BBBBBB */
//         BGRA8888                  = 5,  /**< bgra8888 */
//         BGR888                    = 6,  /**< bgr888 */
//         BGR888_PLANAR             = 7,  /**< bgr888 BBBBBB:GGGGGG:RRRRRR */
//         YUV420P                   = 8,  /**< yuv420p */
//         NV12                      = 9,  /**< YUV  4:2:0 YYYY:UV */
//         NV21                      = 10, /**< YUV  4:2:0 YYYY:VU */
//         GRAY32                    = 11, /**< gray32*/
//         RGB323232                 = 12, /**< rgb323232 fp32*/
//         RGB323232_PLANAR          = 13, /**< rgb323232 fp32  RRRRRR:GGGGGG:BBBBBB*/
//         BGR323232                 = 14, /**< bgr323232 fp32*/
//         BGR323232_PLANAR          = 15, /**< bgr323232 fp32 BBBBBB:GGGGGG:RRRRRR*/
//         GRAY16                    = 16, /**< gray16*/
//         RGB161616                 = 17, /**< rgb161616 fp16*/
//         RGB161616_PLANAR          = 18, /**< rgb161616 fp16  RRRRRR:GGGGGG:BBBBBB*/
//         BGR161616                 = 19, /**< bgr161616 fp16*/
//         BGR161616_PLANAR          = 20, /**< bgr161616 fp16 BBBBBB:GGGGGG:RRRRRR*/
//         FLOAT32C4                 = 21, /**< fp32 channel ==4 */
//         NV12_DETACH               = 22, /**< Y/UV not Contiguous memory*/
//         NV21_DETACH               = 23, /**< Y/UV not Contiguous memory*/
//         YUYV                      = 24, /**< YUV422 PACKED*/
//         UYVY                      = 25, /**< YUV422 PACKED*/
//         YV12                      = 26, /**< YUV  4:2:0 YYYYYYYY:VVUU */
//         YU12                      = 27, /**< YUV  4:2:0 YYYYYYYY:UUVV */
//         COLORCVT_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     ColorCvtType src_type; // Optional : Can be automatically detected by op input
//     ColorCvtType dst_type;
// } WispColorCvtParam)

// ///@brief param for Crop
// PACKED_STRUCT({
//     unsigned int left;
//     unsigned int top;
//     unsigned int height;
//     unsigned int width;
// } WispCropParam)

// PACKED_STRUCT({
//     unsigned int flip_code; /**< 0: x-axis flip, 1: y-axis flip */
// } WispFlipParam)

// ///@brief param for Rotate
// PACKED_STRUCT({ unsigned int rotate_degree; } WispRotateParam)

// ///@brief param for CopyMakeBorder
// PACKED_STRUCT({
//     int top;
//     int left;
//     int bottom;
//     int right;
//     enum BorderType {
//         CONSTANT,
//         REPLICATE,
//         REFLECT,
//         WRAP,
//         REFLECT_101,
//         BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     BorderType type;
//     float border_val;
// } WispCopyMakeBorderParam)

// ///@brief param for Resize
// PACKED_STRUCT({
//     enum ResizeType {
//         NEAREST,
//         LINEAR,
//         AREA,
//         RESIZE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     ResizeType type;
//     unsigned int height;
//     unsigned int width;
// } WispResizeParam)

// ///@brief param for CropResize
// PACKED_STRUCT({
//     enum ResizeType {
//         NEAREST,
//         LINEAR,
//         AREA,
//         RESIZE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     ResizeType type;
//     unsigned int crop_left;
//     unsigned int crop_top;
//     unsigned int crop_height;
//     unsigned int crop_width;
//     unsigned int resize_height;
//     unsigned int resize_width;
// } WispCropResizeParam)

// ///@brief param for warpaffine
// PACKED_STRUCT({
//     enum WarpAffineType {
//         NEAREST,
//         LINEAR,
//         WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     enum WarpAffineBorderType {
//         CONSTANT,
//         BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     WarpAffineType type;
//     WarpAffineBorderType border_type;
//     float affine_mat[6];
//     unsigned int height;
//     unsigned int width;
//     unsigned char border_val;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispWarpAffineParam)

// PACKED_STRUCT({
//     enum WarpAffineType {
//         NEAREST,
//         LINEAR,
//         WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     enum WarpAffineBorderType {
//         CONSTANT,
//         BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     WarpAffineType type;
//     WarpAffineBorderType border_type;
//     unsigned int height;
//     unsigned int width;
//     unsigned int object_num;
//     unsigned char border_val;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispMultiWarpAffineParam)

// ///@brief param for WarpPerspective
// PACKED_STRUCT({
//     enum WarpPerspectiveType {
//         NEAREST,
//         LINEAR,
//         WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     enum WarpPerspectiveBorderType {
//         CONSTANT                = 0,
//         REPLICATE               = 1,
//         TRANSPARENT             = 5,
//         BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     WarpPerspectiveType type;
//     WarpPerspectiveBorderType border_type;
//     float affine_mat[9]; // 3x3 matrix
//     unsigned int height;
//     unsigned int width;
//     unsigned char border_val;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispWarpPerspectiveParam)

// ///@brief param for Pad
// PACKED_STRUCT({
//     unsigned int left;
//     unsigned int top;
//     unsigned int height;
//     unsigned int width;
//     float pad_val;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispPadParam)

// ///@brief param for Norm
// PACKED_STRUCT({
//     float mean[3]; // GRAY: mean[0] , BGR : mean[0-2]
//     float std[3];  // GRAY: std[0] , BGR : std[0-2]
// } WispPixelNormParam)

// ///@brief param for range Norm
// PACKED_STRUCT({
//     float min; // min value for norm
//     float max; // max value for norm
// } WispRangeNormParam)

// ///@brief param for ipm_stitching
// PACKED_STRUCT({
//     unsigned int src_width;
//     unsigned int src_height;
//     unsigned int dst_width;
//     unsigned int dst_height;
// } WispStitchingParam)

// ///@brief param for ConvertTo
// PACKED_STRUCT({
//     enum ConvertType {
//         U8_TO_FP32,
//         FP32_TO_U8,
//         CVT_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     ConvertType type;
// } WispConvertToParam)

// ///@brief param for remap
// PACKED_STRUCT({
//     enum RemapType {
//         NEAREST,
//         LINEAR,
//         WARP_AFFINE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     enum RemapBorderType {
//         CONSTANT,
//         BORDER_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     RemapType type;
//     RemapBorderType border_type;
//     unsigned char border_val;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispRemapParam)

// /* =============================
//  * Param definition for postop
//  * ============================= */

// ///@brief ImgMetaTensor : | ori.whc | final.whc | mat[2][3] |
// enum ImgMetaTensorIndex {
//     ImgMetaOriginWidth       = 0,
//     ImgMetaOriginHeight      = 1,
//     ImgMetaOriginChannel     = 2,
//     ImgMetaFinalWidth        = 3,
//     ImgMetaFinalHeight       = 4,
//     ImgMetaFinalChannel      = 5,
//     ImgMetaTransformMatrix   = 6,
//     ImgMetaMax               = 12,
//     IMAMETA_MAKE_ENUM_32_BIT = 0xffffffff,
// };
// #define IMGMETA_TENSOR_SIZE ImgMetaTensorIndex::ImgMetaMax

// #define RETINA_ANCHOR_STRIDE_MAX_SIZE 8
// #define RETINA_ANCHOR_SCALE_MAX_SIZE 8
// #define RETINA_ANCHOR_RATIO_MAX_SIZE 8
// ///@brief param for GenAnchor
// PACKED_STRUCT({
//     float anchor_stride[RETINA_ANCHOR_STRIDE_MAX_SIZE];
//     float anchor_scale[RETINA_ANCHOR_SCALE_MAX_SIZE];
//     float anchor_ratio[RETINA_ANCHOR_RATIO_MAX_SIZE];
//     unsigned int anchor_stride_num;
//     unsigned int anchor_scale_num;
//     unsigned int anchor_ratio_num;
//     unsigned int level_num;
//     float anchor_margin;
//     bool round_edge;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispParamGenAnchor)

// ///@brief param for GetBboxesNmsPre
// PACKED_STRUCT({
//     unsigned int class_num;
//     unsigned int level_num;
//     unsigned int topk;
// } WispParamGetBboxesNmsPre)

// ///@brief param for Delta2Bbox
// PACKED_STRUCT({
//     float box_margin;
//     float wh_ratio_clip;
//     float means[4];
//     float stds[4];
//     bool with_rel;      // with relationship (channel = 6)
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispParamDelta2Bbox)

// ///@brief param for RemoveFirstNChannel
// PACKED_STRUCT({ unsigned int k; } WispParamRemoveFirstNChannel)

// ///@brief param for Softmax
// PACKED_STRUCT({
//     unsigned int level_num; // multi tensor num; N inputs : N outputs
//     unsigned int base_anchor_count;
//     unsigned int k;
// } WispParamSoftmax)

// ///@brief param for MaxPooling
// PACKED_STRUCT({
//     unsigned int kernel;
//     unsigned int stride;
//     unsigned int pad;
//     unsigned int topk = 0;
//     bool nms;
//     bool topk_cross_channel;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
// } WispParamMaxPooling)

// ///@brief param for TopK
// PACKED_STRUCT({
//     unsigned int k;
//     bool cross_channel;
//     unsigned char rsv1; // need align
//     unsigned char rsv2; // need align
//     unsigned char rsv3; // need align
// } WispParamTopK)

// ///@brief param for IndexToPos
// PACKED_STRUCT({
//     unsigned int h;
//     unsigned int w;
// } WispParamIndexToPos)

// #define NMS_CLASS_MAX_SIZE 16u
// #define NMS_PROPOSAL_MAX_SIZE 32u
// ///@brief param for Nms
// PACKED_STRUCT({
//     enum NmsType {
//         NMS = 0,
//         SOFTNMS_LINEAR,
//         SOFTNMS_GAUSSIAN,
//         NMS_TYPE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     float score_thr[NMS_CLASS_MAX_SIZE];
//     unsigned int class_num;
//     unsigned int max_per_img;
//     float anchor_margin;
//     float iou_thr;
//     NmsType type;
// } WispParamNms)

// ///@brief param for Rodrigues
// PACKED_STRUCT({
//     enum RodriguesType {
//         VECTOR_2_MATRIX = 0,
//         MATRIX_2_VECTOR,
//         RODRIGUES_INVALID,
//         RODRIGUES_TYPE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     RodriguesType rodrigues_type;
// } WispParamRodrigues)

// ///@brief param for SolvePnP
// PACKED_STRUCT({
//     enum SolvePnPType {
//         SOLVEPNP_ITERATIVE = 0,
//         SOLVEPNP_EPNP,
//         SOLVEPNP_P3P,
//         SOLVEPNP_DLS,
//         SOLVEPNP_INVALID               = 10,
//         SOLVEPNP_TYPE_MAKE_ENUM_32_BIT = 0xffffffff,
//     };
//     SolvePnPType pnp_type;
// } WispParamSolvePnP)

// ///@brief param for Concat
// PACKED_STRUCT({ unsigned int axis; } WispParamConcat)

// ///@brief param for ArgMax
// PACKED_STRUCT({ unsigned int axis; } WispParamArgMax)

// ///@brief param for RetinaFusion
// #define RETINA_FUSION_MAX_LEVEL 5
// #define RETINA_FUSION_MAX_MIDDLE_OUTPUTS 12

// PACKED_STRUCT({
//     // GetBboxesNmsPre -> Sigmoid -> Delta2box -> Rescale ->Nms
//     WispParamGenAnchor gen_anchor_param;
//     WispParamGetBboxesNmsPre nms_pre_param;
//     WispParamDelta2Bbox delta2bbox_param;
//     WispParamNms nms_param;
//     union {
//         struct {
//             WispOpTensorParam mlvl_anchor_level[RETINA_FUSION_MAX_LEVEL]; // output of gen anchor
//             WispOpTensorParam topk_cls_score;                             // output of nmspre
//             WispOpTensorParam topk_bbox_pred;                             // output of nmspre
//             WispOpTensorParam topk_bbox_anchor;                           // output of nmspre
//             WispOpTensorParam topk_bbox_label;                            // output of nmspre
//             WispOpTensorParam normalize_topk_cls_score;                   // output of sigmoid
//             WispOpTensorParam topk_bbox;                                  // output of delta2box
//             WispOpTensorParam rescale_topk_bbox;                          // output of rescale
//         } tensor;
//         WispOpTensorParam data[RETINA_FUSION_MAX_MIDDLE_OUTPUTS];
//     } middle_outputs;
//     unsigned int gen_anchor_use_cache;    // control gen anchor run or not,set inside
//     unsigned int gen_anchor_cache_handle; // unique id for different ops,set inside
// } WispParamRetinaFusion)

// #ifdef __cplusplus
// } // extern "C"
// #endif
// } // namespace cv
// #endif // SIMPLE_CV_PARAMTER_H_