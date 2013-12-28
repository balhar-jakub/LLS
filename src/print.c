#include <stdio.h>

#include "types.h"
#include "print.h"

void printMatrix(floattype **matrix, size_t rowCount, size_t columnCount) {
    printf("MATRIX BEGIN\n");
    for(size_t i = 0; i < rowCount; i++) {
        for(size_t j = 0; j < columnCount; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("MATRIX END\n");
}
