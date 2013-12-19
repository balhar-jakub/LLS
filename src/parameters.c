#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "codes.h"
#include "parameters.h"

void setSaneDefaults(Parameters *params);

size_t getParamSize(char *arg){
    return (size_t) strtol(arg, NULL, 10);
}

Parameters *getParams(int argc, char **argv, int *errCode) {
    Parameters *params = (Parameters*) malloc (sizeof(Parameters));
    
    setSaneDefaults(params);
    
    // The application has at least two required parameters.
    if(argc < 3) {
        (*errCode) = CODE_NOT_ENOUGH_PARAMETERS;
        free(params);
        return NULL;
    }
    
    params->rows = getParamSize(argv[1]);
    params->columns = getParamSize(argv[2]);
    
    for(int i = 3; i < argc; i++) {
        if(strcmp(argv[i],"-z") == 0){
            params->isZeroOk = true;            
        }
        if((strcmp(argv[i],"-w") == 0) || (strcmp(argv[i],"-l") == 0)) {
            if(i + 1 >= argc) {
                (*errCode) = CODE_MALFORMED_PARAMETERS;
                free(params);
                return NULL;
            }
            
            if((strcmp(argv[i],"-l")) == 0) {
                if(params->saveFile == true) {
                    (*errCode) = CODE_MUTUAL_EXCLUSIVE_PARAMETERS;
                    free(params);
                    return NULL;
                }
                params->loadFile = true;
            } else {
                if(params->loadFile == true) {
                    (*errCode) = CODE_MUTUAL_EXCLUSIVE_PARAMETERS;
                    free(params);
                    return NULL;
                }
                params->saveFile = true;
            }
            
            params->filePath = argv[i+1];
            i++;
        }
    }
    
    (*errCode) = CODE_OK;
    return params;
}

/*
 * It sets application parameters to same sane defaults. If user passes at least
 * required data, it will set everything else to sane.
 * 
 * 0 isn't ok as default
 * Matrix isn't loaded and neither is it saved.
 */
void setSaneDefaults(Parameters *params) {
    params->columns = 5;
    params->rows = 5;
    
    params->isZeroOk = false;
    params->filePath = NULL;
    params->saveFile = false;
    params->loadFile = false;
}
