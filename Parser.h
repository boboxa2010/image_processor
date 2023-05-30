#pragma once

#include <memory>
#include <filesystem>

#include "Filter.h"

namespace image_processor::cli {
enum class FilterName { Crop, Grayscale, Blur, Negative, EdgeDetection, Sharpening, Crystallize };

struct FilterRepresentation {
    FilterName name;
    std::vector<std::string_view> parameters;
};

class Parser final {
public:
    void Parse(size_t args_count, char** args_value);

    std::filesystem::path GetInputFileName() const;

    std::filesystem::path GetOutputFileName() const;

    void GetFiltersFromParser(std::vector<std::unique_ptr<filters::Filter>>& filters) const;

    bool IsHelp() const;

private:
    std::filesystem::path input_file_name_;
    std::filesystem::path output_file_name_;
    bool help_flag_ = false;
    std::vector<FilterRepresentation> filters_pipline_;
};
}  // namespace image_processor::cli
