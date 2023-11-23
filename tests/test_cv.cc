#include <fstream>

#include "cvtColor.h"
#include "norm.h"
#include "resize.h"
#include "transform.h"
#include "utils/stb_image.h"
#include "utils/test_util.h"
#include "warpAffine.h"

#include <gtest/gtest.h>

#include <register.h>
class ImageTest : public ::testing::Test {
protected:
    void SetUp() override {
        uint32_t size = kWidth * kHeight * kChannel * sizeof(u_char);
        data          = malloc(size);
        if (read_binary_file(img_path, data, size) != 0) {
            std::cerr << "read " << img_path << " failed! size: " << size << std::endl;
            return;
        }
    }
    void TearDown() override { Test::TearDown(); }

    int kWidth           = 550;
    int kHeight          = 733;
    int kChannel         = 3;
    void* data           = nullptr;
    std::string img_path = "data/test_img.jpg";
};


TEST(ImageTest, Resize) {
    // auto transform = std::shared_ptr<cv::Transform>();
    // auto resize_op = cv::Transform::Create("Resize");
    // auto op = RegisterBase<cv::Transform>::GetInstance().Create("resize");
    // if (op->Init("ConvertTo", &param, sizeof(param), nullptr, true) !=
    // ADInference::MStatus::M_OK) {
    //     SDK_LOG_ERROR("ConvertToOp Init failed.");
    //     break;
    // }
}