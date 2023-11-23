#include "transform.h"

#include "cv_api.h"
#include <iostream>
#include <log.h>

int main() {
    base::Image iamge;
    auto op = RegisterBase<cv::Transform>::GetInstance().Create("resize");
    return 0;
}