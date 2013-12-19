/* 
 * File:   types.h
 * Author: Jakub Balhar
 *
 * This file contains types used throughout the application.
 */
#ifndef TYPES_H_
#define TYPES_H_
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
    
    typedef struct matrix_file_header {
        ULong64_t rowcount;  //počet řádků matice, malý endián
        ULong64_t colcount; //počet sloupců matice, malý endián
    } MatrixFileHeader;
    
    typedef struct {
        MatrixFileHeader header;
        floattype **matrix;
    } Matrix;

#endif
    