#include "ConvFilter.h"

void image_processor::filters::ConvFilter::FilterImpl(Image::Channel& channel) const {
    Image::Channel curr_channel;
    curr_channel.resize(channel.size(), std::vector<double>(channel[0].size()));
    for (int32_t i = 0; i < static_cast<int32_t>(channel.size()); ++i) {
        for (int32_t j = 0; j < static_cast<int32_t>(channel[0].size()); ++j) {
            double new_color = 0;
            for (int32_t dy = -padding_; dy <= padding_; ++dy) {
                for (int32_t dx = -padding_; dx <= padding_; ++dx) {
                    new_color += channel[std::min(std::max(i + dy, 0), static_cast<int32_t>(channel.size()) - 1)]
                                        [std::min(std::max(j + dx, 0), static_cast<int32_t>(channel[0].size()) - 1)] *
                                 matrix_[dx + padding_][dy + padding_];
                }
            }
            curr_channel[i][j] = std::min(1.0, std::max(0.0, new_color));
        }
    }
    channel = std::move(curr_channel);
}

image_processor::filters::ConvFilter::ConvFilter(const std::vector<std::vector<float>>& matrix)
    : matrix_(matrix), padding_(static_cast<int32_t>(matrix.size()) / 2) {
}
