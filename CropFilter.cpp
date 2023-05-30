#include "CropFilter.h"

image_processor::filters::CropFilter::CropFilter(size_t width, size_t height) : new_width_(width), new_height_(height) {
}

void image_processor::filters::CropFilter::FilterImpl(image_processor::Image::Channel &channel) const {
    if (new_height_ > channel.size() || new_width_ > channel[0].size() || new_height_ < 0 || new_width_ < 0) {
        return;
    }
    for (auto &row : channel) {
        row.resize(new_width_);
    }
    channel.resize(new_height_);
}
