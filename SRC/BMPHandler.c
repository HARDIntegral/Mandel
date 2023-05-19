#include "BMPHandler.h"

void createImage(const char* name, uint32_t ImageWidth, uint32_t ImageHeight, uint8_t* pixels) {
    // init structs
    BMPSignature BMP_S;
    BMPFileHeader BMP_FH;
    BMPImgHeader BMP_IH;

    BMP_S.Type[0] = 'B';
    BMP_S.Type[1] = 'M';

    // calculate padding
    uint8_t padding = (ImageWidth * 3) % 4;

    // header information
    BMP_FH.FileSize = (ImageWidth * 3 + padding) * ImageHeight + 54;
    BMP_FH.reserved = 0;
    BMP_FH.DataOffset = 54;

    BMP_IH.Size = 40;
    BMP_IH.Width = ImageWidth;
    BMP_IH.Height = ImageHeight;
    BMP_IH.Planes = 1;
    BMP_IH.BPP = 24;
    BMP_IH.Compression = 0;
    BMP_IH.ImageSize = 0;
    BMP_IH.xPPM = 0;
    BMP_IH.yPPM = 0;
    BMP_IH.ColorsUsed = 0;
    BMP_IH.ImportantColors = 0;

    // create File
    FILE* file;
    file = fopen(name, "wb");

    fwrite(&BMP_S, sizeof(BMP_S), 1, file);
    fwrite(&BMP_FH, sizeof(BMP_FH), 1, file);
    fwrite(&BMP_IH, sizeof(BMP_IH), 1, file);

    // painting
    for(uint32_t y = 0; y < ImageHeight; y++) {
        for(uint32_t x = 0; x < ImageWidth; x++) {
            fputc(pixels[3 * (y * ImageWidth + x) + 0], file);
            fputc(pixels[3 * (y * ImageWidth + x) + 1], file);
            fputc(pixels[3 * (y * ImageWidth + x) + 2], file);
        }
        if(padding) for(uint8_t i = 0; i < padding; i++) fputc(0, file);
    }

    fclose(file);
}