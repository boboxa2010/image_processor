#pragma once

#include "ConvFilter.h"

namespace {
const std::vector<std::vector<float>> SHARP_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
}

namespace image_processor::filters {
class SharpeningFilter final : public ConvFilter {
public:
    SharpeningFilter() : ConvFilter(SHARP_MATRIX) {
    }
};
}  // namespace image_processor::filters
