#include <catch.hpp>

#include "Image.h"
#include "BMP.h"
#include "CropFilter.h"

namespace {
const size_t SHREK_WIDTH = 700;
const size_t SHREK_HEIGHT = 422;
const size_t CROPPED_SHREK_WIDTH = 6;
const size_t CROPPED_SHREK_HEIGHT = 400;
const size_t BIG_WIDTH = 1000;
const size_t BIG_HEIGHT = 1000;
const size_t VALID_WIDTH = 6;
const size_t VALID_HEIGHT = 400;

}  // namespace

TEST_CASE("Test_Crop_Bigger_Dimension") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");
    image_processor::filters::CropFilter crop_filter_a(BIG_WIDTH, BIG_HEIGHT);
    crop_filter_a.ApplyFilter(image);
    REQUIRE(image.GetWidth() == SHREK_WIDTH);
    REQUIRE(image.GetHeight() == SHREK_HEIGHT);
}

TEST_CASE("Test_Crop_Valid_Dimension") {
    image_processor::Image image =
        image_processor::bmp::Read("../tasks/image_processor/test_script/data/examples/shrek.bmp");
    image_processor::filters::CropFilter crop_filter_c(VALID_WIDTH, VALID_HEIGHT);
    crop_filter_c.ApplyFilter(image);
    REQUIRE(image.GetWidth() == CROPPED_SHREK_WIDTH);
    REQUIRE(image.GetHeight() == CROPPED_SHREK_HEIGHT);
}
