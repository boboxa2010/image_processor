#include "NegativeFilter.h"

namespace image_processor::filters {
NegativeFilter::~NegativeFilter() = default;

void NegativeFilter::FilterImpl(Image::Channel &channel) const {
    for (auto &row : channel) {
        for (auto &el : row) {
            el = 1 - el;
        }
    }
}
}  // namespace image_processor::filters