#include <fstream>
#include <iostream>

#include "Packet.hpp"

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cerr << "Not enough arguments. Provide the file to read." << std::endl;
        return 1;
    }

    std::vector<unsigned char> buffer;
    std::vector<Packet> packets;

    std::string filename(argv[1]);
    std::ifstream input(filename);

    for (unsigned i = 0; i < Packet::PACKETS; i++) {
        for (unsigned n = 0; n < sizeof(Packet); n++) {
            unsigned char c = input.get();

            if (input.eof()) {
                std::cerr << "Reached EOF early" << std::endl;
                return 1;
            }

            buffer.emplace_back(c);
        }

        packets.emplace_back(Packet(buffer));
        buffer.clear();
    }

    Packet::writeImage(packets, "output.png");

    input.close();
    return 0;
}
