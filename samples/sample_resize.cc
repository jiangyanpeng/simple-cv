#include "transform.h"

#include <iostream>
#include <log.h>
#include <register.h>
int main() {
    // std::cout << " hello cv " << std::endl;
    auto transform = std::shared_ptr<cv::Transform>();
    SIMPLE_LOG_DEBUG("hello world");
    // auto op = RegisterBase<cv::Transform>::GetInstance().Create("resize");
    return 0;
}