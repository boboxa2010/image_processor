#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "SharpeningFilter.h"

namespace {
const double EPS = 0.01;
}

TEST_CASE("Test_Sharp") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::SharpeningFilter sharp_filter;
    sharp_filter.ApplyFilter(image);

    image_processor::Image sharp_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_sharp.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& sharp_image_channels = sharp_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - sharp_image_channels[k][i][j]) < EPS);
            }
        }
    }
}
