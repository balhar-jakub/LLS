#include "handleFiles.h"

/*
 * This function loads matrix from given file.
 * Matrix file has simple format.
 * First line is amount of rows
 * Second line is amount of columns
 * Rows of Matrix are delimited by end of line
 * Cells in the row are delimited by ;
 */
floattype **loadMatrix(char *filePath){
    FILE *matrixFile;
    floattype **matrix;
    MatrixFileHeader header;
    
    matrixFile = fopen(filePath,"rb");
    fread(&header, sizeof(header), 1, matrixFile);
    matrix = AllocMatrix(header.rowcount, header.colcount);

    for(size_t actualRow = 0; actualRow < header.rowcount; actualRow++) {
        fread(matrix[actualRow], sizeof(floattype), header.colcount, matrixFile);
    }

    fclose(matrixFile);
    return matrix;
}

/*
 * This function saves matrix to given file.
 * Matrix file has simple format.
 * First line is amount of rows
 * Second line is amount of columns
 * Rows of Matrix are delimited by end of line
 */
void saveMatrix(floattype **matrix, char *filePath, size_t amountOfRows, size_t amountOfCols){
    FILE *matrixFile;
    MatrixFileHeader header;
    char endOfLine[] = "\n";
    
    matrixFile = fopen(filePath,"wb");
    header.rowcount = amountOfRows;
    header.colcount = amountOfCols;
    fwrite(&header, sizeof(header), 1, matrixFile);
    for(size_t actualRow = 0; actualRow < amountOfRows; actualRow++) {
        fwrite(matrix[actualRow], sizeof(floattype), amountOfCols, matrixFile);
        fwrite(endOfLine, sizeof(char), 1, matrixFile);
    }

    fclose(matrixFile);
}
