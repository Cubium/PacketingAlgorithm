#include <iostream>
#include <fstream>

#include "Packet.hpp"

int main(int argc, char **argv)
{
    if (argc == 1) {
        std::cerr << "Not enough arguments. Provide the image file." << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    auto packets = Packet::loadImage(filename);

    std::ofstream output("encoded");
    
    for (auto packet : packets)
        for (auto byte : packet.get_data())
            output.put(byte);

    output.close();
    return 0;
}

