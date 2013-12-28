#include<stdbool.h>
#include<stdio.h>
#include<math.h>

#include "types.h"
#include "codes.h"
#include "memory.h"
#include "gem.h"
#include "print.h"

int solveGemSquare(floattype **matrix, size_t rowCount){
    floattype highestValue;
    size_t highestValueRow;
    floattype *rowToMove;
    for(size_t actualRow = 0, actualColumn = 0; 
            actualRow < rowCount; actualRow++, actualColumn++) {
        // Move with row with highest value. Pivot row must be among unused rows. 
        highestValue = 0; highestValueRow = actualRow;
        for(size_t candidateRow = actualRow; candidateRow < rowCount; candidateRow++) {
            if(matrix[candidateRow][actualColumn] > highestValue){
                highestValue = matrix[candidateRow][actualColumn];      
                highestValueRow = candidateRow;
            }
        }
        rowToMove = matrix[actualRow];
        matrix[actualRow] = matrix[highestValueRow];
        matrix[highestValueRow] = rowToMove;
        
        // Normalize all columns
        for(size_t columnToNormalize = actualColumn+1; columnToNormalize < rowCount + 1; 
                columnToNormalize++) {
            matrix[actualRow][columnToNormalize] = 
                    matrix[actualRow][columnToNormalize] / matrix[actualRow][actualColumn];
        }
        matrix[actualRow][actualColumn] = 1;
        
        // Normalize all rows now
        for(size_t rowToNormalize = actualRow + 1; rowToNormalize < rowCount;
                rowToNormalize++) {
            for(size_t colToNormalize = actualColumn + 1; colToNormalize < rowCount + 1;
                    colToNormalize++) {
                matrix[rowToNormalize][colToNormalize] = 
                        matrix[rowToNormalize][colToNormalize] - 
                        (matrix[rowToNormalize][actualColumn] * matrix[actualRow][colToNormalize]);
            }
            matrix[rowToNormalize][actualColumn] = 0;
        }
    }
    
    return CODE_OK;
}