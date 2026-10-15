#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include "imgproc/image.hpp"

// Set up mock image data
class ImageTest : public ::testing::Test {
protected:
    size_t width = 3;
    size_t height = 2;
    size_t channels = 3; // RGB image
    std::vector<uint8_t> raw_data;

    // This runs before every single test case
    void SetUp() override {
        // Create an image with synthetic data (0 to 17)
        // 3 columns * 2 rows * 3 channels = 18 total elements
        raw_data.resize(width * height * channels);
        for (size_t i = 0; i < raw_data.size(); ++i) {
            raw_data[i] = static_cast<uint8_t>(i);
        }
    }
};

// 2. Test metadata retrieval
TEST_F(ImageTest, MetadataIsCorrect) {
    Image img(width, height, channels, raw_data.data());

    EXPECT_EQ(img.width(), width);
    EXPECT_EQ(img.height(), height);
    EXPECT_EQ(img.channels(), channels);
}

// 3. Test correct data cloning inside the constructor
TEST_F(ImageTest, DataIsCopiedCorrectly) {
    Image img(width, height, channels, raw_data.data());

    // Ensure the underlying vector matches the source
    EXPECT_EQ(img.getData(), raw_data);
}

// 4. Test normal element retrieval (at index boundaries and middle elements)
TEST_F(ImageTest, RetrieveElementsCorrectly) {
    Image img(width, height, channels, raw_data.data());

    // Row 0, Col 0, Channel 0 -> should be 0
    EXPECT_EQ(img.at(0, 0, 0), 0);

    // Row 0, Col 1, Channel 0 -> (0 * 3 + 1) * 3 + 0 = 3
    EXPECT_EQ(img.at(0, 1, 0), 3);

    // Row 1, Col 2, Channel 2 (Last pixel element) -> (1 * 3 + 2) * 3 + 2 = 17
    EXPECT_EQ(img.at(1, 2, 2), 17);
}

// 5. Test modifying pixel values via mutable reference
TEST_F(ImageTest, CanModifyPixelValues) {
    Image img(width, height, channels, raw_data.data());

    // Modify a pixel element
    img.at(0, 1, 1) = 255;

    // Verify it updated correctly
    EXPECT_EQ(img.at(0, 1, 1), 255);
}

// 6. Test exception throwing for out of bounds access
TEST_F(ImageTest, ThrowsExceptionOnOutOfBounds) {
    Image img(width, height, channels, raw_data.data());

    // Row out of bounds (Height is 2, indexing 2 is out of range)
    EXPECT_THROW(img.at(2, 0, 0), std::out_of_range);

    // Column out of bounds (Width is 3, indexing 3 is out of range)
    EXPECT_THROW(img.at(0, 3, 0), std::out_of_range);

    // Channel out of bounds (Channels is 3, indexing 3 is out of range)
    EXPECT_THROW(img.at(0, 0, 3), std::out_of_range);
}

// 7. Test exception messages explicitly
TEST_F(ImageTest, ExceptionHasCorrectMessage) {
    Image img(width, height, channels, raw_data.data());

    try {
        img.at(99, 0, 0);
        FAIL() << "Expected std::out_of_range was not thrown.";
    } catch (const std::out_of_range& err) {
        EXPECT_STREQ(err.what(), "Image::at: row, column, or channel out of range");
    }
}
