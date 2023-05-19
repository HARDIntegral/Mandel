#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    char Type[2];
} BMPSignature;

typedef struct {
    uint32_t FileSize;
    uint32_t reserved;
    uint32_t DataOffset;
} BMPFileHeader;

typedef struct {
    uint32_t Size;
    uint32_t Width;
    uint32_t Height;
    uint16_t Planes;
    uint16_t BPP;
    uint32_t Compression;
    uint32_t ImageSize;
    uint32_t xPPM;
    uint32_t yPPM;
    uint32_t ColorsUsed;
    uint32_t ImportantColors;
} BMPImgHeader;

void createImage(const char* name, uint32_t ImageWidth, uint32_t ImageHeight, uint8_t* pixels);