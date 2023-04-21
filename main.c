#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "bmp.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No filename enetered.");
        return 0;
    }

    FILE* ptrFile = fopen(argv[1], "r");

    if (ptrFile == NULL) {
        printf("Error: cannot open this file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;

    getFileHeader(&bfHeader, ptrFile);
    getInfoHeader(&biHeader, ptrFile);

    if (argc == 2 || argc == 4) {
        printFileHeader(&bfHeader);
        printInfoHeader(&biHeader);
    }

    if (biHeader.biBitCount != 24 || biHeader.biCompression != 0)
        return 0;

    printf("\n");

    printColorHistogram(
        ptrFile,
        &bfHeader,
        &biHeader
    );


    fclose(ptrFile);


    return 0;
}