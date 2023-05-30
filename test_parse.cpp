#include <catch.hpp>

#include "Parser.h"
#include "Image.h"

namespace {
const std::string PATH = "/home/ivan/pmi-228-1-Ivan-Boboshko-BoboshkoIvan/cmake-build-debug/image_processor";
const std::string INPUT_FILE = "../tasks/image_processor/test_script/data/examples/shrek.bmp";
const std::string OUTPUT_FILE = "../tasks/image_processor/test_script/data/examples/shrek_1.bmp";
const std::string INVALID_FILE = "../tasks/image_processor/test_script/data/examples/non_existent_file.bmp";
}  // namespace

TEST_CASE("Parser: HELP") {
    const size_t args_counts = 1;
    const char* argv[] = {PATH.c_str()};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    REQUIRE(parser.IsHelp());
}

TEST_CASE("Parser: Invalid input file") {
    const size_t args_counts = 2;
    const char* argv[] = {PATH.c_str(), INVALID_FILE.c_str()};
    image_processor::cli::Parser parser;
    REQUIRE_THROWS_AS(parser.Parse(args_counts, const_cast<char**>(argv)), std::invalid_argument);  // NOLINT
}

TEST_CASE("Parser: Invalid filter name 1") {
    const size_t args_counts = 4;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-gss"};
    image_processor::cli::Parser parser;
    REQUIRE_THROWS_AS(parser.Parse(args_counts, const_cast<char**>(argv)), std::invalid_argument);  // NOLINT
}

TEST_CASE("Parser: Invalid filter name 2") {
    const size_t args_counts = 8;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-gs", "-crop", "10", "10",
                          "-a"};  // -a filter name
    image_processor::cli::Parser parser;
    REQUIRE_THROWS_AS(parser.Parse(args_counts, const_cast<char**>(argv)), std::invalid_argument);  // NOLINT
}

TEST_CASE("Parser: Invalid number of parameters for filter 1") {
    const size_t args_counts = 5;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-gs", "1"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}

TEST_CASE("Parser: Invalid number of parameters for filter 2") {
    const size_t args_counts = 7;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-crop", "1", "1", "1"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}

TEST_CASE("Parser: Invalid number of parameters for filter 3") {
    const size_t args_counts = 4;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-crystallize"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}

TEST_CASE("Parser: Invalid argument type 1") {
    const size_t args_counts = 6;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-crop", "-1", "1"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}

TEST_CASE("Parser: Invalid argument type 2") {
    const size_t args_counts = 6;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-crop", "a", "1"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}

TEST_CASE("Parser: Invalid argument type 3") {
    const size_t args_counts = 4;
    const char* argv[] = {PATH.c_str(), INPUT_FILE.c_str(), OUTPUT_FILE.c_str(), "-edge", "-1"};
    image_processor::cli::Parser parser;
    parser.Parse(args_counts, const_cast<char**>(argv));  // NOLINT
    std::vector<std::unique_ptr<image_processor::filters::Filter>> filters;
    REQUIRE_THROWS_AS(parser.GetFiltersFromParser(filters), std::invalid_argument);
}