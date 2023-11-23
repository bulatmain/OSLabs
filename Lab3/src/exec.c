#include <limits.h>

#include "lib/wrapper.h"
#include "lib/macros.h"
#include "lib/child.h"
#include "lib/parent.h"

#define xstr(a) str(a)
#define str(a) #a

#define fileNameScanFormat xstr(FILENAME_MAX)

// #ifdef __linux__
// #define fileNameSize 256
// #define fileNameScanFormat "%256s"
// #elif _WIN64
// #define fileNameSize 256
// #define fileNameScanFormat "%256s"
// #elif _WIN32
// #define fileNameSize 11
// #define fileNameScanFormat "%11s"
// #endif

void init_file(FILE** fp);
void init_shared_object(int* fd, shared_obj** shm, FILE* fp);
void free_shared_object(shared_obj* shm, int pid);

int main() {
    // Read fileName from console stdin
    FILE* fp = NULL;
    
    init_file(&fp);

    // Create shared memory object
    int fd; shared_obj* shm;
    init_shared_object(&fd, &shm, fp);

    // Create child process
    int pid = fork();

    if (pid == -1) {
        ERROR("Error: can not create child process!\n", fp,
        BAD_CREATE_CHILD_ERROR);
    } else if (pid > 0) {   
        parent_process_exec(shm);
        sem_destroy(&shm->read);
        sem_destroy(&shm->write);
    } else {
        child_process_exec(fd, &fp);
    }

    // Free resources
    fclose(fp);

    free_shared_object(shm, pid);

    return 0;
}


void init_file(FILE** fp) {
    char fileName[FILENAME_MAX];

    printf("Please, enter file name: ");
    if (scanf("%"fileNameScanFormat"s", fileName) == EOF) {
        ERROR("\nError: No file name entered\n", NULL,
        INVALID_ARG_ERROR);
    }

    // Open file in fp with fileName
    *fp = fopen(fileName, "r");
    if (*fp == NULL) {
        ERROR("Error: can not open file!\n", NULL,
        OPENING_FILE_ERROR);
    }
}

void init_shared_object(int* fd, shared_obj** shm, FILE* fp) {
    *fd = shm_open(shared_memory_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (*fd == 0) {
        ERROR("Error: can not create shared memory object\n", fp,
        BAD_CREATE_SHM_OBJ);
    }

    if (ftruncate(*fd, sizeof(wrapper)) == -1) {
        ERROR("Error: can not truncate shm_object descriptor\n", fp,
        BAD_FTRUNCATE);
    }

    *shm = mmap(NULL, sizeof(shared_obj), PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0); 
    if (*shm == MAP_FAILED) {
        ERROR("Error: mmap failed\n", fp,
        BAD_MMAP);
    }

    if (sem_init(&(*shm)->read, 1, 0) == -1) {
        ERROR("Error: can not create interprocess semaphore\n", fp,
        BAD_CREATE_SEM);
    }

    if (sem_init(&(*shm)->write, 1, 1) == -1) {
        ERROR("Error: can not create interprocess semaphore\n", fp,
        BAD_CREATE_SEM);
    }
}

void free_shared_object(shared_obj* shm, int pid) {
    if (munmap(shm, sizeof(shared_obj)) == -1) {
        ERROR("Error: can not unmap shared object\n", NULL,
        BAD_UNMAP);
    }
    if (pid > 0) {
        if (shm_unlink(shared_memory_file) == -1) {
            ERROR("Error: can not unlink shared memory filename from memory object\n", NULL,
            BAD_SHM_UNLINK);
        } 
    }
}