#pragma once

#include "Filter.h"

namespace image_processor::filters {
class ChannelWiseFilter : public Filter {
public:
    ~ChannelWiseFilter() override;

    void ApplyFilter(Image &image) const final;

protected:
    virtual void FilterImpl(Image::Channel &channel) const = 0;
};
}  // namespace image_processor::filters