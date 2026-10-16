#include <iostream>
#include "imgproc/io.hpp"

int main()
{
    std::string path1 = "/home/aniruddha/projects/image-processor-cpp/tests/mario_PNG124.png";
    Image imageObj = loadImage(path1);
    std::cout << "width = " << imageObj.width() <<
        ", height = " << imageObj.height() <<
        ", no of channels = " << imageObj.channels() << "\n";

    std::string path2 = "/home/aniruddha/projects/image-processor-cpp/tests/saved_mario_PNG124.png";
    saveImage(imageObj, path2);

    std::cout << "Loading Saved Image...\n";
    Image imageObj2 = loadImage(path2);
    std::cout << "width = " << imageObj2.width() <<
        ", height = " << imageObj2.height() <<
        ", no of channels = " << imageObj2.channels() << "\n";

    return 0;
}