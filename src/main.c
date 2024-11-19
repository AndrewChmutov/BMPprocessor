#include <stdio.h>
#include <stdlib.h>

#include <bmp.h>
#include <structures.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No filename enetered.\n");
        return 0;
    }

    FILE* ptrFile = fopen(argv[1], "rb");

    if (ptrFile == NULL) {
        printf("Error: cannot open this file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;

    getFileHeader(&bfHeader, ptrFile);
    getInfoHeader(&biHeader, ptrFile);

    if (argc == 2) {
        printFileHeader(&bfHeader);
        printInfoHeader(&biHeader);
    }


    if (argc == 2) {
        if (biHeader.biBitCount != 24 || biHeader.biCompression != 0) {
            printf("Not supported functional for non 24 pixel size and non-zero compression\n");
        }
        else {
            printf("\n");
            printColorHistogram(
                ptrFile,
                &bfHeader,
                &biHeader
            );
        }
        char choice;
        printf("Decode steganography?[Y/n] ");
        scanf("%c", &choice);
        if (choice == 'Y' || choice == 'y' || choice == '\n') {
            printSteganography(
                ptrFile,
                argv[2],
                &bfHeader,
                &biHeader
            );
        }
    }
    else if (argc == 3) {
        convertToGrayscale(
            ptrFile,
            argv[2],
            &bfHeader,
            &biHeader
        );
    }
    else if (argc == 4) {
        encodeSteganography(
            ptrFile,
            argv[2],
            argv[3],
            &bfHeader,
            &biHeader
        );
    }

    fclose(ptrFile);


    return 0;
}
