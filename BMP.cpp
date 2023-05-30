#include "BMP.h"

#include <fstream>
#include <ostream>

namespace {
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;
const int BMP_FORMAT = 0x4D42;
const int BMP_SIZE = 24;
const int BITS_COUNT_REQUIRED = 24;
const double LIMIT = 255.0f;
const size_t BMP_CHANNELS_QUANTITY = 3;
int64_t PaddingAmount(size_t width) {
    return ((4 - (static_cast<int64_t>(width) * 3) % 4) % 4);
}
}  // namespace

image_processor::Image image_processor::bmp::Read(const std::filesystem::path &path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::invalid_argument("Cannot open file");
    }

    bmp::BMPFileHeader file_header;
    file.read(reinterpret_cast<char *>(&file_header), FILE_HEADER_SIZE);

    if (file_header.file_type != BMP_FORMAT) {
        throw std::invalid_argument("Invalid format of input file");
    }

    bmp::BMPInfoHeader inf_header;
    file.read(reinterpret_cast<char *>(&inf_header), INFO_HEADER_SIZE);

    if (inf_header.width < 0) {
        throw std::invalid_argument("Invalid width of input file");
    }
    if (inf_header.compression != 0) {
        throw std::invalid_argument("Invalid compression parameter of input file");
    }
    if (inf_header.bit_count != BITS_COUNT_REQUIRED) {
        throw std::invalid_argument("Invalid BMP format of input file");
    }
    if (inf_header.colors_used != 0) {
        throw std::invalid_argument("Invalid colors used for BMP format");
    }

    Image image = Image(BMP_CHANNELS_QUANTITY, inf_header.width, std::abs(inf_header.height));
    const int64_t padding_amount = PaddingAmount(image.GetWidth());

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            uint8_t pixel[3];
            file.read(reinterpret_cast<char *>(pixel), 3);
            size_t curr_height = inf_header.height > 0 ? image.GetHeight() - 1 - y : y;
            image.SetPixel(x, curr_height, static_cast<double>(pixel[2]) / LIMIT, static_cast<double>(pixel[1]) / LIMIT,
                           static_cast<double>(pixel[0]) / LIMIT);
        }
        file.ignore(padding_amount);
    }
    return image;
}
void image_processor::bmp::Write(const std::filesystem::path &path, const Image &image) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    uint8_t bmp_pad[3] = {0, 0, 0};
    static const int64_t PADDING_AMOUNT = PaddingAmount(image.GetWidth());

    bmp::BMPFileHeader bmp_file_header;
    bmp_file_header.file_type = BMP_FORMAT;
    bmp_file_header.file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + image.GetWidth() * image.GetHeight() * 3 +
                                PADDING_AMOUNT * image.GetHeight();
    bmp_file_header.offset_data = FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    bmp::BMPInfoHeader bmp_info_header;
    bmp_info_header.size = INFO_HEADER_SIZE;
    bmp_info_header.width = static_cast<int32_t>(image.GetWidth());
    bmp_info_header.height = static_cast<int32_t>(image.GetHeight());
    bmp_info_header.bit_count = BITS_COUNT_REQUIRED;
    bmp_info_header.size_image = BMP_SIZE;

    file.write(reinterpret_cast<char *>(&bmp_file_header), FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char *>(&bmp_info_header), INFO_HEADER_SIZE);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            const Image::Pixel curr_pixel = image.GetPixel(x, image.GetHeight() - y - 1);
            const uint8_t r = static_cast<const uint8_t>(curr_pixel.r * LIMIT);
            const uint8_t g = static_cast<const uint8_t>(curr_pixel.g * LIMIT);
            const uint8_t b = static_cast<const uint8_t>(curr_pixel.b * LIMIT);
            file.write(reinterpret_cast<const char *>(&b), sizeof(b));
            file.write(reinterpret_cast<const char *>(&g), sizeof(g));
            file.write(reinterpret_cast<const char *>(&r), sizeof(r));
        }
        file.write(reinterpret_cast<char *>(bmp_pad), PADDING_AMOUNT);
    }
    file.close();
}