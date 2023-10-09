#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "lib/wrapper.h"
#include "lib/macros.h"

wrapper calc_line();

void child_process_exec(const int pipe_in_fo, const int pipe_out_fo, FILE* const * fp) {
// Child

    // 1. fp      -> cstdin
    //    cstdout -> pipe

    if (dup2(fileno(*fp), STDIN_FILENO) == -1) {
        ERROR("Error: can not redefine child input thread!\n", *fp,
        DUP2_ERROR);
    }
    if (dup2(pipe_out_fo, STDOUT_FILENO) == -1) {
        ERROR("Error: can not redefine child output thread!\n", *fp,
        DUP2_ERROR);
    }

    close(pipe_in_fo);

    wrapper message;
    message.code = OK_CODE;

    //  0 if false, 1 if true. 
    char one_command_given = 0;

    while (message.code == OK_CODE) {
        message = calc_line(&one_command_given);

        write(pipe_out_fo, &message, sizeof(wrapper));

        one_command_given = 1;
    }

    close(pipe_out_fo);
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
    while (!dez(dividor)) {
        if ((scanf(" %lf", &dividor) == EOF) ||
            (getchar() == '\n')) {
            break;
        }
        dividend /= dividor;
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