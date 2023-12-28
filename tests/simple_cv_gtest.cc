#include "cv_api.h"
#include "utils/stb_image.h"
#include "utils/test_util.h"

#include <fstream>
#include <gtest/gtest.h>
#include <log.h>
class ImageTest : public ::testing::Test {
protected:
    void SetUp() override {
#ifdef CONFIG_SIMPLE_BASE_ENABLE_SPDLOG
        close_level();
#endif
        uint32_t size = kWidth * kHeight * kChannel * sizeof(u_char);
        data          = malloc(size);
        if (read_binary_file(img_path, data, size) != 0) {
            std::cerr << "read " << img_path << " failed! size: " << size << std::endl;
            return;
        }
        TimeStamp time_stamp{};
        image = std::make_shared<base::Image>(kWidth, kHeight, 1, format, time_stamp, data);
    }
    void TearDown() override { Test::TearDown(); }

    int kWidth           = 550;
    int kHeight          = 733;
    int kChannel         = 3;
    void* data           = nullptr;
    PixelFormat format   = PixelFormat::M_PIX_FMT_BGR888;
    std::string img_path = "data/test_img.jpg";
    std::shared_ptr<base::Image> image{nullptr};
};


TEST_F(ImageTest, Transform_Resize) {
    auto op = RegisterBase<cv::Transform>::GetInstance().Create(RESIZE);
    ResizeParam param{
        .type   = ResizeParam::LINEAR,
        .height = 320,
        .width  = 270,
    };
    EXPECT_EQ(op->Init(RESIZE, &param, sizeof(param), nullptr, true), MStatus::M_OK);
    EXPECT_NE(image, nullptr);
}