#include <stdio.h>
#include <stdbool.h>
#include "parameters.h"

size_t getParamSize(char *arg){
    return (size_t) strtol(arg, NULL, 10);
}

bool getParamBool(char *arg){
    return (bool) strtol(arg, NULL, 10);
}
