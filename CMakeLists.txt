cmake_minimum_required(VERSION 3.0)
project(ImageTransmission)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lz -std=c++11 -O0")

include_directories(lodepng)

add_executable(output output.cpp Packet.cpp lodepng/lodepng.cpp)
add_executable(read read.cpp Packet.cpp lodepng/lodepng.cpp)

