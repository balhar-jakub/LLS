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
    size_t columnCount = getParamSize(argv[1]); //(size_t) argv[1];
    size_t rowCount = getParamSize(argv[2]); //(size_t) argv[2];
    bool isZeroOk = getParamBool(argv[3]);
    
    bool saveFile;
    char* filePath;
    if(argc == 6) {
        saveFile = getParamBool(argv[4]);
        filePath = argv[5];
    }
    
    floattype **matrix = AllocMatrix(columnCount, rowCount);
    GenerateDataForMatrix(matrix, rowCount, columnCount, isZeroOk);
    floattype *result = AllocRow(rowCount);
    for(int i = 0; i < columnCount; i++) {
        result[i] = rand();
    }
    
    if(argc == 6) {
        if(saveFile) {
            saveMatrix(matrix, filePath, rowCount, columnCount);
        } else {
            FreeMatrix(matrix, rowCount);
            matrix = loadMatrix(filePath);
        }
    }
    
    // This actually generates Gram matrix. 
    GenerateMatrix(matrix, rowCount, columnCount, result);

    StartStatistics(rowCount);

    switch(SolveLLS4Plus(matrix, columnCount, rowCount, result)){
        case S_OK:
            PrintResult(result, columnCount);
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

    FreeMatrix(matrix, rowCount);
    free(result);

    return (CODE_OK);
}

int main(int argc, char **argv)
{
    solveLLS(argc, argv);
}
