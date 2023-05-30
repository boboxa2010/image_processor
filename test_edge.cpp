#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "EdgeDetectionFilter.h"

namespace {
const double EPS = 0.01;
}  // namespace

TEST_CASE("Test_Edge") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    image_processor::filters::EdgeDetectionFilter edge_detection_filter(1.0);
    edge_detection_filter.ApplyFilter(image);

    image_processor::Image edge_image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_edge.bmp");

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& edge_image_channels = edge_image.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - edge_image_channels[k][i][j]) < EPS);
            }
        }
    }
}