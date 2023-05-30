#include "Threshold.h"

namespace {
const double BLACK = 1.0;
const double WHITE = 0.0;
}  // namespace

namespace image_processor::filters {
void Threshold::FilterImpl(Image::Channel &channel) const {
    for (std::vector<double> &row : channel) {
        for (double &el : row) {
            if (el > threshold_) {
                el = BLACK;
            } else {
                el = WHITE;
            }
        }
    }
}
}  // namespace image_processor::filters