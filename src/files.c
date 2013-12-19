/*
 * File:   files.c
 * Author: Jakub Balhar
 * 
 * Implementation of header files war loading matrices from files and saving 
 * matrices to files. 
 */
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "files.h"
#include "memory.h"
#include "codes.h"

/*
 * It loads matrix from file on the filePath, if the filePath does not exists,
 * it returns NULL. Otherwise it returns loaded Matrix.
 */
Matrix *loadMatrix(char *filePath)
{
    FILE *matrixFile;
    Matrix *matrix;
    
    matrixFile = fopen(filePath,"rb");
    if(matrixFile == NULL) {
        return NULL;
    }
    
    matrix = loadMatrix(matrixFile);
    
    fclose(matrixFile);
    return matrix;
}

/*
 * It loads matrix from given file.
 */
Matrix *loadMatrix(FILE *matrixFile)
{
    floattype **matrix;
    char endOfLine;
    Matrix *result = (Matrix*) malloc (sizeof(Matrix));
    
    MatrixFileHeader header = {0,0};
    fread(&header, sizeof(header), 1, matrixFile);
    
    if(header.colcount == 0 || header.rowcount == 0) {
        return NULL;
    }
    
    matrix = AllocMatrix(header.rowcount, header.colcount);

    for(size_t actualRow = 0; actualRow < header.rowcount; actualRow++) {
        fread(matrix[actualRow], sizeof(floattype), header.colcount, matrixFile);
        fread(&endOfLine, sizeof(char), 1, matrixFile);
    }
    
    result->header = header;
    result->matrix = matrix;
    return result;
}


/*
 * It saves matrix to new file on the given filePath. If it isn't possible it 
 * returns NULL. 
 */
int saveMatrix(floattype **matrix, char *filePath, size_t amountOfRows, 
        size_t amountOfCols)
{
    FILE *matrixFile;
    
    matrixFile = fopen(filePath,"wb");
    if(matrixFile == NULL) {
        return CODE_NO_FILE;
    }
    
    int result = saveMatrix(matrix, matrixFile, amountOfRows, amountOfCols);
    
    if(fclose(matrixFile) != 0){
        return CODE_CANT_CLOSE;
    }
    
    return result;
}

/*
 * It saves matrix to given file on the given filePath. If it isn't possible it 
 * returns NULL. 
 */
int saveMatrix(floattype **matrix, FILE *matrixFile, size_t amountOfRows, 
        size_t amountOfCols)
{
    MatrixFileHeader header;
    char endOfLine[] = "\n";
    
    header.rowcount = amountOfRows;
    header.colcount = amountOfCols;
    if(fwrite(&header, sizeof(header), 1, matrixFile) != 1){
        return CODE_CANT_WRITE;
    }

    for(size_t actualRow = 0; actualRow < amountOfRows; actualRow++) {
        if(fwrite(matrix[actualRow], sizeof(floattype), amountOfCols, matrixFile) != amountOfCols) {
            return CODE_CANT_WRITE;
        }
        if(fwrite(endOfLine, sizeof(char), 1, matrixFile) != 1) {
            return CODE_CANT_WRITE;
        }
    }
    
    return CODE_OK;
}
