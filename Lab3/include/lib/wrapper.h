#ifndef WRAPPER_H

#define WRAPPER_H

#include <semaphore.h>

struct wrapper {
    double result;
    int code;
};

typedef struct wrapper wrapper;

struct shared_obj {
    wrapper message;
    sem_t read;
    sem_t write;
};

typedef struct shared_obj shared_obj;

#endif