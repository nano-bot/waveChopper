#pragma once

#include <cstdint>

struct WavHeader {
    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4];         // RIFF Header Magic header
    uint32_t chunkSize;      // RIFF Chunk Size
    uint8_t WAVE[4];         // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t fmt[4];          // FMT header
    uint32_t subchunk1Size;  // Size of the fmt chunk
    uint16_t audioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t numOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t samplesPerSec;  // Sampling Frequency in Hz
    uint32_t bytesPerSec;    // bytes per second
    uint16_t blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t subchunk2ID[4];  // "data"  string
    uint32_t subchunk2Size;  // Sampled data length
};