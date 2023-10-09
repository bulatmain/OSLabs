#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "lib/wrapper.h"
#include "lib/macros.h"


// PIPE:
// write -> 1,
// 0  -> read.

void parent_process_exec(const int pipe_in_fo, const int pipe_out_fo, FILE* const * fp) {
// Parent        
    // 1. pipe    -> pstdin
    //    pstdout -> console
    if (dup2(pipe_in_fo, STDIN_FILENO) == -1) {
        ERROR("Error: cannot redefine parent input thread!\n", *fp, 
        DUP2_ERROR);
    }

    // 2. close output pipe
    close(pipe_out_fo);  

    // 3. Create and initialize message
    ssize_t nbytes;
    wrapper message;
    message.code = OK_CODE;
    message.result = 1.23f;

    // 4. if error_code -> exit
    //    else          -> print answer in console and exit
    size_t count = 1;

    while (message.code != END_CODE) {
        nbytes = read(pipe_in_fo, &message, sizeof(wrapper));
        if (nbytes == 0) {
            ERROR("Error: for some reason there's nothing to read from pipe!\n", *fp, 
            READ_FROM_PIPE_ERROR);
        } else if (message.code == ERR_DIV_BY_ZERO_CODE) {
            ERROR("Error: division by zero ocured!\n", *fp,
            ERR_DIV_BY_ZERO_CODE);
        } else if (message.code == ERR_EMPTY_FILE) {
            ERROR("Error: empty file given!\n", *fp,
            ERR_EMPTY_FILE);
        } else if (message.code == END_CODE) {
            break;
        } else {
            printf("%ld result: %lf\n", count++, message.result);
        }   
    }

    close(pipe_in_fo);
}



    