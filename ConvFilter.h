#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor::filters {
class ConvFilter : public ChannelWiseFilter {
public:
    ~ConvFilter() override = default;

    explicit ConvFilter(const std::vector<std::vector<float>> &matrix);

protected:
    void FilterImpl(Image::Channel &channel) const final;

private:
    std::vector<std::vector<float>> matrix_;
    int32_t padding_;
};
}  // namespace image_processor::filters