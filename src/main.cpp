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
#include "handleFiles.h"


#ifdef WINDOWS
    #include <windows.h>
    typedef __int64 Long64_t; //Portable signed long integer 8 bytes
    typedef unsigned __int64 ULong64_t; //Portable unsigned long integer 8 bytes
#else
    typedef int HRESULT;
    const HRESULT S_OK = 0;
    const HRESULT S_FALSE = -1;
    const HRESULT E_INVALIDARG = 0x80070057;
    
    typedef long long Long64_t; //Portable signed long integer 8 bytes
    typedef unsigned long long ULong64_t;//Portable unsigned long integer 8 byte
#endif
    
typedef double floattype;
time_t startTimestamp;
size_t sizeOfGramMatrix;

typedef struct {
    ULong64_t rowcount;  //počet řádků matice, malý endián
    ULong64_t colcount; //počet sloupců matice, malý endián
} MatrixFileHeader;

/*
	Allocate dynamically memory for created Matrix. 
 */
floattype **AllocMatrix(size_t columnCount, size_t rowCount) {
    floattype **matrix = (floattype**) malloc (sizeof(floattype*) * rowCount);
    for(size_t i = 0; i != rowCount; i++) {
            matrix[i] = (floattype*) malloc (sizeof(floattype)*(columnCount));
    }
    return matrix;
}

void GenerateDataForMatrix(floattype **matrix, 
        size_t rowCount, 
        size_t columnCount, 
        bool isZeroOk) 
{
    for(size_t i = 0; i < rowCount; i++) {
        for(size_t j = 0; j != columnCount; j++){
            matrix[i][j] = rand();
            if(!isZeroOk && matrix[i][j] == 0) {
                j--;
            }
        }
    }
}

/*
 * Velikost gramovy matice je rovna rowCount + 1 pro GEM, který pak počítá
 * result
 * Prvek gramovy matice na místě i,j je roven skalárnímu součtu vektorů V_i až
 * V_j
 */
floattype **GenerateMatrix(floattype **matrix, 
        size_t gramRows, 
        size_t parametersInRow,
        floattype *results) 
{
    floattype **gramMatrix = AllocMatrix((gramRows + 1), gramRows);
    floattype sum;

    for(size_t row = 0; row < gramRows; row++) {
        for(size_t cell=0; cell < parametersInRow; cell++){
            //Go through all the positions in the final matrix.
            sum = 0;
            for(size_t positionInVector = 0; positionInVector < parametersInRow; positionInVector++){
                sum += (matrix[row][positionInVector] * matrix[cell][positionInVector]);
            }
            gramMatrix[row][cell] = sum;
        }
        gramMatrix[row][parametersInRow] = results[row];
    }
    return gramMatrix;
}

void solveGem(floattype **matrix, floattype *result, size_t rowAmount)
{
    // Jako první dostanu zadanou matici, která je na pravé straně rozšířená o 
    // matici výsledků.
    // Jinak se jedná o matici čtvercovou, je to součástí zadání Gramovy matice.
    int actualRow = 0, innerRow;
    int actualColumn = 0, innerColumn;
    floattype valueOfActualRow, valueOfActualInnerRow;
    // Poslední řádek už je vyřešený
    //rowAmount je u čtvercové matice i, colsAmount pak i +1
    for(actualRow = 0; actualRow < rowAmount - 1; actualRow++, actualColumn++) {
        valueOfActualRow = matrix[actualRow][actualColumn];
        for(innerColumn = actualColumn; innerColumn < rowAmount + 1; innerColumn++) {
            matrix[actualRow][innerColumn] = matrix[actualRow][innerColumn] / valueOfActualRow;
            // V n-tém sloupci mám jedna, ve zbylých sloupcích mám původní 
            // hodnotu lomeno n tým sloupcem.
        }
        // Vezmu jeden po druhém řádky. 
        // První řádek vydělím prvním indexem a následně přičtu resp. 
        // odečtu od dalších řádků tolikrát, aby na zbylých řádcích byla v 
        // daném sloupci nula.
        // Začínám na dalším řádku než aktuálně jsem.
        for(innerRow = actualRow + 1; innerRow < rowAmount; innerRow++) {
            valueOfActualInnerRow = matrix[innerRow][actualColumn]; // Kolikrát je potřeba sluopec přičíst / odečíst
            // Provedu ve skutečnosti odečtení pro všechny sloupce.
            for(innerColumn = actualColumn; innerColumn < rowAmount + 1; innerColumn++) {
                matrix[innerRow][innerColumn] = matrix[innerRow][innerColumn] -
                        (valueOfActualInnerRow * matrix[actualRow][innerColumn]);
            }
        }
    }

    // V tenhle okamžik by měl být vypsán výsledek gemové matice, která je zadaná v parametru.
    printf("The result is:\n");
    for(actualRow = 0; actualRow < rowAmount; actualRow++){
        result[actualRow] = matrix[actualRow][rowAmount];
        printf("result na pozici %d=%f\n", actualRow + 1, matrix[actualRow][rowAmount]);
    }
}

/*
 * It stores basic information about statistics.
 */
void StartStatistics(size_t rowAmount){
    sizeOfGramMatrix = rowAmount;
    startTimestamp = time(NULL);
}

/*
 * It gets actual time as a stop time. Then it prints out the time of process
 * and size of matrix.
 * The data are printed into stdout.
 */ 
void StopAndPrintStatistics(){
    time_t endTimestamp = time(NULL);
    printf("Začátek výpočtu: %ld\nKonec výpočtu: %ld\nPočet řádků matice: %lu\n", 
            startTimestamp, endTimestamp, sizeOfGramMatrix);
}

void sortForPartialPivoting(floattype **matrix, size_t rowCount){
    // Pro všechny sloupce projdi všechny řádky a setřiď je tak, aby
    // v daném řádku byl nejvyšší hodnota z nepoužitých hodnot.
}

/*
 *  It simply frees memory of two dimensional array given as parameter. 
 *  Second parameter is just amount of rows of the array.
 */
void FreeMatrix(floattype **matrix, size_t rowcount){
    for (size_t i = 0; i != rowcount; i++) { 
            free(matrix[i]);
    }
    free(matrix);
}

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

int main(int argc, char **argv)
{
    size_t columnCount = (size_t) strtol(argv[1], NULL, 10); //(size_t) argv[1];
    size_t rowCount = (size_t) strtol(argv[2], NULL, 10); //(size_t) argv[2];
    bool isZeroOk = (int) strtol(argv[3], NULL, 10);
    
    bool saveFile;
    char* filePath;
    if(argc == 6) {
        saveFile = (int) strtol(argv[4], NULL, 10);
        filePath = argv[5];
    }
    
    floattype **matrix = AllocMatrix(columnCount, rowCount);
    GenerateDataForMatrix(matrix, rowCount, columnCount, isZeroOk);
    floattype *result = (floattype*) malloc (sizeof(floattype) * columnCount);
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

    return (0);
}
