

#ifndef PLANNER_H

#define PLANNER_H

#include "structures.h"
#include "tasks.h"

#ifndef STRUCTURE_ELEMENT_SIZE
#define STRUCTURE_ELEMENT_SIZE 3
#endif

void planner(tech_data* data, tech_params* params, int fd[]);

#endif