#pragma once

#include <vector>

namespace image_processor {
class Image final {
public:
    using Channel = std::vector<std::vector<double>>;

    struct Pixel {
        const double& r;
        const double& g;
        const double& b;
    };

    Image();

    Image(size_t number_of_channels, size_t width, size_t height);

    size_t GetWidth() const;

    size_t GetHeight() const;

    Pixel GetPixel(size_t x, size_t y) const;

    void SetPixel(size_t x, size_t y, double r, double g, double b);

    std::vector<Channel>& GetChannels();

private:
    std::vector<Channel> channels_;
};
}  // namespace image_processor