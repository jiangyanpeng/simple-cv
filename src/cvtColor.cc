#include "cvtColor.h"
#include "cv/c_api.h"
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
            SIMPLE_LOG_ERROR("cvtColor::Init failed, ret = %s", MStatusStr[ret].c_str());
            break;
        }

        ret = Transform::ParamCheck(op_param_, sizeof(ColorCvtParam), "cvtColor::Init");
        if (ret != MStatus::M_OK) {
            SIMPLE_LOG_ERROR("cvtColor::Init failed, ret = %s", MStatusStr[ret].c_str());
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

        switch (param_->convect_type) {
            case ColorCvtParam::BGR2NV21:
                SIMPLE_LOG_ERROR("cvtColor::Run not support BGR2NV21");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::NV212BGR:
                SIMPLE_LOG_ERROR("cvtColor::Run not support NV212BGR");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::RGB2NV21:
                SIMPLE_LOG_ERROR("cvtColor::Run not support RGB2NV21");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::RGB2NV12:
                SIMPLE_LOG_ERROR("cvtColor::Run not support RGB2NV12");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::NV122RGB:
                SIMPLE_LOG_ERROR("cvtColor::Run not support NV122RGB");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGR2NV12:
                convert_yuv420sp_to_rgb_packed(input->GetData<uint8_t>(0),
                                               input->GetWidth(),
                                               input->GetHeight(),
                                               output->GetData<uint8_t>(0));
                break;
            case ColorCvtParam::NV122BGR:
                SIMPLE_LOG_ERROR("cvtColor::Run not support NV122BGR");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGR2GRAY:
                convert_bgr_to_gray_packed(input->GetData<uint8_t>(0),
                                           input->GetWidth(),
                                           input->GetHeight(),
                                           input->GetStride(),
                                           output->GetData<uint8_t>(0),
                                           false);
                break;
            case ColorCvtParam::GRAY2BGR:
                SIMPLE_LOG_ERROR("cvtColor::Run not support GRAY2BGR");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGR2BGRA:
                SIMPLE_LOG_ERROR("cvtColor::Run not support BGR2BGRA");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGRA2BGR:
                SIMPLE_LOG_ERROR("cvtColor::Run not support BGRA2BGR");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::RGB2GRAY:
                convert_bgr_to_gray_packed(input->GetData<uint8_t>(0),
                                           input->GetWidth(),
                                           input->GetHeight(),
                                           input->GetStride(),
                                           output->GetData<uint8_t>(0),
                                           true);
                break;
            case ColorCvtParam::GRAY2RGB:
                SIMPLE_LOG_ERROR("cvtColor::Run not support GRAY2RGB");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGR2RGB:
            case ColorCvtParam::RGB2BGR:
                convert_bgr_to_rgb_packed(input->GetData<uint8_t>(0),
                                          input->GetWidth(),
                                          input->GetHeight(),
                                          input->GetStride(),
                                          output->GetData<uint8_t>(0));
                break;
            case ColorCvtParam::RGB2YV12:
                SIMPLE_LOG_ERROR("cvtColor::Run not support RGB2BGR");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::BGR2YV12:
                SIMPLE_LOG_ERROR("cvtColor::Run not support BGR2YV12");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::YUV2GRAY_420:
                SIMPLE_LOG_ERROR("cvtColor::Run not support YUV2GRAY_420");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::NV122NV21:
                SIMPLE_LOG_ERROR("cvtColor::Run not support NV122NV21");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            case ColorCvtParam::NV212NV12:
                SIMPLE_LOG_ERROR("cvtColor::Run not support NV212NV12");
                ret = MStatus::M_NOT_SUPPORT;
                break;
            default:
                ret = MStatus::M_NOT_SUPPORT;
                break;
        }
    } while (0);
    SIMPLE_LOG_DEBUG("cvtColor::Run End");
    return ret;
}

} // namespace cv