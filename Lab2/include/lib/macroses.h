#ifndef MACROSES_H

#define MACROSES_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR(message, error_code) { \
    printf(message);                 \
    exit(error_code);                \
}

#define RUNTIME_ERROR -1
#define LOGIC_ERROR -2
#define INVALID_ARGUMENTS_ERRO -3

#endif