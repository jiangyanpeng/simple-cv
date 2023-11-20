#ifndef SIMPLE_CV_NORM_H_
#define SIMPLE_CV_NORM_H_

#include "transform.h"

namespace cv {

class norm final : public Transform {
public:
    norm() {}
    ~norm() {}

    MStatus Init(const std::string& name,
                 const void* param,
                 const size_t param_len,
                 const void* context = nullptr,
                 const bool inplace  = false) override;

    MStatus Run(const std::shared_ptr<base::Image>& input,
                std::shared_ptr<base::Image>& output) override;

private:
    NormParam* param_;
};

} // namespace cv
#endif // SIMPLE_CV_NORM_H_