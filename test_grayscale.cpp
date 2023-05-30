#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "GrayscaleFilter.h"

namespace {
const double EPS = 0.01;
}

TEST_CASE("Test_GrayScale") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::GrayscaleFilter grayscale_filter;
    grayscale_filter.ApplyFilter(image);

    image_processor::Image grayscale_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_grayscale.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& grayscale_image_channels = grayscale_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - grayscale_image_channels[k][i][j]) < EPS);
            }
        }
    }
}