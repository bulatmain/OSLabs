#ifndef TASKS_H

#define TASKS_H

#include "structures.h"

struct tech_data
{
    float** image;
    size_t n;
    size_t m;
};
typedef struct tech_data tech_data;

struct tech_params
{
    size_t n;
    size_t m;
    size_t k;
};
typedef struct tech_params tech_params;

struct elementary_task {
    tech_data* task;
    size_t i;
    size_t j;
};
typedef struct elementary_task elementary_task;

enum task_type {
    EROSION,
    EXTENTION
};
typedef enum task_type task_type;

void calculate_erosion(elementary_task* task);

void calculate_extention(elementary_task* task);

void execute_task(elementary_task* task, task_type type);

#endif