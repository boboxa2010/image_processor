#include "Image.h"

namespace image_processor {

Image::Image() = default;

Image::Image(size_t number_of_channels, size_t width, size_t height)
    : channels_(std::vector<Channel>(number_of_channels, Channel(height, std::vector<double>(width, 0)))) {
}

size_t Image::GetWidth() const {
    return channels_[0][0].size();
}

size_t Image::GetHeight() const {
    return channels_[0].size();
}

Image::Pixel Image::GetPixel(size_t x, size_t y) const {
    if (channels_.size() == 1) {
        return {.r = channels_[0][y][x], .g = channels_[0][y][x], .b = channels_[0][y][x]};
    }
    return {.r = channels_[0][y][x], .g = channels_[1][y][x], .b = channels_[2][y][x]};
}

void Image::SetPixel(size_t x, size_t y, double r, double g, double b) {
    if (channels_.size() == 1) {
        channels_.push_back(Channel(this->GetHeight(), std::vector<double>(this->GetWidth(), 0)));
        channels_.push_back(Channel(this->GetHeight(), std::vector<double>(this->GetWidth(), 0)));
    }
    channels_[0][y][x] = r;
    channels_[1][y][x] = g;
    channels_[2][y][x] = b;
}

std::vector<Image::Channel>& Image::GetChannels() {
    return channels_;
}
}  // namespace image_processor