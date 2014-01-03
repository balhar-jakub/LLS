#include <stdio.h>
#include <stdlib.h>

#include "lls.h"
#include "types.h"
#include "codes.h"
#include "matrix.h"
#include "gem.h"
#include "memory.h"
#include "parameters.h"
#include "statistics.h"
#include "files.h"
#include "print.hpp"

/*
 matrix - ukazatel na matici s vygenerovanými hodnotami, která slouží jako základ pro
 gramovu matici.
 paramcount - počet parametrů modelu. Počet sloupců matice.
 rowcount - počet naměřených hodnot. Počet řádků matice
 result - ukazatel na již alokované pole, kam se uloží vypočítané hodnoty parametrů

 funkce vrací:
        S_OK pokud byl systém určený nebo přeurčený
        S_FALSE pokud byl systém podurčený
        E_INVALIDARG pokud mají argumenty špatnou hodnotu, např. rowcount < paramcount
*/
HRESULT SolveLLS4Plus(floattype **matrix, size_t paramCount, size_t rowCount, floattype *result) {
    if(rowCount < paramCount){
        return E_INVALIDARG;
    }
    floattype **gramMatrix = GenerateMatrix(matrix, rowCount, paramCount, result);
    solveGemSquare(gramMatrix, rowCount);

    FreeMatrix(gramMatrix, rowCount);
    return S_OK;
}

int solveLLS(int argc, char **argv) {
    Matrix *matrixData = NULL;
    int errorCode = CODE_OK;
    Parameters *params = getParams(argc, argv, &errorCode);
    if(params == NULL) {
        free(params);
        return errorCode;
    }
    
    floattype **matrix = AllocMatrix(params->rows, params->columns);
    GenerateDataForMatrix(matrix, params->rows, params->columns, params->isZeroOk);
    
    floattype *result = AllocRow(params->rows);
    for(size_t i = 0; i < params->columns; i++) {
        result[i] = rand();
    }
    
    if(params->saveFile) {
        saveMatrix(matrix, params->filePath, params->rows, params->columns);
    } 
    if(params->loadFile) {
        FreeMatrix(matrix, params->rows);
        matrixData = loadMatrix(params->filePath);
        matrix = matrixData->matrix;
    } 
    
    StartStatistics(params->rows);
    
    HRESULT resultCode = SolveLLS4Plus(matrix, params->columns, params->rows, result);
    PrintResultComputation(resultCode, params->rows, result);

    StopAndPrintStatistics();

    FreeMatrix(matrix, params->rows);
    free(result);
    if(matrixData != NULL) {
        free(matrixData);
    }
    free(params);

    return (CODE_OK);
}
