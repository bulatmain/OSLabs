#ifndef SHARED_H

#define SHARED_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "lib/wrapper.h"
#include "lib/macros.h"

#define shared_memory_file "/shm_obj"

#endif