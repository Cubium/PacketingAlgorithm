#include "Packet.hpp"

std::vector<Packet> Packet::loadImage(std::string filename)
{
    std::vector<unsigned char> image; //the raw pixels
    std::vector<Packet> packets;
    unsigned size = Packet::IMAGE_SIZE;
    
    unsigned error = lodepng::decode(image, size, size, filename);
    if (error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        std::exit(1);
    }

    Packet current;
    for (uint8_t i=0; i < Packet::IMAGE_SIZE / Packet::PACKET_SIZE; ++i) {
        for (unsigned n=0; n < Packet::PACKET_SIZE; n++) {
            current.data[n] = image[i * Packet::PACKET_SIZE + 4 * n];
        }
        current.id = i;
        current.calc_crc();
        packets.push_back(current);
    }

    return packets;
}

bool Packet::validate_crc() const
{
    auto crc_calc = crc32(0L, data.data(), Packet::PACKET_SIZE) & 0xFF;
    return crc == crc_calc;
}

void Packet::calc_crc()
{
    crc = crc32(0L, data.data(), Packet::PACKET_SIZE) & 0xFF;
}
