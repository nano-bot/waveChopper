#include "waveChopper/WaveFile.h"
#include <fstream>
#include <iostream>
#include <waveChopper/Formatter.h>
#include "waveChopper/WavHeader.h"
#include "algorithm"


WaveFile::WaveFile(const fs::path &pathToShow) : path{pathToShow}, header{std::make_unique<WavHeader>()} {
    std::fstream input{pathToShow.string(), std::ios::binary | std::ios::in};
    input.read(reinterpret_cast<char *>(header.get()), sizeof(WavHeader));
    validateHeader();
    rawData = std::make_unique<char[]>(header->subchunk2Size);
    input.read(reinterpret_cast<char *>(rawData.get()), header->subchunk2Size);
}

void WaveFile::writeToFile(const fs::path &wavFilePath) {

}

void WaveFile::extractOneCycle() {

}

void WaveFile::writePngToFile(const fs::path &pngFile) {
    int16_t *samples = reinterpret_cast<int16_t *>(rawData.get());
    std::cout << header->subchunk2Size / 2 << std::endl;
    //pngWriter.printToFile(samples, samples + header->subchunk2Size / 2, pngFile);
    pngWriter.printToFile(reinterpret_cast<int16_t *>(rawData.get()), header->subchunk2Size / 2, pngFile);
}


void WaveFile::validateHeader() {
    if (header->numOfChan != 1) {
        throw std::runtime_error{Formatter() << "Wrong number of channels should be 1, given" << header->numOfChan};
    }
    if (header->samplesPerSec != 44100) {
        throw std::runtime_error{Formatter() << "Wrong sample rate, should be 44.1KHz, given" << header->samplesPerSec};
    }
}

std::ostream &operator<<(std::ostream &ostream, const WaveFile &waveFile) {
    ostream << "Wave file: " << waveFile.path << std::endl;
    ostream << "Num of channels: " << waveFile.header->numOfChan << std::endl;
    ostream << "Bits per sample: " << waveFile.header->bitsPerSample << std::endl;
    ostream << "Num of samples: "
            << waveFile.header->subchunk2Size / waveFile.header->numOfChan / (waveFile.header->bitsPerSample / 8);
    return ostream;
}