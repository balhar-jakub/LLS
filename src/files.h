/* 
 * File:   files.h
 * Author: Jakub Balhar
 *
 * Simple utility for loading matrices from binary file and writing matrices 
 * into the binary file. 
 */
#include "types.h"

#ifndef FILES_H_
#define FILES_H_
    floattype **loadMatrix(char *filePath, MatrixFileHeader *header);
    floattype **loadMatrix(FILE *matrixFile, MatrixFileHeader *header);
    
    int saveMatrix(floattype **matrix, char *filePath, size_t amountOfRows, size_t amountOfCols);
    int saveMatrix(floattype **matrix, FILE *file, size_t amountOfRows, size_t amountOfCols);
#endif