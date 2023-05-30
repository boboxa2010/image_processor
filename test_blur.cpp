#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "Blur.h"

namespace {
const double EPS = 0.01;
const double SIGMA = 10.0;
}  // namespace

TEST_CASE("Test_Blur") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::Blur blur(SIGMA);
    blur.ApplyFilter(image);

    image_processor::Image blur_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_blur.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& blur_image_channels = blur_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - blur_image_channels[k][i][j]) < EPS);
            }
        }
    }
}