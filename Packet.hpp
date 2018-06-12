#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <cstdint>
#include <cstdlib>

#include "lodepng/lodepng.h"
#include <zlib.h>

struct Packet {
    static const size_t IMAGE_SIZE = 500;
    static const size_t PACKET_SIZE = 100;

    uint8_t id;
    uint8_t crc;
    uint8_t data[PACKET_SIZE];

    void setId(uint8_t id) { this->id = id; }
    bool validate_crc() const;
    void calc_crc();

    static std::vector<Packet> loadImage(std::string filename);
};

static_assert(Packet::IMAGE_SIZE * Packet::IMAGE_SIZE % Packet::PACKET_SIZE == 0, "Chunk size must be a factor of pixel count");

