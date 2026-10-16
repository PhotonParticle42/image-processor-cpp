#include <iostream>
#include <filesystem>
#include "imgproc/io.hpp"

int main(int argc, char* argv[])
{
    std::cout << "Processing image....\n";
    std::cout << "Total arguments received (argc): " << argc << "\n";
    if (argc > 3) {
        std::cout << "[ERROR] Unknown arguments received.\n";
        return 1;
    } else if (argc < 3){
        std::cout << "[ERROR] Please provide both input and ouput paths of images.\n";
        return 1;
    } else {
        std::cout << "All arguments received, proceeding further...\n";
    }

    std::cout << "input image: " << argv[1] << "\n";
    std::cout << "output image: " << argv[2] << "\n";

    std::string input{ argv[1] };

    std::filesystem::path filePath = input;

    if (std::filesystem::exists(filePath)) {
        std::cout << "The input file exists!\n";
    } else {
        std::cout << "The input file does not exist.\n";
        return 1;
    }

    Image imageObj = loadImage(input);
    std::cout << "width = " << imageObj.width() <<
        ", height = " << imageObj.height() <<
        ", no of channels = " << imageObj.channels() << "\n";

    std::string output{ argv[2] };
    saveImage(imageObj, output);

    std::cout << "Loading Saved Image...\n";
    Image imageObj2 = loadImage(output);
    std::cout << "width = " << imageObj2.width() <<
        ", height = " << imageObj2.height() <<
        ", no of channels = " << imageObj2.channels() << "\n";

    return 0;
}