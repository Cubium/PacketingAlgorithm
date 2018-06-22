#include <iostream>

#include "Packet.hpp"

const double ERROR_RATE = 0.10;

int main(void)
{
    auto packets = Packet::loadImage("greyscale.png");

    /*
    unsigned errors = 0;
    for (auto &packet : packets) {
        packet.corrupt(ERROR_RATE);
        if (!packet.validate_crc())
            errors++;
    }

    std::cout << errors << " errors, " << Packet::PACKETS - errors << " intact packets.\n";
    std::cout << static_cast<double>(errors) / static_cast<double>(Packet::PACKETS) << "\% of packets corrupted\n";

    std::cout << packets.size() << " packets use " << sizeof(Packet) * packets.size() << " bytes.\n";
    */

    Packet::writeImage(packets, "corrupted.png");

    return 0;
}

