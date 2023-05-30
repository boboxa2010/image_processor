#include <stdexcept>

#include "GrayscaleFilter.h"

namespace {
const double RED_COEFFICIENT = 0.299;
const double GREEN_COEFFICIENT = 0.587;
const double BLUE_COEFFICIENT = 0.114;
double MakeGray(const image_processor::Image::Pixel& pixel) {
    return pixel.r * RED_COEFFICIENT + pixel.g * GREEN_COEFFICIENT + pixel.b * BLUE_COEFFICIENT;
}
}  // namespace

void image_processor::filters::GrayscaleFilter::ApplyFilter(Image& image) const {
    std::vector<Image::Channel>& image_channels = image.GetChannels();

    if (image_channels.size() == 1) {
        return;
    } else if (image_channels.size() == 3) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                image_channels[0][y][x] =
                    MakeGray({image_channels[0][y][x], image_channels[1][y][x], image_channels[2][y][x]});
                ;
            }
        }
        image_channels.pop_back();
        image_channels.pop_back();
    } else {
        throw std::invalid_argument("Invalid numbers of colors in image");
    }
}
