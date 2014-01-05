/*
 * File:   test_lls.c
 * Author: balhar
 *
 * Created on 3.1.2014, 10:26:39
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../src/codes.h"
#include "../src/lls.h"
#include "../src/types.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testSolveLLS() {
    char *argv[] = {(char*)"lls",(char*)"4",(char*)"4"};
    int result = solveLLS(3, argv);
    
    CU_ASSERT(result == CODE_OK);
}

void testSolveLLS_Rectangle() {
    char *argv[] = {(char*)"lls",(char*)"6",(char*)"4"};
    int result = solveLLS(3, argv);
    
    printf("Result: %d\n", result);
    CU_ASSERT(result == CODE_OK);
}

void testSolveLLS_Err() {
    char *argv[] = {(char*)"lls",(char*)"5"};
    int result = solveLLS(2, argv);
    CU_ASSERT(result == CODE_NOT_ENOUGH_PARAMETERS);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_lls", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testSolveLLS4Plus", testSolveLLS)) ||
            (NULL == CU_add_test(pSuite, "testSolveLLS4PlusErr", testSolveLLS_Err)) ||
            (NULL == CU_add_test(pSuite, "testSolveLLS4PlusRectangle", testSolveLLS_Rectangle))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
