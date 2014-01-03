/* 
 * File:   lls.h
 * Author: balhar
 *
 * Created on 3. leden 2014, 10:22
 */

#include "types.h"

#ifndef LLS_H
#define	LLS_H

#ifdef	__cplusplus
extern "C" {
#endif


    HRESULT SolveLLS4Plus(floattype **extendedmatrix, size_t paramcount, size_t rowcount, floattype *result);
    int solveLLS(int argc, char **argv);

#ifdef	__cplusplus
}
#endif

#endif	/* LLS_H */

