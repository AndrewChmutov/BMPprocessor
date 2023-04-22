#pragma once
#include "structures.h"
#include <stdio.h>

void getFileHeader(BITMAPFILEHEADER *bfHeader, FILE *file);
void getInfoHeader(BITMAPINFOHEADER *biHeader, FILE *file);

void printFileHeader(BITMAPFILEHEADER *bfHeader);
void printInfoHeader(BITMAPINFOHEADER *biHeader);

typedef enum { false, true } bool;

float **getColorHistogram(FILE *file, 
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader,
                            WORD *ranges, WORD rangec,
                            bool freePixels);
    
void printColorHistogram(FILE *file, 
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader);


void convertToGrayscale(FILE *file, const char* const name,
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader);


void encodeSteganography(FILE *file, const char *const name,
                            const char *text,
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader);


void printSteganography(FILE *file, const char *const name,
                            BITMAPFILEHEADER *bfHeader, 
                            BITMAPINFOHEADER *biHeader);