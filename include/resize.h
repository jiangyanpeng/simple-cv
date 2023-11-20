#ifndef SIMPLE_CV_RESIZE_H_
#define SIMPLE_CV_RESIZE_H_

#include "transform.h"

namespace cv {

class resize final : public Transform {
public:
    resize() {}
    ~resize() {}

    MStatus Init(const std::string& name,
                 const void* param,
                 const size_t param_len,
                 const void* context = nullptr,
                 const bool inplace  = false) override;

    MStatus Run(const std::shared_ptr<base::Image>& input,
                std::shared_ptr<base::Image>& output) override;

private:
    ResizeParam* param_;
};

} // namespace cv
#endif // SIMPLE_CV_RESIZE_H_