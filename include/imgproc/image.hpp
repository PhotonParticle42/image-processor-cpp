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