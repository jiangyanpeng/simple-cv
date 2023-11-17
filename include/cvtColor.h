#ifndef SIMPLE_CV_COLOT_CONVERT_H_
#define SIMPLE_CV_COLOT_CONVERT_H_

#include "transform.h"
#include <functional>

namespace cv {
class cvtColor final : public Transform {
public:
    cvtColor() {}
    ~cvtColor() {}

    MStatus Init(const std::string& name,
                 const void* param,
                 const size_t param_len,
                 const void* context = nullptr,
                 const bool inplace  = false) override;

    MStatus Run(const std::shared_ptr<base::Image>& inputs,
                std::shared_ptr<base::Image>& outputs) override;

public:
    // static MStatus BGR2GRAY_31(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus BGR2RGB_33(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus BGR2BGRA_34(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus BGR2NV21_31(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus BGR2GRAY_41(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus BGRA2BGR_43(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus GRAY2BGR_13(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus GRAY2BGR_14(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus NV212BGR_13(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus NV212RGB_13(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus NV122BGR_13(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus NV122RGB_13(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus YUV2GRAY_420_11(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus YUV4222GRAY_21(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus YUV4222BGR_23(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus GRAY162GRAY8_11(const FastcvDesc& src, const FastcvDesc& dst);
    // static MStatus RGBA2BGR_43(const FastcvDesc& src, const FastcvDesc& dst);

protected:
    ColorCvtParam* param_;

protected:
    // std::function<MStatus(const FastcvDesc&, const FastcvDesc&)> cvt_func_{nullptr};
};
} // namespace cv
#endif // SIMPLE_CV_COLOT_CONVERT_H_