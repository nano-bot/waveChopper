#include <iostream>
#include "lodePNG/lodepng.h"
#include "waveChopper/WaveFile.h"
#include <string_view>

int main() {
    WaveFile waveFile{ fs::path{std::string_view{"D:\\tools\\sox-14-4-2\\converted\\Virus_WT_045.wav"}}};
    waveFile.writePngToFile(fs::path{std::string_view{"d:\\playground\\wave.png"}});
    std::cout<< waveFile;
    return 0;
}