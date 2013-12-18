/* 
 * File:   test_files.c
 * Author: balhar
 * 
 * Created on 17. prosinec 2013, 16:51
 */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../src/files.h"
#include "../src/types.h"
#include "../src/codes.h"
#include "../src/memory.h"

void assertMatricesAreSame(floattype **expected, floattype **result, 
        MatrixFileHeader *resultHeader);

static FILE *matrixFile;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
    matrixFile = fopen("test/matrix_to_save","wb");
    if(matrixFile == NULL) {
        return CODE_NO_FILE;
    } else {
        return CODE_OK;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
    int result = fclose(matrixFile);
    if(result != CODE_OK) {
        return CODE_CANT_CLOSE;
    }
    return CODE_OK;
}

void testSaveMatrix(void) {
    size_t columns = 3;
    size_t rows = 3;
    floattype **matrix = AllocMatrix(rows, columns);
    floattype **expected = AllocMatrix(rows, columns);
    
    CU_ASSERT(CODE_OK == saveMatrix(matrix, matrixFile, rows, columns));
    FreeMatrix(matrix, rows);
    
    MatrixFileHeader header = {0, 0};
    matrix = loadMatrix(matrixFile, &header);
    CU_ASSERT(NULL != matrix);
    if(NULL == matrix) {
        FreeMatrix(expected, rows);
        return;
    }
    printf("%llu %llu\n", header.colcount, header.rowcount);
    
    CU_ASSERT(3 == header.rowcount);
    CU_ASSERT(3 == header.colcount);
    
    assertMatricesAreSame(expected, matrix, &header);
    
    FreeMatrix(matrix, rows);
    FreeMatrix(expected, rows);
}

void assertMatricesAreSame(floattype **expected, floattype **result, 
        MatrixFileHeader *resultHeader) {
    if(resultHeader->rowcount == 0 && resultHeader->colcount == 0){
        return;
    }
    for(size_t i = 0; i < resultHeader->rowcount; i++) {
        for(size_t j = 0; j < resultHeader->colcount; j++) {
            CU_ASSERT(expected[i][j] == result[i][j]);
        }
    }
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
    pSuite = CU_add_suite("test_files", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testSaveMatrix", testSaveMatrix))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}