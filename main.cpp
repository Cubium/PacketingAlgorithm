#include <iostream>

#include "Packet.hpp"

int main(void)
{
    auto packets = Packet::loadImage("greyscale.png");
    std::cout << packets.size() * Packet::PACKET_SIZE << std::endl;
    return 0;
}

