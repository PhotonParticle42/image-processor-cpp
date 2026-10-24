#include <iostream>
#include <filesystem>
#include "imgproc/io.hpp"

GrayMethod parseGrayScaleMethod(const std::string& arg) {
    if (arg == "GRAY:BT601")  return GrayMethod::BT601;
    if (arg == "GRAY:BT709") return GrayMethod::BT709;
    if (arg == "GRAY:AVG") return GrayMethod::Average;
    return GrayMethod::Unknown; // Safely handle invalid input
}

int main(int argc, char* argv[])
{
    std::cout << "Processing image....\n";
    std::cout << "Total arguments received (argc): " << argc << "\n";
    if (argc > 4) {
        std::cout << "[ERROR] Unknown arguments received.\n";
        return 1;
    } else if (argc < 4){
        std::cout << "[ERROR] Please use cmd as:operation input_image ouput_image.\n";
        return 1;
    } else {
        std::cout << "All arguments received, proceeding further...\n";
    }

    std::cout << "operation: " << argv[1] << "\n";
    std::string operation{ argv[1] };
    GrayMethod method = parseGrayScaleMethod(operation);
    if (method == GrayMethod::Unknown) {
        throw std::runtime_error("Unknown Method Entered For Grayscale calculation.");
    }

    std::cout << "input image: " << argv[2] << "\n";
    std::string input{ argv[2] };

    std::filesystem::path filePath = input;

    if (std::filesystem::exists(filePath)) {
        std::cout << "The input file exists!\n";
    } else {
        std::cout << "The input file does not exist.\n";
        return 1;
    }

    std::cout << "output image: " << argv[3] << "\n";

    Image imageObj = loadImage(input);
    std::cout << "width = " << imageObj.width() <<
        ", height = " << imageObj.height() <<
        ", no of channels = " << imageObj.channels() << "\n";

    std::string output{ argv[3] };
    Image grayScale = toGrayscale(imageObj, method);
    saveImage(grayScale, output);

    std::cout << "Loading Saved Image...\n";
    Image imageObj2 = loadImage(output);
    std::cout << "width = " << imageObj2.width() <<
        ", height = " << imageObj2.height() <<
        ", no of channels = " << imageObj2.channels() << "\n";

    return 0;
}