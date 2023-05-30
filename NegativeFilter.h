#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor::filters {
class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override;

protected:
    void FilterImpl(Image::Channel &channel) const override;
};
}  // namespace image_processor::filters