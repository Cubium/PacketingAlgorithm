Implementation of the packeting algorithm as proposed to Dr. Sojka. Produces two binaries that will encode/decode png images. Relies on the lodepng library.

To build:
$ git clone --recursive https://github.com/Cubium/PacketingAlgorithm
& cd PacketingAlgorithm
& cmake .
& make

To encode a png file:
& output FILE

to decode:
& read FILE
