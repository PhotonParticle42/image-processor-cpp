#include <iostream>
#include "imgproc/io.hpp"

int main()
{
    std::string path1 = "/home/aniruddha/projects/image-processor-cpp/tests/mario_PNG124.png";
    Image imageObj = loadImage(path1);

    std::string path2 = "/home/aniruddha/projects/image-processor-cpp/tests/saved_mario_PNG124.png";
    saveImage(imageObj, path2);

    std::cout << "Loading Saved Image...\n";
    loadImage(path2);

    return 0;
}