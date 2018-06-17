#pragma once


#include "WavHeader.h"
#include "PngWriter.h"

namespace fs = std::experimental::filesystem;

class WaveFile {

public:
    explicit WaveFile(const fs::path &srcWavFile);

    void writeToFile(const fs::path &wavFile);

    void extractOneCycle();

    void writePngToFile(const fs::path &pngFile);


    friend std::ostream &operator<<(std::ostream &ostream, const WaveFile &waveFile);

private:
    fs::path path;
    std::unique_ptr<WavHeader> header;
    std::unique_ptr<char[]> rawData;
    PngWriter pngWriter;

    void validateHeader();
};

std::ostream &operator<<(std::ostream &ostream, const WaveFile &waveFile);



