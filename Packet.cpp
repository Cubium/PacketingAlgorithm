#include "Packet.hpp"

std::vector<Packet> Packet::loadImage(std::string filename)
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
    for (size_t i=0; i < Packet::PACKETS; i++) {
        for (size_t n=0; n < Packet::PACKET_SIZE; n++) {
            current.data[n] = *iter;
            iter += 4;
        }

        current.id = i;
        current.calc_crc();
        packets.push_back(current);
    }

    return packets;
}

void Packet::writeImage(const std::vector<Packet> &packets, std::string filename)
{
    std::vector<unsigned char> imageData;
    imageData.reserve(PIXELS * 4);

    for (auto &packet : packets) {
        for (uint8_t byte : packet.data) {
            //RGB are all equal in greyscale
            for (auto i=0; i<3; i++) {
                imageData.push_back(static_cast<unsigned char>(byte));
            }
            //Alpha (RGBA encoding)
            imageData.push_back(255);
        }
    }

    auto error = lodepng::encode(filename, imageData, Packet::IMAGE_DIM, Packet::IMAGE_DIM);
    if(error) {
        std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
        exit(2);
    }
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

void Packet::corrupt(double errorRate)
{
    std::random_device r;
    std::default_random_engine rng(r());
    std::uniform_real_distribution<double> real_dist(0, 1);
    std::uniform_int_distribution<uint8_t> byte_dist(0, 255);
    double random;

    //Randomly flip random bits
    for (auto &byte : data)
    {
        random = real_dist(rng);

        if (random < errorRate)
            byte ^= byte_dist(rng);
    }
}

