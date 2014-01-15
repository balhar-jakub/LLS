/*
 * File:   test_gem.c
 * Author: Jakub Balhar
 *
 * Test suite for gem implementation in this project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../src/gem.h"
#include "../src/codes.h"
#include "../src/types.h"
#include "../src/memory.h"
#include "../src/print.hpp"

/*
 * CUnit Test Suite
 */

void assertMatricesAreSame(floattype **expected, floattype **result, 
        MatrixFileHeader *resultHeader);

int init_suite(void) {
    printf("\n Start test");
    return 0;
}

int clean_suite(void) {
    printf("\n End test");
    return 0;
}

void testSolveGemBasic() {
    size_t rowCount = 4;
    size_t columnCount = 5;
    
    floattype** matrix = AllocMatrix(rowCount, columnCount);
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;
    matrix[0][4] = 2;
    
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[1][3] = 0;
    matrix[1][4] = 9;
    
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;
    matrix[2][4] = 6;
    
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
    matrix[3][4] = 6;
    
    
    floattype** expected = AllocMatrix(rowCount, columnCount);
    expected[0][0] = 1;
    expected[0][1] = 0;
    expected[0][2] = 0;
    expected[0][3] = 0;
    expected[0][4] = 2;
    
    expected[1][0] = 0;
    expected[1][1] = 1;
    expected[1][2] = 0;
    expected[1][3] = 0;
    expected[1][4] = 9;
    
    expected[2][0] = 0;
    expected[2][1] = 0;
    expected[2][2] = 1;
    expected[2][3] = 0;
    expected[2][4] = 6;
    
    expected[3][0] = 0;
    expected[3][1] = 0;
    expected[3][2] = 0;
    expected[3][3] = 1;
    expected[3][4] = 6;
    
    int result = solveGemSquare(matrix, rowCount);
    CU_ASSERT(result == CODE_OK);
    
    MatrixFileHeader *header = (MatrixFileHeader*) malloc(sizeof(MatrixFileHeader));
    header->colcount = columnCount;
    header->rowcount = rowCount;
    assertMatricesAreSame(expected, matrix, header);
    
    free(header);
    FreeMatrix(matrix, rowCount);
    FreeMatrix(expected, rowCount);
}

void testSolveGemMoreComplicated() {
    size_t rowCount = 3;
    size_t columnCount = 4;
    
    floattype** matrix = AllocMatrix(rowCount, columnCount);
    matrix[0][0] = 8;
    matrix[0][1] = 5;
    matrix[0][2] = 1;
    matrix[0][3] = 2;
    
    matrix[1][0] = 3;
    matrix[1][1] = 4;
    matrix[1][2] = 1;
    matrix[1][3] = 5;
    
    matrix[2][0] = 4;
    matrix[2][1] = 8;
    matrix[2][2] = 7;
    matrix[2][3] = 2;
    
    floattype** expected = AllocMatrix(rowCount, columnCount);
    expected[0][0] = 1;
    expected[0][1] = 0.625;
    expected[0][2] = 0.125;
    expected[0][3] = 0.25;
    
    expected[1][0] = 0;
    expected[1][1] = 1;
    expected[1][2] = 1.181818;
    expected[1][3] = 0.181818;
    
    expected[2][0] = 0;
    expected[2][1] = 0;
    expected[2][2] = 1;
    expected[2][3] = -2.445783;
    
    int result = solveGemSquare(matrix, rowCount);
    CU_ASSERT(result == CODE_OK);
    
    MatrixFileHeader *header = (MatrixFileHeader*) malloc(sizeof(MatrixFileHeader));
    header->colcount = columnCount;
    header->rowcount = rowCount;
    assertMatricesAreSame(expected, matrix, header);
    
    free(header);
    FreeMatrix(matrix, rowCount);
    FreeMatrix(expected, rowCount);
}

