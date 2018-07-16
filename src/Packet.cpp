#include "Packet.hpp"

Packet::Packet() = default;

Packet::Packet(std::vector<unsigned char> bytes)
{
    id = bytes[0];
    crc = bytes[1];

    for (size_t i = 0; i < data.size() && i < bytes.size() - 2; i++)
        data[i] = bytes[i + 2];
}

std::vector<Packet> Packet::loadImage(const std::string& filename)
{
    std::vector<unsigned char> image; //the raw pixels
    std::vector<Packet> packets;
    unsigned dim = Packet::IMAGE_DIM;

    unsigned error = lodepng::decode(image, dim, dim, filename);
    if (error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        exit(1);
    }

    Packet current;
    auto iter = image.begin();
    for (size_t i = 0; i < Packet::PACKETS; i++) {
        for (size_t n = 0; n < Packet::PACKET_SIZE; n++) {
            current.data[n] = *iter;
            iter += 4;
        }

        current.id = i;
        current.calc_crc();
        packets.push_back(current);
    }

    return packets;
}

void Packet::writeImage(const std::vector<Packet>& packets, const std::string& filename)
{
    std::vector<unsigned char> imageData;
    imageData.reserve(PIXELS * 4);

    for (auto& packet : packets) {
        for (uint8_t byte : packet.data) {
            //RGB are all equal in greyscale
            for (auto i = 0; i < 3; i++) {
                imageData.push_back(static_cast<unsigned char>(byte));
            }
            //Alpha (RGBA encoding)
            imageData.push_back(255);
        }
    }

    auto error = lodepng::encode(filename, imageData, Packet::IMAGE_DIM, Packet::IMAGE_DIM);
    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        exit(2);
    }
}

bool Packet::check_crc() const
{
    auto crc = crc32(0L, data.data(), Packet::PACKET_SIZE) & 0xFF;
    return this->crc == crc;
}

void Packet::calc_crc()
{
    crc = crc32(0L, data.data(), Packet::PACKET_SIZE) & 0xFF;
}

std::vector<unsigned char> Packet::get_data() const
{
    const auto* raw_data = (const unsigned char*)this;
    std::vector<unsigned char> bytes;

    for (unsigned i = 0; i < sizeof(Packet); i++)
        bytes.push_back(raw_data[i]);

    return bytes;
}
