/* 
 * File:   memory.h
 * Author: balhar
 *
 * Created on 18. prosinec 2013, 9:15
 */
#include "types.h"
#include <stdio.h>

#ifndef MEMORY_H
#define	MEMORY_H

#ifdef	__cplusplus
extern "C" {
#endif

floattype **AllocMatrix(size_t rowCount, size_t columnCount);
floattype *AllocRow(size_t rowSize);
void FreeMatrix(floattype **matrix, size_t rowCount);
floattype *AllocResult(size_t rowSize);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORY_H */

