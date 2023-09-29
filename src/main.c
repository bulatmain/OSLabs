#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define inf __INT_MAX__
#define eps 1e-9

#define dez(f) (f < 0 ? (-f) < eps : f < eps)

#define ERROR(message) { \
    printf(message);     \
    if (fp != NULL) {    \
        fclose(fp);      \
    }                    \
    exit(0);             \
}

union wrapper {
    double result;
    int code;
};

typedef union wrapper wrapper;

#define ERR_CODE -1
#define END_CODE 1
#define OK_CODE 0


wrapper calc_line() {

}

int main() {

    // 1. read fileName from console stdin

    char fileName[4096];
    FILE* fp = NULL;
    
    printf("Please, enter file name: ");
    if (scanf("%12s", fileName) == EOF) {
        ERROR("\nNo file name entered\nClosing...\n");
    }

    // 2. open file in fp with fileName

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        ERROR("Error: can not open file!\n");
    }

    // 3. create pipe fd

    int fd[2];
    if (pipe(fd) == -1) {
        ERROR("Error: can not create pipe!\n");
    }

    // 4. create child process


    int pid = fork();

    if (pid == -1) {
        ERROR("Error: can not create child process!\n");
    } else if (pid > 0) {   
// Parent       

        // 1. pipe    -> pstdin
        //    pstdout -> console

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            ERROR("Error: cannot redefine parent input thread!\n");
        }

        // 2. close output pipe

        close(fd[1]);  

        // 3. Create and initialize message
        ssize_t nbytes;
        wrapper message;
        message.result = 0;


        nbytes = read(fd[0], &message, sizeof(wrapper));

        if (nbytes == 0) {
            ERROR("Error: for some reason there's nothing to read from pipe!\n")
        }

        // 4. if error_code -> exit
        //    else          -> print answer in console and exit

        if (message.code == ERR_CODE) {
            printf("Division by zero ocured!\n");
        } else {
            printf("Result: %lf\n", message.result);
        }

        fclose(fp);

    } else {
// Child

        // 1. fp      -> cstdin
        //    cstdout -> pipe

        if (dup2(fileno(fp), STDIN_FILENO) == -1) {
            ERROR("Error: can not redefine child input thread!\n");
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            ERROR("Error: can not redefine child output thread!\n");
        }

        // 2. close input pipe

        close(fd[0]);

        // 3. calc function

        double dividend, dividor;

        int code_1 = scanf("%lf", &dividend);
        if (code_1 == EOF) {
            ERROR("Error: given file is empty!\n");
        }
        int code_2 = scanf("%lf", &dividor);

        if (code_2 != EOF) {
            while (!dez(dividor)) {
                dividend /= dividor;
                if (scanf("%lf", &dividor) == EOF) {
                    break;
                }
            }
        }

        // 4. Pack message
        wrapper message;

        if (dez(dividor)) {
            message.result = 0;
            message.code = ERR_CODE;
        } else {
            message.result = dividend;
            message.code = OK_CODE;
        }

        // 5. Write message to pipe

        write(fd[1], &message, sizeof(wrapper));

    }

    return 0;
}