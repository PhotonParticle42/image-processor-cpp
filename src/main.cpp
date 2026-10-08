#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>

class Image {
public:
    Image(size_t width, size_t height, size_t channels)
        : _width(width), _height(height), _channels(channels),
          _data(width * height * channels, 0) {}

    size_t width() const    { return _width; }
    size_t height() const   { return _height; }
    size_t channels() const { return _channels; }

    uint8_t& at(size_t row, size_t column, size_t c)              // checked
    {
        return _data[getIndex(row, column, c)];
    }

    const uint8_t& at(size_t row, size_t column, size_t c) const  // checked
    {
        return _data[getIndex(row, column, c)];
    }

private:
    size_t getIndex(size_t row, size_t column, size_t c) const
    {
        if (row >= _height || column >= _width || c >= _channels) {
            throw std::out_of_range("Image::at: row, column, or channel out of range");
        }
        return (row * _width + column) * _channels + c;
    }

    size_t _width;
    size_t _height;
    size_t _channels;
    std::vector<uint8_t> _data;
};

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