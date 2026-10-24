#include "imgproc/io.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <iostream>
#include <memory>
#include <cmath>

namespace {
    uint8_t CalGreyScaleWithBT601(const Image& in, size_t row, size_t col)
    {
        double gray{ 0.0 };
        gray = 0.299 * in.at(row, col, 0) + 0.587 * in.at(row, col, 1) + 0.114 * in.at(row, col, 2);    
        return static_cast<uint8_t>(std::lround(gray));
    }

    uint8_t CalGreyScaleWithBT709(const Image& in, size_t row, size_t col)
    {
        double gray{ 0.0 };
        gray = 0.2126 * in.at(row, col, 0) + 0.7152 * in.at(row, col, 1) + 0.0722 * in.at(row, col, 2);    
        return static_cast<uint8_t>(std::lround(gray));
    }

    uint8_t CalGreyScaleWithAverage(const Image& in, size_t row, size_t col)
    {
        double gray{ 0.0 };
        gray = (in.at(row, col, 0) + in.at(row, col, 1) + in.at(row, col, 2)) / 3;    
        return static_cast<uint8_t>(std::lround(gray));
    }
}

Image loadImage(const std::string& path)
{
    int width{ 0 };
    int height{ 0 };
    int numChannels{ 0 };
    constexpr int kChannels{ 4 };

    std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
        stbi_load(path.c_str(), &width, &height, &numChannels, kChannels), stbi_image_free);

    if (!data) {
        throw std::runtime_error("stbi_load failed for '" + path + "': " + stbi_failure_reason());
    }
    std::cout << "file had " << numChannels << ", buffer has " << kChannels << "\n";

    //construct the image with the number of bytes in the buffer
    Image img(width, height, kChannels, data.get());
    return img;
}

void saveImage(const Image& img, const std::string& path)
{
	int success = stbi_write_png(path.c_str(), img.width(), img.height(), img.channels(), img.getData().data(), img.width()*img.channels());
    if (!success) {
    	throw std::runtime_error("stbi_write_png failed for '" + path + "'./n");
    }
    std::cout << "Saved Image successfully: " << path << ".\n";
}

Image toGrayscale(const Image& in, GrayMethod method)
{
    if (in.channels() < 3) {
        throw std::invalid_argument("toGrayscale: input needs at least 3 channels");
    }

    Image out(in.width(), in.height(), 1);   // blank constructor

    //height is how many rows, width is how many columns.
    for(size_t row = 0; row < in.height(); row++) {
        for(size_t col = 0; col < in.width(); col++) {

            uint8_t greyedValue{ 0 };
            if (method == GrayMethod::BT601) {
                greyedValue = CalGreyScaleWithBT601(in, row, col);
            } else if (method == GrayMethod::BT709) {
                greyedValue = CalGreyScaleWithBT709(in, row, col);
            } else if (method == GrayMethod::Average) {
                greyedValue = CalGreyScaleWithAverage(in, row, col);
            } else {
                throw std::runtime_error("Unknown Method Entered For Grayscale calculation.");
            }

            out.at(row, col, 0) = greyedValue;
        }
    }

    return out;
}