#pragma once

#include <iostream>
#include <string>
#include <array>
#include <random>

#include <cstdint>
#include <cstdlib>

#include "lodepng/lodepng.h"
#include <zlib.h>

struct Packet {
    static const size_t IMAGE_DIM = 256;
    static const size_t PIXELS = IMAGE_DIM * IMAGE_DIM;
    static const size_t PACKET_SIZE = 256;
    static const size_t PACKETS = PIXELS / PACKET_SIZE;

    uint8_t id;
    uint8_t crc;
    std::array<uint8_t, PACKET_SIZE> data;

    void setId(uint8_t id) { this->id = id; }
    bool validate_crc() const;
    void calc_crc();
    void corrupt(double errorRate);

    static std::vector<Packet> loadImage(std::string filename);
    static void writeImage(const std::vector<Packet> &packets, std::string filename);
};

static_assert(Packet::PIXELS % Packet::PACKET_SIZE == 0, "Chunk size must be a factor of pixel count");
static_assert(Packet::PACKETS <= 256, "A one-byte index cannot support more than 256 Packets");
