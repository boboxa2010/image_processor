#pragma once

#include "Filter.h"
#include <memory>

namespace image_processor::filters {
class CompositeFilter : public Filter {
public:
    ~CompositeFilter() override = default;

    explicit CompositeFilter(std::vector<std::unique_ptr<Filter>> filters);

    void ApplyFilter(Image &image) const final;

protected:
    CompositeFilter();

    void AddFilter(std::unique_ptr<Filter> filter_ptr);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
}  // namespace image_processor::filters