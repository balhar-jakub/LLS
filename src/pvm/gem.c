#include<stdbool.h>
#include<stdio.h>
#include<math.h>

#include "../types.h"
#include "../codes.h"
#include "../memory.h"
#include "../gem.h"
#include "../print.hpp"

size_t highestValueRowInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount);
void normalizeColumnsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount);
void normalizeRowsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount);
void countNewValueColumns(floattype **matrix, size_t actualRow, size_t rowToNormalize, size_t actualColumn, size_t rowCount);

int solveGemSquare(floattype **matrix, size_t rowCount){
    size_t highestValueRow;
    floattype *rowToMove;
    for(size_t actualRow = 0, actualColumn = 0; 
            actualRow < rowCount; actualRow++, actualColumn++) {
        // Move with row with highest value. Pivot row must be among unused rows. 
        highestValueRow = highestValueRowInSelection(matrix, actualRow, actualColumn, rowCount);
        rowToMove = matrix[actualRow];
        matrix[actualRow] = matrix[highestValueRow];
        matrix[highestValueRow] = rowToMove;
        // Normalize all columns
        normalizeColumnsInSelection(matrix, actualRow, actualColumn, rowCount+1);
        matrix[actualRow][actualColumn] = 1;
        
        // Normalize all rows now
        normalizeRowsInSelection(matrix, actualRow, actualColumn, rowCount);
    }
    
    return CODE_OK;
}


void normalizeRowsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount){
    for(size_t rowToNormalize = actualRow + 1; rowToNormalize < rowCount;
            rowToNormalize++) {
        countNewValueColumns(matrix, actualRow, rowToNormalize, actualColumn, rowCount + 1);
        matrix[rowToNormalize][actualColumn] = 0;
    }
}

void countNewValueColumns(floattype **matrix, size_t actualRow, size_t rowToNormalize, size_t actualColumn, size_t rowCount) {
    for(size_t colToNormalize = actualColumn+1; colToNormalize < rowCount;
            colToNormalize++) {
        matrix[rowToNormalize][colToNormalize] = 
                matrix[rowToNormalize][colToNormalize] - 
                (matrix[rowToNormalize][actualColumn] * matrix[actualRow][colToNormalize]);
    }    
}

void normalizeColumnsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount) {
    for(size_t columnToNormalize = actualColumn + 1; columnToNormalize < rowCount; 
                columnToNormalize++) {
        matrix[actualRow][columnToNormalize] = 
                matrix[actualRow][columnToNormalize] / matrix[actualRow][actualColumn];
    }   
}

size_t highestValueRowInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount) {
    size_t highestValueRow = actualRow;
    floattype highestValue = 0;
    for(size_t candidateRow = actualRow; candidateRow < rowCount; candidateRow++) {
        if(matrix[candidateRow][actualColumn] > highestValue){
            highestValue = matrix[candidateRow][actualColumn];      
            highestValueRow = candidateRow;
        }
    }
    return highestValueRow;
}