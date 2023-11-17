#ifndef SIMPLE_CV_TRANSFORM_H_
#define SIMPLE_CV_TRANSFORM_H_

#include "paramter.h"

#include <common.h>
#include <image/image.h>

#include <memory>
#include <vector>

namespace cv {
class Transform {
public:
    Transform() {}
    virtual ~Transform() {}

    ///@brief  if you compile simple.cv into a static library, that may cause the operator to be
    /// unregistered,To solve this problem:
    ///@note
    /// case 1: If you want to register all operators
    ///       mothod 1: use  -Wl,--whole-archive for compilation options
    ///       mothod 2: call  RegisterAllOps()
    /// case 2: If you want to register partial operators
    ///       (1) include "XXXX.h" and Use its functions directly
    ///       (2) include "XXXX.h" and use REGISTER_COMMON_ENGINE,then create op
    static void RegisterOps() {}

    ///@brief  API to inflate registered OP
    ///@return nullptr if fail
    static std::shared_ptr<Transform> Create(const std::string& op_name);

    ///@brief  Only execute once, init with param,etc load kernel into memory,
    virtual MStatus Init(const std::string& name,
                         const void* param,
                         const size_t param_len,
                         const void* context = nullptr,
                         const bool inplace  = false);
    ///@brief prepare when first  run ,etc calculate outputs tensor shape
    ///@brief input :  op input data
    ///@brief output : if "inplace" set, Output tensor with memory allocation
    ///@brief          otherwise , output tensor without memory allocation
    ///@brief context:  for cuda/ocl queue / hexagon pipeline
    ///@brief run ops / laurch kennel
    virtual MStatus Run(const std::shared_ptr<base::Image>& inputs,
                        std::shared_ptr<base::Image>& outputs) = 0;

    ///@brief  get/set  op info
    inline OpType GetOpType() { return op_type_; }
    inline std::string& GetOpName() { return op_name_; }
    inline std::vector<uint8_t>& GetOpParam() { return op_param_; }

protected:
    MStatus ParamCheck(const std::vector<uint8_t>& param,
                       const size_t expect_param_size,
                       const std::string& prefix);

protected:
    OpType op_type_{OpType::None};
    std::string op_name_{"unset"};
    const void* op_ctx_{nullptr};
    std::vector<uint8_t> op_param_;
    bool op_prepared_{false};
    bool op_inplace_{true};

    bool can_inplace_{false};
};

} // namespace cv
#endif // SIMPLE_CV_TRANSFORM_H_