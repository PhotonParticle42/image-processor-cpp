Creating an Image Processor

Build:
cmake --build build

Usage:

1) ./build/imgproc GRAY:BT601 input.png output.png
2) ./build/imgproc GRAY:BT709 input.png output.png
3) ./build/imgproc GRAY:AVG input.png output.png

Unit tests:
./build/tests/test_image