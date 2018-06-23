#include <iostream>

#include "Packet.hpp"

int main(void)
{
    auto packets = Packet::loadImage("greyscale.png");
    Packet::writeImage(packets, "corrupted.png");

    return 0;
}

