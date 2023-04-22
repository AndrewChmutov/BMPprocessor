#include "bmp.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>


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


float **getColorHistogram(FILE *file, 
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader,
                            WORD *ranges, WORD rangec,
                            bool freePixels) {
    size_t rowPixels = biHeader->biWidth;
    size_t rowCount = biHeader->biHeight;
    size_t rowLength = (biHeader->biBitCount * rowPixels + 31) / 32;
    WORD colorCount[3];
    rowLength *= 4;
    uint8_t temp;

    int **pixelsCount = malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++) {
        pixelsCount[i] = malloc(sizeof(int) * (rangec - 1));
        colorCount[i] = 0;
        for (int j = 0; j < rangec - 1; j++)
            pixelsCount[i][j] = 0;
    }

    fseek(file, bfHeader->bfOffBits, SEEK_SET);
    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowPixels; j++) {
            for (int c = 0; c < 3; c++) {
                temp = 0;
                fread(&temp, sizeof(temp), 1, file);


                for (int r = 1; r < rangec; r++) {
                    if ((temp >= ranges[r - 1]) && (temp < ranges[r])) {
                        colorCount[c] += 1;
                        pixelsCount[c][r - 1] += 1;
                        break;
                    }
                }
            }
        }
        fseek(file, rowLength - rowPixels * 3, SEEK_CUR);
    }
    

    float **pixelsPercent = malloc(sizeof(float*) * 3);
    for (int i = 0; i < 3; i++) {
        pixelsPercent[i] = malloc(sizeof(float) * (rangec - 1));
        for (int j = 0; j < rangec - 1; j++) 
            pixelsPercent[i][j] = (float)pixelsCount[i][j] / colorCount[i];

        free(pixelsCount[i]);
    }
    free(pixelsCount);

    if (freePixels == true) {
        for (int i = 0; i < 3; i++)
            free(pixelsPercent[i]);
        free(pixelsPercent);
        pixelsPercent = NULL;
    }

    return pixelsPercent;
}

void printColorHistogram(FILE *file, 
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader) {
    WORD ranges[16] = {
        0, 16, 32, 64, 80, 96, 112, 128, 144, 
        160, 176, 192, 208, 224, 240, 256
    };

    float **pixelsPercent = getColorHistogram(
        file, 
        bfHeader, 
        biHeader,
        ranges,
        16,
        false
    );

    char *colors[3] = { "Blue", "Green", "Red" };

    for (int c = 0; c < 3; c++) {
        printf("%s:\n", colors[c]);
        for (int i = 1; i < 16; i++) {
            printf("  %u-%u: %.2f %%\n", ranges[i - 1], ranges[i] - 1, 100.0 * pixelsPercent[c][i - 1]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++)
        free(pixelsPercent[i]);
    free(pixelsPercent);
    pixelsPercent = NULL;
}


void convertToGrayscale(FILE *file, const char* const name,
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader) {
    rewind(file);
    FILE *newfile = fopen(name, "w");

    uint8_t *header = malloc(bfHeader->bfOffBits);
    
    fread(header, sizeof(uint8_t), bfHeader->bfOffBits, file);
    fwrite(header, sizeof(uint8_t), bfHeader->bfOffBits, newfile);
    free(header);

    size_t rowPixels = biHeader->biWidth;
    size_t rowCount = biHeader->biHeight;
    size_t rowLength = (biHeader->biBitCount * rowPixels + 31) / 32;
    WORD colorCount[3];
    rowLength *= 4;
    uint8_t temp;


    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowPixels; j++) {
            uint8_t avg = 0;
            for (int c = 0; c < 3; c++) {
                temp = 0;
                fread(&temp, sizeof(temp), 1, file);
                avg += temp / 3;
            }
            for (int k = 0; k < 3; k++)
                fputc(avg, newfile);
        }
        temp = 0;
        for (int k = 0; k < rowLength - rowPixels * 3; k++) 
            fputc(temp, newfile);
        
        fseek(file, rowLength - rowPixels * 3, SEEK_CUR);
    }

    // fseek(newfile, 28, SEEK_SET);
    // fputc(8, newfile);

    fclose(newfile);
}