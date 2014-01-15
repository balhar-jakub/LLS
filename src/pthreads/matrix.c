#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "../matrix.h"
#include "../types.h"
#include "../memory.h"
#include "../random.h"
#include "../codes.h"
#include "../print.hpp"

void countOneCell(floattype **matrix, floattype **gramMatrix, size_t row, size_t cell, size_t columns);

typedef struct {
    floattype **matrix;
    floattype **gramMatrix;
    
    size_t row;
    size_t cell;
    size_t columns;
    size_t cells;
} CountCellParameters;
void *countOneCellHandler(void *arg);
int cellsPerThread = 4;

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
    int amountOfTasks = (rows * ceil((double)((double)rows / (double)cellsPerThread)));
    int actualTask = 0, result = CODE_OK;
    CountCellParameters *params[amountOfTasks];
    pthread_t thread[amountOfTasks];
    
    for(size_t row = 0; row < rows; row++) {
        for(size_t cell = 0; cell < rows; cell += cellsPerThread){
            params[actualTask] = (CountCellParameters*) malloc (sizeof(CountCellParameters));
            params[actualTask]->cell = cell;
            params[actualTask]->columns = columns;
            params[actualTask]->row = row;
            params[actualTask]->matrix = matrix;
            params[actualTask]->gramMatrix = gramMatrix;
            if(cell + cellsPerThread >= rows) {
                params[actualTask]->cells = rows - cell;
            } else {
                params[actualTask]->cells = cellsPerThread;
            }
            
            
            //Go through all the positions in the final matrix.
            result = pthread_create(&thread[actualTask], NULL, countOneCellHandler, params[actualTask]);
            if(result != CODE_OK) {
                return NULL;
            }
            //countOneCell(matrix, gramMatrix, row, cell, columns);
            actualTask++;
        }
        gramMatrix[row][rows] = results[row];
    }
    for(int i = 0; i < amountOfTasks; i++) {
        result = pthread_join(thread[i], NULL);
        if(result != CODE_OK) {
            return NULL;
        }
        free(params[i]);
    }
            
    return gramMatrix;
}

void countOneCell(floattype **matrix, floattype **gramMatrix, size_t row, size_t cell, size_t columns) {
    floattype sum = 0;
    for(size_t positionInVector = 0; positionInVector < columns; positionInVector++){
        sum += (matrix[row][positionInVector] * matrix[cell][positionInVector]);
    }
    gramMatrix[row][cell] = sum;
}

void *countOneCellHandler(void *args) {
    CountCellParameters *params = (CountCellParameters*)args;
    for(size_t i = 0; i < params->cells; i++) {
        countOneCell(params->matrix, params->gramMatrix, params->row, params->cell + i,
            params->columns);
    }
    return NULL;
}