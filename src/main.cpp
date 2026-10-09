#include <iostream>
#include "imgproc/image.hpp"

int main()
{
    Image image(3, 2, 3);  // 3 wide, 2 tall, RGB

    // Checkerboard: white, black, white / black, white, black
    for (size_t row = 0; row < image.height(); ++row) {
        for (size_t col = 0; col < image.width(); ++col) {
            uint8_t value = ((row + col) % 2 == 0) ? 255 : 0;
            for (size_t c = 0; c < image.channels(); ++c) {
                image.at(row, col, c) = value;
            }
        }
    }

    // Test 1: read back a value
    int v = image.at(1, 1, 0);
    std::cout << (v == 255 ? "PASS" : "FAIL") << ": at(1,1,0) = " << v << "\n";

    // Test 2: row out of range
    try {
        image.at(3, 2, 0);
        std::cout << "FAIL: bad row did not throw\n";
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: bad row threw: " << e.what() << "\n";
    }

    // Test 3: channel out of range
    try {
        image.at(0, 0, 3);
        std::cout << "FAIL: bad channel did not throw\n";
    } catch (const std::out_of_range& e) {
        std::cout << "PASS: bad channel threw: " << e.what() << "\n";
    }

    return 0;
}