#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<float.h>

#include "../types.h"
#include "../codes.h"
#include "../memory.h"
#include "../gem.h"
#include "../print.hpp"

void *highestValueRowInSelectionHandler(void *args);
void *normalizeRowsInSelectionHandler(void *args);
void *normalizeColumnsInSelectionHandler(void *args);
void *countNewValueColumnsHandler(void *args);

size_t highestValueRowInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount);
void normalizeColumnsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount, size_t baseColumn);
void normalizeRowsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount, size_t baseRow);
void countNewValueColumns(floattype **matrix, size_t actualRow, size_t rowToNormalize, size_t actualColumn, size_t rowCount);

typedef struct {
    floattype **matrix;
    
    size_t actualRow;
    size_t actualColumn;
    size_t rowCount;
} HighestValueRowParameters;

typedef struct {
    floattype **matrix;
    
    size_t actualRow;
    size_t actualColumn;
    size_t rowCount;
    size_t baseColumn;
} ColumnNormalize;


int solveGemSquare(floattype **matrix, size_t rowCount){
    size_t highestValueRow;
    floattype *rowToMove;
    size_t columnCount = rowCount + 1;
    
    int amountOfThreads = 4, result;
    int rowsPerThread = ceil((double)((double)rowCount / (double)amountOfThreads));
    int columnsPerThread = ceil((double)((double)columnCount / (double)amountOfThreads));
    pthread_t thread[amountOfThreads];
    HighestValueRowParameters *highestValueParams[amountOfThreads];
    ColumnNormalize *columnNormalize[amountOfThreads];
    size_t *returnValues[amountOfThreads];
    floattype highestValue = 0;
    
    for(size_t actualRow = 0, actualColumn = 0; 
            actualRow < rowCount; actualRow++, actualColumn++) {
        // Move with row with highest value. Pivot row must be among unused rows.
        highestValueRow = actualRow;
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualRow + (i * rowsPerThread) >= rowCount) {
                continue;
            }
            highestValueParams[i] = (HighestValueRowParameters*) malloc(sizeof(HighestValueRowParameters));
            highestValueParams[i]->actualColumn = actualColumn;
            highestValueParams[i]->matrix = matrix;
            
            highestValueParams[i]->actualRow = actualRow + (i * rowsPerThread);
            size_t maxRow = actualRow + ((i + 1) * rowsPerThread);
            if(maxRow > rowCount) {
                maxRow = rowCount;
            }
            highestValueParams[i]->rowCount = maxRow;
            result = pthread_create(&thread[i], NULL, highestValueRowInSelectionHandler, highestValueParams[i]);
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            
        }
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualRow + (i * rowsPerThread) >= rowCount) {
                continue;
            }
            result = pthread_join(thread[i], (void**)&(returnValues[i]));
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            free(highestValueParams[i]);
        }
        highestValue = DBL_MIN;
        for(int i = 0; i < amountOfThreads; i++){
            if(actualRow + (i * rowsPerThread) >= rowCount) {
                continue;
            }
            size_t candidateRow = *returnValues[i];
            if(matrix[candidateRow][actualColumn] > highestValue){
                highestValue = matrix[candidateRow][actualColumn];      
                highestValueRow = candidateRow;
            }
            free(returnValues[i]);
        }
        rowToMove = matrix[actualRow];
        matrix[actualRow] = matrix[highestValueRow];
        matrix[highestValueRow] = rowToMove;
        
        // Normalize all columns
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualColumn + (i * columnsPerThread) >= columnCount) {
                continue;
            }
            columnNormalize[i] = (ColumnNormalize*) malloc(sizeof(ColumnNormalize));
            columnNormalize[i]->actualRow = actualRow;
            columnNormalize[i]->matrix = matrix;
            
            columnNormalize[i]->baseColumn = actualColumn;
            columnNormalize[i]->actualColumn = actualColumn + (i * columnsPerThread);
            size_t maxCell = actualColumn + ((i + 1) * columnsPerThread) + 1;
            if(maxCell > columnCount) { 
                maxCell = columnCount;
            }
            columnNormalize[i]->rowCount = maxCell;
            result = pthread_create(&thread[i], NULL, normalizeColumnsInSelectionHandler, columnNormalize[i]);
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            
        }
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualColumn + (i * columnsPerThread) >= columnCount) {
                continue;
            }
            result = pthread_join(thread[i], NULL);
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            free(columnNormalize[i]);
        }
        matrix[actualRow][actualColumn] = 1;
        
        
        // Normalize all rows now
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualRow + (i * rowsPerThread) >= rowCount) {
                continue;
            }
            columnNormalize[i] = (ColumnNormalize*) malloc(sizeof(ColumnNormalize));
            columnNormalize[i]->actualColumn = actualColumn;
            columnNormalize[i]->matrix = matrix;
            
            columnNormalize[i]->baseColumn = actualRow;
            columnNormalize[i]->actualRow = actualRow + (i * rowsPerThread);
            size_t maxRow = actualRow + ((i + 1) * rowsPerThread) + 1;
            if(maxRow > rowCount) { 
                maxRow = rowCount;
            }
            columnNormalize[i]->rowCount = maxRow;
            result = pthread_create(&thread[i], NULL, normalizeRowsInSelectionHandler, columnNormalize[i]);
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            
        }
        for(int i = 0; i < amountOfThreads; i++) {
            if(actualRow + (i * rowsPerThread) >= rowCount) {
                continue;
            }
            result = pthread_join(thread[i], NULL);
            if(result != CODE_OK) {
                return CODE_CANT_CREATE_THREAD;
            }
            free(columnNormalize[i]);
        }
    }
    
    return CODE_OK;
}

