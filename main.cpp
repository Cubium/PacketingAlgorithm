#include <iostream>

#include "Packet.hpp"

const double ERROR_RATE = 0.010; //10%

int main(void)
{
    auto packets = Packet::loadImage("greyscale.png");

    for (auto &packet : packets) {
        packet.corrupt(ERROR_RATE);
    }

    Packet::writeImage(packets, "corrupted.png");

    return 0;
}

