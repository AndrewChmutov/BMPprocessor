#include "bmp.h"
#include <stdint.h>
#include <inttypes.h>


void getFileHeader(BITMAPFILEHEADER *bfHeader, FILE *file) {
    fread(&bfHeader->bfType, sizeof(bfHeader->bfType), 1, file);
    fread(&bfHeader->bfSize, sizeof(bfHeader->bfSize), 1, file);
    fread(&bfHeader->bfReserved1, sizeof(bfHeader->bfReserved1), 1, file);
    fread(&bfHeader->bfReserved2, sizeof(bfHeader->bfReserved2), 1, file);
    fread(&bfHeader->bfOffBits, sizeof(bfHeader->bfOffBits), 1, file);
}


void getInfoHeader(BITMAPINFOHEADER *biHeader, FILE *file) {
    fread(&biHeader->biSize, sizeof(biHeader->biSize), 1, file);
    fread(&biHeader->biWidth, sizeof(biHeader->biWidth), 1, file);
    fread(&biHeader->biHeight, sizeof(biHeader->biHeight), 1, file);
    fread(&biHeader->biPlanes, sizeof(biHeader->biPlanes), 1, file);
    fread(&biHeader->biBitCount, sizeof(biHeader->biBitCount), 1, file);
    fread(&biHeader->biCompression, sizeof(biHeader->biCompression), 1, file);
    fread(&biHeader->biSizeImage, sizeof(biHeader->biSizeImage), 1, file);
    fread(&biHeader->biXPelsPerMeter, sizeof(biHeader->biXPelsPerMeter), 1, file);
    fread(&biHeader->biYPelsPerMeter, sizeof(biHeader->biYPelsPerMeter), 1, file);
    fread(&biHeader->biClrUsed, sizeof(biHeader->biClrUsed), 1, file);
    fread(&biHeader->biClrImportant, sizeof(biHeader->biClrImportant), 1, file);
    
}


void printFileHeader(BITMAPFILEHEADER *bfHeader) {
    printf("BITMAPFILEHEADER\n");
    printf("  bfType:\t\t0x%x (BM)\n", bfHeader->bfType);
    printf("  bfSize:\t\t%u\n", bfHeader->bfSize);
    printf("  bfReversed1:\t\t0x%x\n", bfHeader->bfReserved1);
    printf("  bfReversed2:\t\t0x%x\n", bfHeader->bfReserved2);
    printf("  bfOffBits:\t\t%u\n", bfHeader->bfOffBits);
}


void printInfoHeader(BITMAPINFOHEADER *biHeader) {
    printf("BITMAPINFOHEADER\n");
    printf("  biSize:\t\t%u\n", biHeader->biSize);
    printf("  biWidth:\t\t%d\n", biHeader->biWidth);
    printf("  biHeight\t\t%d\n", biHeader->biHeight);
    printf("  biPlanes:\t\t%u\n", biHeader->biPlanes);
    printf("  biBitCount:\t\t%u\n", biHeader->biBitCount);
    printf("  biCompression:\t%u\n", biHeader->biCompression);
    printf("  biSizeImage:\t\t%u\n", biHeader->biSizeImage);
    printf("  biXPelsPerMeter:\t%d\n", biHeader->biXPelsPerMeter);
    printf("  biYPelsPerMeter:\t%d\n", biHeader->biYPelsPerMeter);
    printf("  biClrUsed:\t\t%u\n", biHeader->biClrUsed);
    printf("  biClrImportant:\t%u\n", biHeader->biClrImportant);
}