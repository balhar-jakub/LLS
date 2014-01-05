#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "types.h"
#include "matrix.h"
#include "memory.h"
#include "random.h"

/*
 * It gets pointer to matrix and fills the matrix with random data.
 * Only thing I know how to test is whether there is no zero when isZeroOk is 
 * false
 */
void GenerateDataForMatrix(floattype **matrix, 
        size_t rowCount, 
        size_t columnCount, 
        bool isZeroOk) 
{
    for(size_t i = 0; i < rowCount; i++) {
        for(size_t j = 0; j != columnCount; j++){
            matrix[i][j] = randLim(200);
            if(!isZeroOk && matrix[i][j] == 0) {
                j--;
            }
        }
    }
}

/*
 * Velikost gramovy matice je rovna rowCount + 1 pro GEM, který pak počítá
 * result
 * Prvek gramovy matice na místě i,j je roven skalárnímu součtu vektorů V_i a
 * V_j, kde i i j jsou čísla řádku dané matice. 
 */
floattype **GenerateMatrix(floattype **matrix, 
        size_t rows, 
        size_t columns,
        floattype *results) 
{
    if(columns > rows) {
        return NULL;
    }
    floattype **gramMatrix = AllocMatrix(rows, (rows+1));
    floattype sum;

    for(size_t row = 0; row < rows; row++) {
        for(size_t cell=0; cell < rows; cell++){
            //Go through all the positions in the final matrix.
            sum = 0;
            for(size_t positionInVector = 0; positionInVector < columns; positionInVector++){
                sum += (matrix[row][positionInVector] * matrix[cell][positionInVector]);
            }
            gramMatrix[row][cell] = sum;
        }
        gramMatrix[row][rows] = results[row];
    }
    return gramMatrix;
}