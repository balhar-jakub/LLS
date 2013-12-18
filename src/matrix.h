/* 
 * File:   matrix.h
 * Author: balhar
 *
 * Created on 17. prosinec 2013, 16:30
 */
#include "types.h"

#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

void GenerateDataForMatrix(
    floattype **matrix, 
    size_t rowCount, 
    size_t columnCount, 
    bool isZeroOk
);

floattype **GenerateMatrix(
    floattype **matrix, 
    size_t gramRows, 
    size_t parametersInRow,
    floattype *results
); 


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

