#pragma once

#include "CompositeFilter.h"
#include "GrayscaleFilter.h"
#include "ConvFilter.h"
#include "Threshold.h"

namespace image_processor::filters {
class EdgeDetectionFilter final : public CompositeFilter {
public:
    explicit EdgeDetectionFilter(double threshold);
};
}  // namespace image_processor::filters