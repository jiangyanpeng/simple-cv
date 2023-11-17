#include "cvtColor.h"

namespace cv {
MStatus cvtColor::Init(const std::string& name,
                       const void* param,
                       const size_t param_len,
                       const void* context,
                       const bool inplace) {
    SIMPLE_LOG_DEBUG("cvtColor::Init Start");
    MStatus ret = MStatus::M_OK;
    do {
        ret = Transform::Init(name, param, param_len, context, inplace);
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("cvtColor::Init failed, ret = {}", MStatusStr[ret].c_str());
            break;
        }

        ret = Transform::ParamCheck(op_param_, sizeof(ColorCvtParam), "cvtColor::Init");
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("cvtColor::Init failed, ret = {}", MStatusStr[ret].c_str());
            break;
        }
        param_ = reinterpret_cast<ColorCvtParam*>(op_param_.data());
    } while (0);
    SIMPLE_LOG_DEBUG("cvtColor::Init End");
    return ret;
}

MStatus cvtColor::Run(const std::shared_ptr<base::Image>& input,
                      std::shared_ptr<base::Image>& output) {
    SIMPLE_LOG_DEBUG("cvtColor::Run Start");
    MStatus ret = MStatus::M_OK;
    do {
        if (input->GetPixelFormat() == static_cast<PixelFormat>(param_->convect_type)) {
            output = input;
            break;
        }
        auto dst_format = static_cast<PixelFormat>(param_->convect_type);
        if (op_inplace_) {
            output = std::make_shared<base::Image>(*(input.get()), dst_format);
        } else {
            output = std::make_shared<base::Image>(input->GetWidth(),
                                                   input->GetHeight(),
                                                   input->GetNumber(),
                                                   dst_format,
                                                   input->GetTimestamp(),
                                                   input->GetMemType());
        }
        if (nullptr != output) {
            SIMPLE_LOG_ERROR("cvtColor::Run malloc memory failed");
            ret = MStatus::M_INTERNAL_FAILED;
            break;
        }

    } while (0);
    SIMPLE_LOG_DEBUG("cvtColor::Run End");
    return ret;
}

} // namespace cv