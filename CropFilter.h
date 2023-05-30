#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor::filters {
class CropFilter final : public ChannelWiseFilter {
public:
    CropFilter(size_t width, size_t height);

    ~CropFilter() override = default;

private:
    size_t new_width_;
    size_t new_height_;

protected:
    void FilterImpl(Image::Channel& channel) const override;
};
}  // namespace image_processor::filters