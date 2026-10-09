#include "image.hpp"
#include<string>

Image loadImage(const std::string& path);
void saveImage(const Image& img, const std::string& path);  // write PNG