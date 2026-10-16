#include "imgproc/io.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <iostream>
#include <memory>

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

    Image img(width, height, numChannels, data.get());
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