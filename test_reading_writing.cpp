#include <catch.hpp>

#include "BMP.h"
#include "Image.h"

namespace {
const double EPS = 0.01;
}

TEST_CASE("Reading File: invalid format of reading file") {
    REQUIRE_THROWS_AS(
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/invalid_format.txt"),
        std::invalid_argument);
}

TEST_CASE("Reading File: trying to read non-existent file") {
    REQUIRE_THROWS_AS(
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/non_existent_file.bmp"),
        std::invalid_argument);
}

TEST_CASE("Writing File") {

    // reading file
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");

    // writing file
    image_processor::bmp::Write("../tasks/image_processor/test_script/data/examples/shrek_copy.bmp", image);

    // reading copy
    image_processor::Image image_copy =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek_copy.bmp");

    // checking equality of images;
    if (image.GetHeight() != image_copy.GetHeight() || image.GetWidth() != image_copy.GetWidth()) {
        REQUIRE_FALSE(true);
    }

    const std::vector<image_processor::Image::Channel>& image_channels = image.GetChannels();
    const std::vector<image_processor::Image::Channel>& image_copy_channels = image_copy.GetChannels();
    for (size_t k = 0; k < image_channels.size(); ++k) {
        for (size_t i = 0; i < image_channels[k].size(); ++i) {
            for (size_t j = 0; j < image_channels[k][0].size(); ++j) {
                REQUIRE(std::abs(image_channels[k][i][j] - image_copy_channels[k][i][j]) < EPS);
            }
        }
    }
}