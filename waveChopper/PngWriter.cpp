#include <lodepng.h>
#include <iostream>
#include "waveChopper/PngWriter.h"

void
PngWriter::encodeOneStep(std::vector<unsigned char> &image, int width, int height, const fs::path &outputFile) {
    //Encode the image
    auto tmp = outputFile.string();
    unsigned error = lodepng::encode(outputFile.string(), image, width, height);

    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }

}


