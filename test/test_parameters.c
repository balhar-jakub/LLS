/*
 * File:   test_parameters.c
 * Author: Jakub Balhar
 *
 * Created on 19.12.2013, 9:13:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../src/types.h"
#include "../src/codes.h"
#include "../src/parameters.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testGetParamSize() {
    char* arg = (char*) "10";
    size_t result = getParamSize(arg);
    CU_ASSERT(result == 10);
}

void testGetParamBasic() {
    int argc = 3;
    char *argv[] = {(char*)"lls",(char*)"5",(char*)"4"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT_FATAL(params != NULL);
    
    CU_ASSERT(params->rows == 5);
    CU_ASSERT(params->columns == 4);
    CU_ASSERT(params->isZeroOk == false);
    CU_ASSERT(params->filePath == NULL);
    CU_ASSERT(params->loadFile == false);
    CU_ASSERT(params->saveFile == false);
    free(params);
}

void testGetParamZeroOnly() {
    int argc = 4;
    char *argv[] = {(char*)"lls",(char*)"5",(char*)"4",(char*)"-z"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT_FATAL(params != NULL);
    CU_ASSERT(params->isZeroOk == true);
    free(params);
}

void testGetParamSaveFile() {
    int argc = 5;
    char *argv[] = {(char*)"lls",(char*)"5",(char*)"4",(char*)"-w", (char*)"saveFilePath"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT_FATAL(params != NULL);
    CU_ASSERT(params->saveFile == true);
    CU_ASSERT(strcmp(params->filePath,"saveFilePath") == 0);
    free(params);
}

void testGetParamLoadFile() {
    int argc = 5;
    char *argv[] = {(char*)"lls",(char*)"5",(char*)"4",(char*)"-l",(char*)"loadFilePath"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT_FATAL(params != NULL);
    CU_ASSERT(params->loadFile == true);
    CU_ASSERT(strcmp(params->filePath,"loadFilePath") == 0);
    free(params);
}

void testGetParamNotEnoughParams() {
    int argc = 2;
    char *argv[] = {(char*)"lls",(char*)"5"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT(params == NULL);
    
    CU_ASSERT(errorCode == CODE_NOT_ENOUGH_PARAMETERS);
    free(params);
}

void testGetParamParamEndsAfterWOrL() {
    int argc = 4;
    char *argv[] = {(char*)"lls",(char*)"5",(char*)"4",(char*)"-w"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT(params == NULL);
    
    CU_ASSERT(errorCode == CODE_MALFORMED_PARAMETERS);
    free(params);
}

void testGetParamMutualExclusive() {
    int argc = 7;
    char *argv[] = {(char*)"lls",(char*)"5", (char*)"4", (char*)"-w", 
        (char*)"savePath", (char*)"-l", (char*)"loadPath"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT(params == NULL);
    
    CU_ASSERT(errorCode == CODE_MUTUAL_EXCLUSIVE_PARAMETERS);
    free(params);
}

void testGetParamMutualExclusiveOther() {
    int argc = 7;
    char *argv[] = {(char*)"lls",(char*)"5", (char*)"4", (char*)"-l", 
        (char*)"savePath", (char*)"-w", (char*)"loadPath"};
    int errorCode = 0;
    Parameters *params = getParams(argc, argv, &errorCode);
    CU_ASSERT(params == NULL);
    
    CU_ASSERT(errorCode == CODE_MUTUAL_EXCLUSIVE_PARAMETERS);
    free(params);
}


int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_parameters", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testGetParamSize", testGetParamSize)) ||
            (NULL == CU_add_test(pSuite, "testGetParamBasic", testGetParamBasic)) ||
            (NULL == CU_add_test(pSuite, "testGetParamZeroOnly", testGetParamZeroOnly)) ||
            (NULL == CU_add_test(pSuite, "testGetParamLoadFile", testGetParamLoadFile)) ||
            (NULL == CU_add_test(pSuite, "testGetParamSaveFile", testGetParamSaveFile)) ||
            (NULL == CU_add_test(pSuite, "testGetParamNotEnoughParams", testGetParamNotEnoughParams)) ||
            (NULL == CU_add_test(pSuite, "testGetParamParamEndsAfterWOrL", testGetParamParamEndsAfterWOrL)) ||
            (NULL == CU_add_test(pSuite, "testGetParamMutualExclusive", testGetParamMutualExclusive)) ||
            (NULL == CU_add_test(pSuite, "testGetParamMutualExclusiveOther", testGetParamMutualExclusiveOther))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
