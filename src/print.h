/* 
 * File:   print.h
 * Author: balhar
 *
 * Created on 28. prosinec 2013, 9:55
 */
#include <stdio.h>
#include "types.h"

#ifndef PRINT_H
#define	PRINT_H

#ifdef	__cplusplus
extern "C" {
#endif

    void printMatrix(floattype **matrix, size_t rowCount, size_t columnCount);


#ifdef	__cplusplus
}
#endif

#endif	/* PRINT_H */

