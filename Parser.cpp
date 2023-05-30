#include <stdexcept>
#include <unordered_map>

#include "NegativeFilter.h"
#include "GrayscaleFilter.h"
#include "CropFilter.h"
#include "EdgeDetectionFilter.h"
#include "SharpeningFilter.h"
#include "Crystallize.h"
#include "Parser.h"
#include "Blur.h"

namespace {
bool IsUint(std::string_view str) {
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

bool IsUnsignedDouble(std::string_view str) {
    auto it = str.begin();
    while (it != str.end() && (std::isdigit(*it) || *it == '.')) {
        it++;
    }
    return !str.empty() && it == str.end();
}

bool IsInt(std::string_view str) {
    auto it = str.begin();
    while (it != str.end() && (std::isdigit(*it) || *it == '-')) {
        it++;
    }
    return !str.empty() && it == str.end();
}

bool IsDouble(std::string_view str) {
    auto it = str.begin();
    while (it != str.end() && (std::isdigit(*it) || *it == '.' || *it == '-')) {
        it++;
    }
    return !str.empty() && it == str.end();
}

void CheckFileExistence(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("File or path does not exist " + path.string());
    }
}

void CheckPathExistence(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path.parent_path())) {
        throw std::invalid_argument("File or path does not exist " + path.string());
    }
}

const size_t MIN_VALID_PARAMETERS_NUMBER = 2;

const size_t INPUT_FILE_INDEX = 1;

const size_t OUTPUT_FILE_INDEX = 2;

const std::unordered_map<std::string, image_processor::cli::FilterName> STRING_TO_FILTER_NAME = {
    {"-crop", image_processor::cli::FilterName::Crop},
    {"-gs", image_processor::cli::FilterName::Grayscale},
    {"-neg", image_processor::cli::FilterName::Negative},
    {"-sharp", image_processor::cli::FilterName::Sharpening},
    {"-edge", image_processor::cli::FilterName::EdgeDetection},
    {"-blur", image_processor::cli::FilterName::Blur},
    {"-crystallize", image_processor::cli::FilterName::Crystallize}};

}  // namespace
namespace image_processor::cli {
void Parser::Parse(size_t args_count, char** args_value) {
    if (args_count == 1) {
        help_flag_ = true;
        return;
    }
    if (args_count == MIN_VALID_PARAMETERS_NUMBER) {
        throw std::invalid_argument("Invalid number of arguments");
    }

    input_file_name_ = args_value[INPUT_FILE_INDEX];
    output_file_name_ = args_value[OUTPUT_FILE_INDEX];
    CheckFileExistence(input_file_name_);
    CheckPathExistence(output_file_name_);

    FilterRepresentation curr_filter;
    bool is_filter_name = true;
    for (size_t i = 3; i < args_count; ++i) {
        if (args_value[i][0] == '-' && !IsInt(args_value[i]) && !IsDouble(args_value[i])) {
            if (!is_filter_name) {
                filters_pipline_.push_back(curr_filter);
                curr_filter = FilterRepresentation{};
            }
            if (STRING_TO_FILTER_NAME.contains(args_value[i])) {
                curr_filter.name = STRING_TO_FILTER_NAME.at(args_value[i]);
                is_filter_name = false;
            } else {
                throw std::invalid_argument("Invalid name of filter: " + std::string(args_value[i]));
            }
        } else {
            curr_filter.parameters.push_back(args_value[i]);
        }
    }
    filters_pipline_.push_back(curr_filter);
}

std::filesystem::path Parser::GetInputFileName() const {
    return input_file_name_;
}

std::filesystem::path Parser::GetOutputFileName() const {
    return output_file_name_;
}

void Parser::GetFiltersFromParser(std::vector<std::unique_ptr<filters::Filter>>& filters) const {
    for (size_t i = 0; i < filters_pipline_.size(); ++i) {
        switch (filters_pipline_[i].name) {

            case FilterName::Crop:
                if (filters_pipline_[i].parameters.size() != 2) {
                    throw std::invalid_argument("Invalid number of parameters for crop");
                }
                if (!IsUint(filters_pipline_[i].parameters[0])) {
                    throw std::invalid_argument("Invalid parameter for crop: " +
                                                std::string(filters_pipline_[i].parameters[0]));
                }
                if (!IsUint(filters_pipline_[i].parameters[1])) {
                    throw std::invalid_argument("Invalid parameter for crop: " +
                                                std::string(filters_pipline_[i].parameters[1]));
                }
                filters.push_back(
                    std::make_unique<filters::CropFilter>(std::stoi(filters_pipline_[i].parameters[0].data()),
                                                          std::stoi(filters_pipline_[i].parameters[1].data())));
                break;
            case FilterName::Grayscale:
                if (!filters_pipline_[i].parameters.empty()) {
                    throw std::invalid_argument("Invalid number of parameters for grayscale");
                }
                filters.push_back(std::make_unique<filters::GrayscaleFilter>());
                break;
            case FilterName::Blur:
                if (filters_pipline_[i].parameters.size() != 1) {
                    throw std::invalid_argument("Invalid number of parameters for blur");
                }
                if (!IsUnsignedDouble(filters_pipline_[i].parameters[0])) {
                    throw std::invalid_argument("Invalid parameter for blur: " +
                                                std::string(filters_pipline_[i].parameters[0]));
                }
                filters.push_back(std::make_unique<filters::Blur>(std::stod(filters_pipline_[i].parameters[0].data())));
                break;
            case FilterName::Negative:
                if (!filters_pipline_[i].parameters.empty()) {
                    throw std::invalid_argument("Invalid number of parameters for negative");
                }
                filters.push_back(std::make_unique<filters::NegativeFilter>());
                break;
            case FilterName::EdgeDetection:
                if (filters_pipline_[i].parameters.size() != 1) {
                    throw std::invalid_argument("Invalid number of parameters for edge");
                }
                if (!IsUnsignedDouble(filters_pipline_[i].parameters[0])) {
                    throw std::invalid_argument("Invalid parameter for edge: " +
                                                std::string(filters_pipline_[i].parameters[0]));
                }
                filters.push_back(std::make_unique<filters::EdgeDetectionFilter>(
                    std::stod(filters_pipline_[i].parameters[0].data())));
                break;
            case FilterName::Sharpening:
                if (!filters_pipline_[i].parameters.empty()) {
                    throw std::invalid_argument("Invalid number of parameters for sharpening");
                }
                filters.push_back(std::make_unique<filters::SharpeningFilter>());
                break;
            case FilterName::Crystallize:
                if (filters_pipline_[i].parameters.size() != 1) {
                    throw std::invalid_argument("Invalid number of parameters for crystallize");
                }
                if (!IsUint(filters_pipline_[i].parameters[0])) {
                    throw std::invalid_argument("Invalid parameter for crystallize: " +
                                                std::string(filters_pipline_[i].parameters[0]));
                }
                filters.push_back(
                    std::make_unique<filters::Crystallize>(std::stoi(filters_pipline_[i].parameters[0].data())));
                break;
        }
    }
}
bool Parser::IsHelp() const {
    return help_flag_;
}
}  // namespace image_processor::cli