/* 
 * File:   parameters.h
 * Author: Jakub Balhar
 *
 * This part of program handles parsing parameters received from user via the 
 * command line
 */
#include <stdio.h>
#include <stdbool.h>
#include "types.h"

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#ifdef	__cplusplus
extern "C" {
#endif

    size_t getParamSize(char *arg);
    
    /*
     * The application has some amount of possibilities how it can be called:
     * 
     * lls {amountOfRecordedValues} {amountOfParameters}
     * These two parameters are required
     * 
     * There are some optional arguments to the application
     * -z If this option is present, zero can be in generated matrix.
     * -w {filePath} If this option is present, write generated matrix into the file
     *      which follows this argument.
     * -l {filePath} If this option is present, load matrix to solve from file, 
     *      which follows this argument.
     * 
     * Any other arguments will be ignored
     */
    Parameters *getParams(int argc, char **argv, int *errCode);

#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_H */