void testSolveGemPivotingBasic() {
    size_t rowCount = 3;
    size_t columnCount = 4;
    
    floattype** matrix = AllocMatrix(rowCount, columnCount);
    matrix[0][0] = 0;
    matrix[0][1] = 4;
    matrix[0][2] = 1;
    matrix[0][3] = 5;
    
    matrix[1][0] = 8;
    matrix[1][1] = 5;
    matrix[1][2] = 1;
    matrix[1][3] = 2;
    
    matrix[2][0] = 4;
    matrix[2][1] = 8;
    matrix[2][2] = 7;
    matrix[2][3] = 2;
    
    floattype** expected = AllocMatrix(rowCount, columnCount);
    expected[0][0] = 1;
    expected[0][1] = 0.625;
    expected[0][2] = 0.125;
    expected[0][3] = 0.25;
    
    expected[1][0] = 0;
    expected[1][1] = 1;
    expected[1][2] = 1.181818;
    expected[1][3] = 0.181818;
    
    expected[2][0] = 0;
    expected[2][1] = 0;
    expected[2][2] = 1;
    expected[2][3] = -1.146341;
    
    int result = solveGemSquare(matrix, rowCount);
    CU_ASSERT(result == CODE_OK);
    
    MatrixFileHeader *header = (MatrixFileHeader*) malloc(sizeof(MatrixFileHeader));
    header->colcount = columnCount;
    header->rowcount = rowCount;
    assertMatricesAreSame(expected, matrix, header);
    
    free(header);
    FreeMatrix(matrix, rowCount);
    FreeMatrix(expected, rowCount);
}

void testSolveGemPivotingMoreComplicated() {
    size_t rowCount = 3;
    size_t columnCount = 4;
    
    floattype** matrix = AllocMatrix(rowCount, columnCount);
    matrix[0][0] = 0.0001;
    matrix[0][1] = 4;
    matrix[0][2] = 1;
    matrix[0][3] = 5;
    
    matrix[1][0] = 8;
    matrix[1][1] = 0.0001;
    matrix[1][2] = 1;
    matrix[1][3] = 2;
    
    matrix[2][0] = 4;
    matrix[2][1] = 8;
    matrix[2][2] = 0.0001;
    matrix[2][3] = 2;
    
    floattype** expected = AllocMatrix(rowCount, columnCount);
    expected[0][0] = 1;
    expected[0][1] = 0.000013;
    expected[0][2] = 0.125;
    expected[0][3] = 0.25;
    
    expected[1][0] = 0;
    expected[1][1] = 1;
    expected[1][2] = -0.062488;
    expected[1][3] = 0.125001;
    
    expected[2][0] = 0;
    expected[2][1] = 0;
    expected[2][2] = 1;
    expected[2][3] = 3.600173;
    
    int result = solveGemSquare(matrix, rowCount);
    CU_ASSERT(result == CODE_OK);
    
    MatrixFileHeader *header = (MatrixFileHeader*) malloc(sizeof(MatrixFileHeader));
    header->colcount = columnCount;
    header->rowcount = rowCount;
    assertMatricesAreSame(expected, matrix, header);
    
    free(header);
    FreeMatrix(matrix, rowCount);
    FreeMatrix(expected, rowCount);
}

void assertMatricesAreSame(floattype **expected, floattype **result, 
        MatrixFileHeader *resultHeader) {
    if(resultHeader->rowcount == 0 && resultHeader->colcount == 0){
        return;
    }
    for(size_t i = 0; i < resultHeader->rowcount; i++) {
        for(size_t j = 0; j < resultHeader->colcount; j++) {
            CU_ASSERT_DOUBLE_EQUAL(expected[i][j], result[i][j], 0.00001);
        }
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_gem", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testSolveGemBasic", testSolveGemBasic)) ||
            (NULL == CU_add_test(pSuite, "testSolveGemMoreComplicated", testSolveGemMoreComplicated)) ||
            (NULL == CU_add_test(pSuite, "testSolveGemPivotingBasic", testSolveGemPivotingBasic)) ||
            (NULL == CU_add_test(pSuite, "testSolveGemPivotingMoreComplicated", testSolveGemPivotingMoreComplicated))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
