#include "transform.h"

#include "cv_api.h"
#include <iostream>
#include <log.h>

int main() {
    auto op = RegisterBase<cv::Transform>::GetInstance().Create(RESIZE);
    ResizeParam param{
        .type   = ResizeParam::LINEAR,
        .height = 320,
        .width  = 270,
    };
    return 0;
}