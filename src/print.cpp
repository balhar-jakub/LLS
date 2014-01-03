#include <stdio.h>
#include <iostream>

#include "types.h"
#include "print.hpp"


void PrintResult(floattype *result, size_t amountOfResults){
    for(size_t i=0; i < amountOfResults; i++){
        printf("Výsledek %lu je %f\n", (i+1), result[i]);
    }
}

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

void PrintResultComputation(HRESULT resultCode, size_t rows, floattype *result) {
    switch(resultCode){
        case S_OK:
            PrintResult(result, rows);
            break;
        case S_FALSE:
            std::cout << "cannot solve";
            break;
        case E_INVALIDARG:
            std::cout << "function's parameters mismatch";
            break;
        default:
            std::cout << "Unexpected error";
    }
}
