#pragma once

#include "Image.h"

namespace image_processor::filters {
class Filter {
public:
    virtual void ApplyFilter(Image &image) const = 0;

    virtual ~Filter() = default;
};
}  // namespace image_processor::filters
