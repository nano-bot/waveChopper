#pragma once

#include <experimental/filesystem>
#include <numeric>

namespace fs = std::experimental::filesystem;

class PngWriter {

public:
    static const int WIDTH = 1028;
    static const int HEIGHT = 1024;
    static const int INTERPOLATED_SAMPLES_COUNT = 4;
    static const int RGBA_PIXEL = 4;

    using Color = std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>;

    PngWriter();


    template<typename T>
    void printToFile(const T *values, size_t numOfSamples, const fs::path &outputFile) {
        auto minValue = std::numeric_limits<T>::min();
        auto maxValue = std::numeric_limits<T>::max();
        auto averagedInterval = numOfSamples / WIDTH + 1;
        auto previousX = 0;
        auto previousY = scaleToHeight(0, minValue, maxValue);
        auto sampleStep = size_t{0};
        while (sampleStep != numOfSamples) {
            auto beginInterval = sampleStep;
            auto endInternal = size_t {0};
            if (sampleStep + averagedInterval >= numOfSamples) {
                averagedInterval = numOfSamples - sampleStep;
            }
            endInternal = sampleStep + averagedInterval;
            auto averageValue = std::accumulate(values + beginInterval, values + endInternal, 0.f) / averagedInterval;
            auto scaledValue = scaleToHeight(averageValue, minValue, maxValue);
            drawLine(previousX, previousY, ++previousX, scaledValue, {255, 255, 255, 255});
            previousY = scaledValue;
            sampleStep += averagedInterval;
        }


          encodeOneStep(buffer, WIDTH, HEIGHT, outputFile);
    }

    template<typename IIter>
    void printToFile(IIter begin, IIter end, const fs::path &outputFile) {
        auto totalSamples = std::distance(begin, end);
        auto minValue = std::numeric_limits<typename std::remove_pointer<IIter>::type>::min();
        auto maxValue = std::numeric_limits<typename std::remove_pointer<IIter>::type>::max();
        auto image = std::vector<unsigned char>{};
        image.resize(static_cast<unsigned long long int>(totalSamples * HEIGHT * 4));
        auto counter = 0;
        std::for_each(begin, end, [&](auto sampleValue) {
            auto scaledValue = scaleToHeight(sampleValue, minValue, maxValue);
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

    std::vector<unsigned char> buffer;

    template<typename S, typename T>
    int scaleToHeight(S sampleValue, T lowerBound, T upperBound) {
        auto totalBound = upperBound - lowerBound;

        auto absScaled = (static_cast<double>(sampleValue) + (totalBound / 2)) / totalBound;

        return absScaled * HEIGHT;
    }

    void plot(int x, int y, const Color &color);

    void drawLine(int xStart, int yStart, int xEnd, int yEnd, const Color &color);


};

