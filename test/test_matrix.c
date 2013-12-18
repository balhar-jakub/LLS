/* 
 * File:   test_matrix.c
 * Author: balhar
 * 
 * Created on 18. prosinec 2013, 14:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../src/codes.h"
#include "../src/types.h"
#include "../src/matrix.h"
#include "../src/memory.h"

/* Pointer to the file used by the tests. */
void assertMatricesAreSame(floattype **expected, floattype **result, 
        size_t rows, size_t columns);

void assertMatricesAreSame(floattype **expected, floattype **result, 
        size_t rows, size_t columns) {
    if(rows == 0 && columns == 0){
        return;
    }
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < columns; j++) {
            CU_ASSERT(expected[i][j] == result[i][j]);
        }
    }
}

/* 
 */
int init_suite1(void) {
    return CODE_OK;
}

/* 
 */
int clean_suite1(void) {
    return CODE_OK;
}

void testGenerateSquare(void) {
    size_t rows = 4;
    size_t columns = 4;
    floattype **result;
    
    floattype **matrix = AllocMatrix(rows, columns);
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[0][3] = 1;
    
    matrix[1][0] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
    matrix[1][3] = 1;
    
    matrix[2][0] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 1;
    matrix[2][3] = 1;
    
    matrix[3][0] = 1;
    matrix[3][1] = 1;
    matrix[3][2] = 1;
    matrix[3][3] = 1;
    
    floattype * resultColumn = AllocRow(rows);
    resultColumn[0] = 5;
    resultColumn[1] = 5;
    resultColumn[2] = 5;
    resultColumn[3] = 5;
    
    floattype ** expected = AllocMatrix(rows, rows + 1);
    expected[0][0] = 4;
    expected[0][1] = 4;
    expected[0][2] = 4;
    expected[0][3] = 4;
    expected[0][4] = 5;
    
    expected[1][0] = 4;
    expected[1][1] = 4;
    expected[1][2] = 4;
    expected[1][3] = 4;
    expected[1][4] = 5;
    
    expected[2][0] = 4;
    expected[2][1] = 4;
    expected[2][2] = 4;
    expected[2][3] = 4;
    expected[2][4] = 5;
    
    expected[3][0] = 4;
    expected[3][1] = 4;
    expected[3][2] = 4;
    expected[3][3] = 4;
    expected[3][4] = 5;
    
    result = GenerateMatrix(matrix, rows, columns, resultColumn);
    
    assertMatricesAreSame(expected, result, rows, rows + 1);
    
    free(resultColumn);
    FreeMatrix(matrix, rows);
    FreeMatrix(expected, rows);
    FreeMatrix(result, rows);
}

void testGenerateRectangleCorrect(void) {
    size_t rows = 5;
    size_t columns = 3;
    floattype **result;
    
    floattype **matrix = AllocMatrix(rows, columns);
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    
    matrix[1][0] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
    
    matrix[2][0] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 1;
    
    matrix[3][0] = 1;
    matrix[3][1] = 1;
    matrix[3][2] = 1;
    
    matrix[4][0] = 1;
    matrix[4][1] = 1;
    matrix[4][2] = 1;
    
    floattype *resultColumn = AllocRow(rows);
    resultColumn[0] = 5;
    resultColumn[1] = 5;
    resultColumn[2] = 5;
    resultColumn[3] = 5;
    resultColumn[4] = 5;
    
    floattype ** expected = AllocMatrix(rows, rows + 1);
    expected[0][0] = 3;
    expected[0][1] = 3;
    expected[0][2] = 3;
    expected[0][3] = 3;
    expected[0][4] = 3;
    expected[0][5] = 5;
    
    expected[1][0] = 3;
    expected[1][1] = 3;
    expected[1][2] = 3;
    expected[1][3] = 3;
    expected[1][4] = 3;
    expected[1][5] = 5;
    
    expected[2][0] = 3;
    expected[2][1] = 3;
    expected[2][2] = 3;
    expected[2][3] = 3;
    expected[2][4] = 3;
    expected[2][5] = 5;
    
    expected[3][0] = 3;
    expected[3][1] = 3;
    expected[3][2] = 3;
    expected[3][3] = 3;
    expected[3][4] = 3;
    expected[3][5] = 5;
    
    expected[4][0] = 3;
    expected[4][1] = 3;
    expected[4][2] = 3;
    expected[4][3] = 3;
    expected[4][4] = 3;
    expected[4][5] = 5;
    
    result = GenerateMatrix(matrix, rows, columns, resultColumn);
    
    assertMatricesAreSame(expected, result, rows, rows+1);
    
    free(resultColumn);
    FreeMatrix(matrix, rows);
    FreeMatrix(expected, rows);
    FreeMatrix(result, rows);
}

void testGenerateRectangleTooManyColumns(void) {
    size_t rows = 3;
    size_t columns = 5;
    floattype **result;
    floattype **matrix = AllocMatrix(rows, columns);
    floattype *resultColumn = AllocRow(rows);
    
    result = GenerateMatrix(matrix, rows, columns, resultColumn);
    CU_ASSERT(result == NULL);
    
    free(resultColumn);
    FreeMatrix(matrix, rows);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("test_matrix", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "testGenerateSquare", testGenerateSquare)) ||
            (NULL == CU_add_test(pSuite, "testGenerateRectangleCorrect", testGenerateRectangleCorrect)) ||
            (NULL == CU_add_test(pSuite, "testGenerateRectangleTooManyColumns", testGenerateRectangleTooManyColumns))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
