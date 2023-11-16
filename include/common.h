#ifndef SIMPLE_CV_COMMON_H_
#define SIMPLE_CV_COMMON_H_
namespace cv {

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wpacked"
#endif
#if defined(__linux__) || defined(__android__) || defined(__QNX__) || defined(__GNUC__)
#define PACKED_STRUCT(...) typedef struct __attribute__((__packed__)) __VA_ARGS__;
#else
#define PACKED_STRUCT(...)                              \
    __pragma(pack(push, 1)) typedef struct __VA_ARGS__; \
    __pragma(pack(pop))
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

} // namespace cv
#endif // SIMPLE_CV_COMMON_H_