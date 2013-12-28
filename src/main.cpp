/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2013 Balhar Jakub <balhar.jakub@gmail.com>
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <stdbool.h>
#include <stdint.h>

#include "files.h"
#include "types.h"
#include "codes.h"
#include "parameters.h"
    
void PrintResult(floattype *result, size_t amountOfResults){
    for(size_t i=0; i < amountOfResults; i++){
        printf("Výsledek %lu je %f\n", (i+1), result[i]);
    }
}

/*
 extendedmatrix - ukazatel na již alokovanou paměť matice o rozměrech (paramcount+1) X rowcount
 paramcount - počet parametrů modelu
 rowcount - počet naměřených hodnot
 result - ukazatel na již alokované pole, kam se uloží vypočítané hodnoty parametrů

 funkce vrací:
        S_OK pokud byl systém určený nebo přeurčený
        S_FALSE pokud byl systém podurčený
        E_INVALIDARG pokud mají argumenty špatnou hodnotu, např. rowcount < paramcount
*/
HRESULT SolveLLS4Plus(floattype **extendedmatrix, size_t paramcount, size_t rowcount, floattype *result) {
    if(rowcount < paramcount){
        return E_INVALIDARG;
    }
    floattype **gramMatrix = GenerateMatrix(extendedmatrix,rowcount,paramcount, result);
    solveGem(gramMatrix, result, rowcount);

    FreeMatrix(gramMatrix, rowcount);
    return S_OK;
}

int solveLLS(int argc, char **argv) {
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    if(params == NULL) {
        return errorCode;
    }
    
    floattype **matrix = AllocMatrix(params->columns, params->rows);
    GenerateDataForMatrix(matrix, params->rows, params->columns, params->isZeroOk);
    
    floattype *result = AllocRow(params->rows);
    for(int i = 0; i < params->columns; i++) {
        result[i] = rand();
    }
    
    if(params->saveFile) {
        saveMatrix(matrix, params->filePath, params->rows, params->columns);
    } 
    if(params->loadFile) {
        FreeMatrix(matrix, params->rows);
        Matrix matrixData;
        matrixData = loadMatrix(params->filePath);
    }
    
    // This actually generates Gram matrix. 
    GenerateMatrix(matrix, params->rows, params->columns, result);

    StartStatistics(params->rows);

    switch(SolveLLS4Plus(matrix, params->columns, params->rows, result)){
        case S_OK:
            PrintResult(result, params->columns);
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

    StopAndPrintStatistics();

    FreeMatrix(matrix, params->rows);
    free(result);

    return (CODE_OK);
}

int main(int argc, char **argv)
{
    return solveLLS(argc, argv);
}
