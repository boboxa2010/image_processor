#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor::filters {
class Blur : public ChannelWiseFilter {
public:
    explicit Blur(double sigma);

    ~Blur() override;

protected:
    void FilterImpl(Image::Channel &channel) const override;

private:
    void MakeKernel(double sigma);

    std::vector<double> kernel_;
};
}  // namespace image_processor::filters
