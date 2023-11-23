#include "lib/parent.h"

void parent_process_exec(shared_obj* shm) {
// Parent
    // Create and initialize message
    wrapper message = {
        .code = OK_CODE
    };

    // if error_code -> exit
    // else          -> print answer in console and exit
    size_t count = 1;

    while (message.code != END_CODE) {
        sem_wait(&shm->read);
        message = shm->message;
        sem_post(&shm->write);
        if (message.code == ERR_DIV_BY_ZERO_CODE) {
            ERROR("Error: division by zero ocured!\n", NULL,
            ERR_DIV_BY_ZERO_CODE);
        } else if (message.code == ERR_EMPTY_FILE) {
            ERROR("Error: empty file given!\n", NULL,
            ERR_EMPTY_FILE);
        } else if (message.code == END_CODE) {
            break;
        } else {
            printf("%ld result: %lf\n", count++, message.result);
        }   
    }
}



    