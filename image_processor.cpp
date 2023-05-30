#include <iostream>

#include "BMP.h"
#include "Parser.h"
#include "CompositeFilter.h"

int main(int argc, char** argv) {
    try {
        image_processor::cli::Parser parser;
        parser.Parse(argc, argv);
        if (parser.IsHelp()) {
            std::cout << "Image Processor" << '\n';
            std::cout << "///////////////" << '\n';
            std::cout << "Supported format: .bmp (BMP 24)" << '\n';
            std::cout << "///////////////" << '\n';
            std::cout
                << "How to use: ./image_processor {input file path} {output file formats} "
                   "[-{filter name 1} [filter argument 1] [filter argument 2] ...] [-{filter name 2} [filter argument "
                   "1] [filter argument 2] ...] ..."
                << '\n';
            std::cout << "///////////////" << '\n';
            std::cout << "Supported filters:" << '\n';
            std::cout << "Crop (-crop width height)" << '\n';
            std::cout << "Grayscale (-gs)" << '\n';
            std::cout << "Negative (-neg)" << '\n';
            std::cout << "Sharpening (-sharp)" << '\n';
            std::cout << "Blur (-blur sigma)" << '\n';
            std::cout << "Edge Detection (-edge threshold)" << '\n';
            std::cout << "Crystallize (-crystal crystals_quantity)" << '\n';
        } else {
            image_processor::Image image = image_processor::bmp::Read(parser.GetInputFileName());
            std::vector<std::unique_ptr<image_processor::filters::Filter>> pipline_filters;
            parser.GetFiltersFromParser(pipline_filters);
            image_processor::filters::CompositeFilter composite_filter(std::move(pipline_filters));
            composite_filter.ApplyFilter(image);
            image_processor::bmp::Write(parser.GetOutputFileName(), image);
        }
    } catch (const std::exception& e) {
        std::cout << "ERROR" << '\n';
        std::cout << e.what();
    }

    return 0;
}
