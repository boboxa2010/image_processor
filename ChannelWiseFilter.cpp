#include "ChannelWiseFilter.h"

void image_processor::filters::ChannelWiseFilter::ApplyFilter(Image &image) const {
    for (auto &channel : image.GetChannels()) {
        FilterImpl(channel);
    }
}

image_processor::filters::ChannelWiseFilter::~ChannelWiseFilter() = default;
