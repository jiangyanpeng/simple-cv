#include "resize.h"
#include "cv/c_api.h"

namespace cv {
MStatus resize::Init(const std::string& name,
                     const void* param,
                     const size_t param_len,
                     const void* context,
                     const bool inplace) {
    SIMPLE_LOG_DEBUG("resize::Init Start");
    MStatus ret = MStatus::M_OK;
    do {
        ret = Transform::Init(name, param, param_len, context, inplace);
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("resize::Init failed, ret = {}", MStatusStr[ret].c_str());
            break;
        }

        ret = Transform::ParamCheck(op_param_, sizeof(ResizeParam), "resize::Init");
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("resize::Init failed, ret = {}", MStatusStr[ret].c_str());
            break;
        }
        param_ = reinterpret_cast<ResizeParam*>(op_param_.data());
    } while (0);
    SIMPLE_LOG_DEBUG("resize::Init End");
    return ret;
}

MStatus resize::Run(const std::shared_ptr<base::Image>& input,
                    std::shared_ptr<base::Image>& output) {
    SIMPLE_LOG_DEBUG("resize::Run Start");
    MStatus ret = MStatus::M_OK;
    do {
        if (op_inplace_ && [](uint32_t in_size, uint32_t out_size) -> bool {
                return in_size >= out_size;
            }(input->GetWidth() * input->GetHeight(), param_->height * param_->width)) {
            output = std::make_shared<base::Image>(*(input.get()), input->GetPixelFormat());
        } else {
            uint32_t in_width  = param_->width;
            uint32_t in_height = param_->height;
            output             = std::make_shared<base::Image>(in_width,
                                                   in_height,
                                                   input->GetNumber(),
                                                   input->GetPixelFormat(),
                                                   input->GetTimestamp(),
                                                   input->GetMemType());
        }
        if (nullptr != output) {
            SIMPLE_LOG_ERROR("resize::Run malloc memory failed");
            ret = MStatus::M_INTERNAL_FAILED;
            break;
        }
        if (param_->type != ResizeParam::LINEAR) {
            SIMPLE_LOG_ERROR("resize::Run not support {}", static_cast<int>(param_->type));
            ret = MStatus::M_NOT_SUPPORT;
            break;
        }

        if (input->GetPixelFormat() != M_PIX_FMT_NV12 ||
            input->GetPixelFormat() != M_PIX_FMT_NV21 ||
            input->GetPixelFormat() != M_PIX_FMT_YUYV ||
            input->GetPixelFormat() != M_PIX_FMT_UYVY ||
            input->GetPixelFormat() != M_PIX_FMT_YV12 ||
            input->GetPixelFormat() != M_PIX_FMT_YU12) {
            switch (input->GetChannel()) {
                case 1:
                    resize_bilinear_c1(input->GetData<uint8_t>(0),
                                       input->GetWidth(),
                                       input->GetHeight(),
                                       output->GetData<uint8_t>(0),
                                       output->GetWidth(),
                                       output->GetHeight());
                    break;
                case 2:
                    resize_bilinear_c2(input->GetData<uint8_t>(0),
                                       input->GetWidth(),
                                       input->GetHeight(),
                                       output->GetData<uint8_t>(0),
                                       output->GetWidth(),
                                       output->GetHeight());
                    break;
                case 3:
                    resize_bilinear_c3(input->GetData<uint8_t>(0),
                                       input->GetWidth(),
                                       input->GetHeight(),
                                       output->GetData<uint8_t>(0),
                                       output->GetWidth(),
                                       output->GetHeight());
                    break;
                case 4:
                    resize_bilinear_c4(input->GetData<uint8_t>(0),
                                       input->GetWidth(),
                                       input->GetHeight(),
                                       output->GetData<uint8_t>(0),
                                       output->GetWidth(),
                                       output->GetHeight());
                    break;
                default:
                    SIMPLE_LOG_ERROR("resize::Run not support channel {}", input->GetChannel());
                    ret = MStatus::M_NOT_SUPPORT;
                    break;
            }
        } else {
            resize_bilinear_yuv420sp(input->GetData<uint8_t>(0),
                                     input->GetWidth(),
                                     input->GetHeight(),
                                     output->GetData<uint8_t>(0),
                                     output->GetWidth(),
                                     output->GetHeight());
        }
    } while (0);
    SIMPLE_LOG_DEBUG("resize::Run End");
    return ret;
}

} // namespace cv