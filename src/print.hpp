/* 
 * File:   print.hpp
 * Author: balhar
 *
 * Created on 3. leden 2014, 11:34
 */
#include <stdio.h>
#include "types.h"

#ifndef PRINT_HPP
#define	PRINT_HPP

void printMatrix(floattype **matrix, size_t rowCount, size_t columnCount);
void PrintResultComputation(HRESULT resultCode, size_t rows, floattype *result);

#endif	/* PRINT_HPP */

