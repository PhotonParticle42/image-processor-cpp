#pragma once
#include "image.hpp"
#include<string>

enum class GrayMethod { BT601, BT709, Average, Unknown };

Image loadImage(const std::string& path);
void saveImage(const Image& img, const std::string& path);  // write PNG
Image toGrayscale(const Image& in, GrayMethod method = GrayMethod::BT601);