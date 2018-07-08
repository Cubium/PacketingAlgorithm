cmake_minimum_required(VERSION 3.0)
project(ImageTransmission)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lz -std=c++11 -O3")

include_directories(lodepng)

add_executable(encode src/encode.cpp src/Packet.cpp lodepng/lodepng.cpp)
add_executable(decode src/decode.cpp src/Packet.cpp lodepng/lodepng.cpp)

