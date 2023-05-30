#include "Crystallize.h"

#include <limits>
#include <random>
#include <stdexcept>

namespace {
const int64_t SEED = 2282281488;
std::vector<size_t> GenerateRandomVectorOfIndexes(size_t start, size_t end, size_t size) {
    static std::uniform_int_distribution<size_t> distribution(start, end);
    static std::mt19937 gen(SEED);
    std::vector<size_t> result(size);
    std::generate(result.begin(), result.end(), []() { return distribution(gen); });
    return result;
}
}  // namespace

void image_processor::filters::Crystallize::ApplyFilter(Image& image) const {
    if (crystals_quantity_ > image.GetWidth() * image.GetHeight()) {
        return;
    }

    std::vector<size_t> crystal_x = GenerateRandomVectorOfIndexes(0, image.GetHeight() - 1, crystals_quantity_);
    std::vector<size_t> crystal_y = GenerateRandomVectorOfIndexes(0, image.GetWidth() - 1, crystals_quantity_);
    std::vector<Image::Pixel> pixels;

    for (size_t i = 0; i < crystals_quantity_; ++i) {
        pixels.push_back(image.GetPixel(crystal_x[i], crystal_y[i]));
    }

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            size_t curr_crystal_index = FindClosestCrystal(crystal_x, crystal_y, i, j);
            image.SetPixel(j, i, pixels[curr_crystal_index].r, pixels[curr_crystal_index].g,
                           pixels[curr_crystal_index].b);
        }
    }
}

image_processor::filters::Crystallize::Crystallize(size_t crystals_quantity) : crystals_quantity_(crystals_quantity) {
}

size_t image_processor::filters::Crystallize::FindClosestCrystal(const std::vector<size_t>& new_x,
                                                                 const std::vector<size_t>& new_y, size_t curr_height,
                                                                 size_t curr_width) const {
    size_t minimal_distance = std::numeric_limits<size_t>::max();
    size_t closest_crystal_index = 0;
    for (size_t k = 0; k < crystals_quantity_; ++k) {
        size_t curr_distance =
            (curr_height - new_y[k]) * (curr_height - new_y[k]) + (curr_width - new_x[k]) * (curr_width - new_x[k]);
        if (curr_distance < minimal_distance) {
            minimal_distance = curr_distance;
            closest_crystal_index = k;
        }
    }
    return closest_crystal_index;
}
