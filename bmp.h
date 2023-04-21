#pragma once
#include "structures.h"
#include <stdio.h>

void getFileHeader(BITMAPFILEHEADER *bfHeader, FILE *file);
void getInfoHeader(BITMAPINFOHEADER *biHeader, FILE *file);

void printFileHeader(BITMAPFILEHEADER *bfHeader);
void printInfoHeader(BITMAPINFOHEADER *biHeader);