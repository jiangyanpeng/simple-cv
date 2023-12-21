#include "norm.h"
#include "cv/c_api.h"

namespace cv {
MStatus norm::Init(const std::string& name,
                   const void* param,
                   const size_t param_len,
                   const void* context,
                   const bool inplace) {
    SIMPLE_LOG_DEBUG("norm::Init Start\n");
    MStatus ret = MStatus::M_OK;
    do {
        ret = Transform::Init(name, param, param_len, context, inplace);
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("norm::Init failed, ret = %s\n", MStatusStr[ret].c_str());
            break;
        }

        ret = Transform::ParamCheck(op_param_, sizeof(NormParam), "norm::Init");
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("norm::Init failed, ret = %s\n", MStatusStr[ret].c_str());
            break;
        }
        param_ = reinterpret_cast<NormParam*>(op_param_.data());
    } while (0);
    SIMPLE_LOG_DEBUG("norm::Init End\n");
    return ret;
}

MStatus norm::Run(const std::shared_ptr<base::Image>& input, std::shared_ptr<base::Image>& output) {
    SIMPLE_LOG_DEBUG("norm::Run Start\n");
    MStatus ret = MStatus::M_OK;
    do {

        PixelFormat dst = M_PIX_FMT_GRAY32;
        switch (input->GetPixelFormat()) {
            case M_PIX_FMT_GRAY8:
                dst = M_PIX_FMT_GRAY32;
                break;
            case M_PIX_FMT_RGB888:
                dst = M_PIX_FMT_RGB323232;
                break;
            case M_PIX_FMT_BGR888:
                dst = M_PIX_FMT_BGR323232;
                break;
            default:
                SIMPLE_LOG_ERROR("norm::Run not support format %s\n",
                                 FormatStr[input->GetPixelFormat()]);
                break;
        }

        SIMPLE_LOG_DEBUG(
            "norm::Run %s norm to %s\n", FormatStr[input->GetPixelFormat()], FormatStr[dst]);
        output = std::make_shared<base::Image>(input->GetWidth(),
                                               input->GetHeight(),
                                               input->GetNumber(),
                                               dst,
                                               input->GetTimestamp(),
                                               input->GetMemType());
        switch (input->GetChannel()) {
            case 1:
                /* code */
                break;
            case 3:
                normalize_8uc3_packed(input->GetData<uint8_t>(0),
                                      input->GetWidth(),
                                      input->GetHeight(),
                                      param_->mean,
                                      param_->std,
                                      output->GetData<float>(0));
            default:
                break;
        }
    } while (0);
    SIMPLE_LOG_DEBUG("norm::Run End\n");
    return ret;
}
} // namespace cv