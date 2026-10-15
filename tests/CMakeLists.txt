find_package(GTest REQUIRED)

add_executable(test_image
    test_image.cpp
)

target_link_libraries(test_image
    PRIVATE
        imgproc_lib
        GTest::gtest_main
)

include(GoogleTest)

# Run tests from the tests source directory
# so relative test image paths work
set_target_properties(test_image PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

gtest_discover_tests(test_image
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)