#include "EdgeDetectionFilter.h"

image_processor::filters::EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : CompositeFilter() {
    AddFilter(std::make_unique<GrayscaleFilter>());
    AddFilter(std::make_unique<ConvFilter>(std::vector<std::vector<float>>{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}));
    AddFilter(std::make_unique<Threshold>(threshold));
}