void *normalizeRowsInSelectionHandler(void *args) {
    ColumnNormalize *params = (ColumnNormalize*)args;
    normalizeRowsInSelection(params->matrix, params->actualRow, 
            params->actualColumn, params->rowCount, params->baseColumn);
    return NULL;
}

void normalizeRowsInSelection(floattype **matrix, size_t actualRow, 
        size_t actualColumn, size_t rowCount, size_t baseRow){
    for(size_t rowToNormalize = actualRow + 1; rowToNormalize < rowCount;
            rowToNormalize++) {
        countNewValueColumns(matrix, baseRow, rowToNormalize, actualColumn, rowCount + 1);
        matrix[rowToNormalize][actualColumn] = 0;
    }
}

void countNewValueColumns(floattype **matrix, size_t actualRow, 
        size_t rowToNormalize, size_t actualColumn, size_t rowCount) {
    for(size_t colToNormalize = actualColumn+1; colToNormalize < rowCount;
            colToNormalize++) {
        matrix[rowToNormalize][colToNormalize] = 
                matrix[rowToNormalize][colToNormalize] - 
                (matrix[rowToNormalize][actualColumn] * matrix[actualRow][colToNormalize]);
    }    
}

void *normalizeColumnsInSelectionHandler(void *args) {
    ColumnNormalize *params = (ColumnNormalize*)args;
    normalizeColumnsInSelection(params->matrix, params->actualRow, params->actualColumn, params->rowCount, params->baseColumn);
    return NULL;
}

void normalizeColumnsInSelection(floattype **matrix, size_t actualRow, size_t actualColumn, size_t rowCount, size_t baseColumn) {
    for(size_t columnToNormalize = actualColumn + 1; columnToNormalize < rowCount; 
                columnToNormalize++) {
        matrix[actualRow][columnToNormalize] = 
                matrix[actualRow][columnToNormalize] / matrix[actualRow][baseColumn];
    }   
}


void *highestValueRowInSelectionHandler(void *args){
    HighestValueRowParameters *params = (HighestValueRowParameters*)args;
    size_t *returns = (size_t*) malloc (sizeof(size_t));
    *returns = highestValueRowInSelection(params->matrix, params->actualRow,
            params->actualColumn, params->rowCount);
    pthread_exit((void*)returns);
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