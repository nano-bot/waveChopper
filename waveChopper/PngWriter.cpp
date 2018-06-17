#include <lodepng.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "waveChopper/PngWriter.h"

PngWriter::PngWriter() {
    buffer.resize(WIDTH * HEIGHT * RGBA_PIXEL, 0);
}

void
PngWriter::encodeOneStep(std::vector<unsigned char> &image, int width, int height, const fs::path &outputFile) {
    //Encode the image
    auto tmp = outputFile.string();
    unsigned error = lodepng::encode(outputFile.string(), image, width, height);

    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }

}

void PngWriter::plot(int x, int y, const PngWriter::Color &color) {
    assert(x >= 0 && x <= WIDTH);
    assert(y >= 0 && y <= HEIGHT);

    auto[red, green, blue, alpha] = color;
    buffer[RGBA_PIXEL * WIDTH * y + RGBA_PIXEL * x + 0] = red;
    buffer[RGBA_PIXEL * WIDTH * y + RGBA_PIXEL * x + 1] = green;
    buffer[RGBA_PIXEL * WIDTH * y + RGBA_PIXEL * x + 2] = blue;
    buffer[RGBA_PIXEL * WIDTH * y + RGBA_PIXEL * x + 3] = alpha;
}

void PngWriter::drawLine(int x1, int y1, int x2, int y2, const Color &color) {
    // Bresenham's line algorithm
    bool steep = (std::abs(y2 - y1) > std::abs(x2 - x1));
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const auto dx = x2 - x1;
    const auto dy = std::abs(y2 - y1);
    auto error = dx / 2.0f;
    const auto ystep = (y1 < y2) ? 1 : -1;
    auto y = y1;

    const auto maxX = x2;
    for (auto x = x1; x < maxX; x++) {
        if (steep) {
            plot(y, x, color);
        } else {
            plot(x, y, color);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}








