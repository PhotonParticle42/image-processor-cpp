cmake_minimum_required(VERSION 3.20)
project(imgproc CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#lib containing img processing logic
add_library(imgproc_lib
	src/io.cpp
)

target_include_directories(imgproc_lib PUBLIC include third_party)

#main executable
add_executable(imgproc src/main.cpp)

target_link_libraries(imgproc
	PRIVATE
		imgproc_lib
)

#include testing
include(CTest)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif()