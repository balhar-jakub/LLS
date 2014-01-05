#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "types.h"
#include "codes.h"
#include "random.h"

/*
	Allocate dynamically memory for created Matrix. 
 */
floattype **AllocMatrix(size_t rowCount, size_t columnCount) 
{
    floattype **matrix = (floattype**) malloc (sizeof(floattype*) * rowCount);
    for(size_t i = 0; i < rowCount; i++) {
            matrix[i] = AllocRow(columnCount);
            for(size_t j = 0; j < columnCount; j++) {
                matrix[i][j] = 0;
            }
    }
    return matrix;
}

/*
 *  It simply frees memory of two dimensional array given as parameter. 
 *  Second parameter is just amount of rows of the array.
 */
void FreeMatrix(floattype **matrix, size_t rowCount){
    for (size_t i = 0; i < rowCount; i++) { 
            free(matrix[i]);
    }
    free(matrix);
}

/*
 * It simply allocates Row in memory. Just handy shorter notation for calloc.
 */
floattype *AllocRow(size_t rowSize) {
    return (floattype*) calloc (rowSize, sizeof(floattype));
}

floattype *AllocResult(size_t rowSize) {
    floattype *result = AllocRow(rowSize);
    for(size_t i = 0; i < rowSize; i++) {
        result[i] = randLim(20000);
    }
    return result;
}