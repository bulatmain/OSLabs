#include "lib/child.h"

wrapper calc_line();

void child_process_exec(const int fd, FILE** fp) {
// Child
    // fp      -> cstdin
    if (dup2(fileno(*fp), STDIN_FILENO) == -1) {
        ERROR("Error: can not redefine child input thread!\n", *fp,
        DUP2_ERROR);
    }

    // Get acces to shared memory object
    shared_obj *shm = mmap(NULL, sizeof(shared_obj), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    if (shm == MAP_FAILED) {
        ERROR("Error: mmap failed\n", NULL,
        BAD_MMAP);
    }

    // Create and initialize message
    wrapper message = {
        .code = OK_CODE
    };

    //  0 if false, 1 if true. 
    char one_command_given = 0;

    while (message.code == OK_CODE) {
        message = calc_line(&one_command_given);

        sem_wait(&shm->write);
        shm->message = message;
        sem_post(&shm->read);

        one_command_given = 1;
    }

    if (munmap(shm, sizeof(shared_obj)) == -1) {
        ERROR("Error: can not unmap shared object\n", NULL,
        BAD_UNMAP);
    } 
}


wrapper calc_line(char* one_command_given) {
    wrapper message;
    
    double dividend, dividor;

    int code_1 = scanf(" %lf", &dividend);
    if (code_1 == EOF) {
        message.result = 0;
        if (*one_command_given == 0) {
            message.code = ERR_EMPTY_FILE;
        } else if (*one_command_given == 1) {
            message.code = END_CODE;
        }
        return message;
    }
    dividor = 1;
    int code_2;
    while (!dez(dividor)) {
        code_2 = scanf(" %lf", &dividor);
        if (code_2 == EOF) {
            break;
        }
        dividend /= dividor;
        if (getchar() == '\n') {
            break;
        }
    }
    
    if (dez(dividor)) {
        message.result = 0;
        message.code = ERR_DIV_BY_ZERO_CODE;
    } else {
        message.result = dividend;
        message.code = OK_CODE;
    }
    return message;
}