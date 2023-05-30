#pragma once

#include "Filter.h"

namespace image_processor::filters {
class Crystallize final : public Filter {
public:
    explicit Crystallize(size_t crystals_quantity);

    ~Crystallize() override = default;

    void ApplyFilter(Image& image) const final;

private:
    size_t FindClosestCrystal(const std::vector<size_t>& new_x, const std::vector<size_t>& new_y, size_t curr_height,
                              size_t curr_width) const;

    size_t crystals_quantity_;
};
}  // namespace image_processor::filters
