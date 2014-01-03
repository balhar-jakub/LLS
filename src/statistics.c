#include <stdio.h>
#include <time.h>

#include "statistics.h"

size_t sizeOfGramMatrix;
time_t startTimestamp;

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
