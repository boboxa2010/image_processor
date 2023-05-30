#include "CompositeFilter.h"

void image_processor::filters::CompositeFilter::ApplyFilter(Image &image) const {
    for (const auto &filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void image_processor::filters::CompositeFilter::AddFilter(std::unique_ptr<Filter> filter_ptr) {
    filters_.push_back(std::move(filter_ptr));
}

image_processor::filters::CompositeFilter::CompositeFilter(std::vector<std::unique_ptr<Filter>> filters)
    : filters_(std::move(filters)) {
}
image_processor::filters::CompositeFilter::CompositeFilter() = default;
