#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "NegativeFilter.h"

namespace {
const double EPS = 0.01;
}

TEST_CASE("Test_Negative") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::NegativeFilter negative_filter;
    negative_filter.ApplyFilter(image);

    image_processor::Image negative_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_negative.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& negative_image_channels = negative_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - negative_image_channels[k][i][j]) < EPS);
            }
        }
    }
}
