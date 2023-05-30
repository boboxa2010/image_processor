#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor::filters {
class Threshold final : public ChannelWiseFilter {
public:
    explicit Threshold(double threshold) : threshold_(threshold) {
    }

protected:
    void FilterImpl(Image::Channel &channel) const override;

private:
    double threshold_;
};
}  // namespace image_processor::filters
