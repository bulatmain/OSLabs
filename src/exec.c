#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "lib/wrapper.h"
#include "lib/macros.h"
#include "lib/child.h"
#include "lib/parent.h"

#define fileNameSize 4096
#define fileNameScanFormat "%4096s"

int main() {

    // 1. read fileName from console stdin

    char fileName[fileNameSize];
    FILE* fp = NULL;
    
    printf("Please, enter file name: ");
    if (scanf(fileNameScanFormat, fileName) == EOF) {
        ERROR("\nNo file name entered\nClosing...\n", NULL,
        INVALID_ARG_ERROR);
    }

    // 2. open file in fp with fileName

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        ERROR("Error: can not open file!\n", NULL,
        OPENING_FILE_ERROR);
    }

    // 3. create pipe fd

    int fd[2];
    if (pipe(fd) == -1) {
        ERROR("Error: can not create pipe!\n", fp,
        BAD_CREATE_PIPE_ERROR);
    }

    // 4. create child process


    int pid = fork();

    if (pid == -1) {
        ERROR("Error: can not create child process!\n", fp,
        BAD_CREATE_CHILD_ERROR);
    } else if (pid > 0) {   
        child_process_exec(fd[0], fd[1], &fp);
    } else {
        parent_process_exec(fd[0], fd[1], &fp);
    }

    return 0;
}