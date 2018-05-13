#pragma once

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class PngWriter {

public:
    static const int HEIGHT = 2000;

    template<typename IIter>
    void printToFile(IIter begin, IIter end, const fs::path &outputFile) {
        auto totalSamples = std::distance(begin, end);
        auto minValue = std::numeric_limits<typename std::remove_pointer<IIter>::type>::min();
        auto maxValue = std::numeric_limits<typename std::remove_pointer<IIter>::type>::max();
        auto image = std::vector<unsigned char>{};
        image.resize(static_cast<unsigned long long int>(totalSamples * HEIGHT * 4));
        auto counter = 0;
        std::for_each(begin, end, [&](auto sampleValue) {
            auto scaledValue = scaleValue(sampleValue, minValue, maxValue);
            for (int y = 0; y < HEIGHT; ++y) {
                if (scaledValue == y) {
                    image[4 * totalSamples * y + 4 * counter + 0] = 255;
                    image[4 * totalSamples * y + 4 * counter + 1] = 255;
                    image[4 * totalSamples * y + 4 * counter + 2] = 255;
                    image[4 * totalSamples * y + 4 * counter + 3] = 255;
                } else {
                    image[4 * totalSamples * y + 4 * counter + 0] = 0;
                    image[4 * totalSamples * y + 4 * counter + 1] = 0;
                    image[4 * totalSamples * y + 4 * counter + 2] = 0;
                    image[4 * totalSamples * y + 4 * counter + 3] = 255;
                }
            }
            counter++;
        });
        encodeOneStep(image, totalSamples, HEIGHT, outputFile);
    }

private:
    void encodeOneStep(std::vector<unsigned char> &image, int width, int height, const fs::path &outputFile);

    template<typename T>
    int scaleValue(T sampleValue, T lowerBound, T upperBound) {
        auto totalBound = upperBound - lowerBound;

        auto absScaled = (static_cast<double>(sampleValue) + (totalBound / 2)) / totalBound;

        return absScaled * HEIGHT;
    }


};

