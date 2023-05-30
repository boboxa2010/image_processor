#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "Crystallize.h"

namespace {
const double EPS = 0.01;
const size_t CRYSTALS_QUANTITY = 1000;
}  // namespace

TEST_CASE("Test_Crystallized") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::Crystallize crystallize_filter(CRYSTALS_QUANTITY);
    crystallize_filter.ApplyFilter(image);

    image_processor::Image crystallized_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_crystall.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& crystallized_image_channels = crystallized_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - crystallized_image_channels[k][i][j]) < EPS);
            }
        }
    }
}