#include "Blur.h"
#include <cmath>
#include <numbers>

namespace {
double GaussFunc(double sigma, double x) {
    return std::exp(-(x * x) / (2 * sigma * sigma)) / (2 * std::numbers::pi * sigma * sigma);
}
}  // namespace

image_processor::filters::Blur::~Blur() = default;

image_processor::filters::Blur::Blur(double sigma) {
    MakeKernel(sigma);
}
void image_processor::filters::Blur::FilterImpl(image_processor::Image::Channel &channel) const {
    Image::Channel tmp_channel;
    int32_t radius = static_cast<int32_t>(kernel_.size()) / 2;
    tmp_channel.resize(channel.size(), std::vector<double>(channel[0].size(), 0));
    for (int32_t y = 0; y < static_cast<int32_t>(channel.size()); ++y) {
        for (int32_t x = 0; x < static_cast<int32_t>(channel[0].size()); ++x) {
            double new_color = 0;
            for (int32_t delta = -radius; delta <= radius; ++delta) {
                new_color += channel[std::min(std::max(y + delta, 0), static_cast<int32_t>(channel.size()) - 1)][x] *
                             kernel_[delta + radius];
            }
            tmp_channel[y][x] += new_color;
        }
    }

    for (int32_t y = 0; y < static_cast<int32_t>(channel.size()); ++y) {
        for (int32_t x = 0; x < static_cast<int32_t>(channel[0].size()); ++x) {
            channel[y][x] = 0;
            for (int32_t delta = -radius; delta <= radius; ++delta) {
                channel[y][x] +=
                    tmp_channel[y][std::min(std::max(x + delta, 0), static_cast<int32_t>(channel[0].size()) - 1)] *
                    kernel_[delta + radius];
            }
        }
    }
}
void image_processor::filters::Blur::MakeKernel(double sigma) {
    const int32_t radius = static_cast<int32_t>(std::ceil(2 * sigma)) | 1;
    kernel_.resize(2 * radius + 1);
    double whole_sum = 0;
    for (int32_t delta = -radius; delta <= radius; ++delta) {
        kernel_[delta + radius] = GaussFunc(sigma, delta);
        whole_sum += kernel_[delta + radius];
    }
    for (size_t i = 0; i < kernel_.size(); ++i) {
        kernel_[i] /= whole_sum;
    }
}
