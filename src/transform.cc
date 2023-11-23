#include "transform.h"

#include <register.h>
#include <string.h>
namespace cv {
MStatus Transform::Init(const std::string& name,
                        const void* param,
                        const size_t param_len,
                        const void* context,
                        const bool inplace) {
    SIMPLE_LOG_DEBUG("Transform::Init Start");

    auto ret = MStatus::M_OK;
    do {
        op_name_ = name;
        if (nullptr != param && param_len > 0) {
            op_param_.resize(param_len);
            memcpy(op_param_.data(), param, param_len);
        }
        op_ctx_     = context;
        op_inplace_ = inplace;
    } while (0);

    SIMPLE_LOG_DEBUG("Transform::Init End");
}

std::shared_ptr<Transform> Transform::Create(const std::string& op_name) {
    SIMPLE_LOG_DEBUG("Transform::Create {}", op_name.c_str());
    return RegisterBase<Transform>::GetInstance().Create(op_name);
}

MStatus Transform::ParamCheck(const std::vector<uint8_t>& param,
                              const size_t expect_param_size,
                              const std::string& prefix) {
    if (param.size() != expect_param_size) {
        SIMPLE_LOG_ERROR(
            "{} check paramters failed, {}vs{}", prefix.c_str(), param.size(), expect_param_size);
        return MStatus::M_INVALID_ARG;
    }
    return MStatus::M_OK;
}

} // namespace cv
