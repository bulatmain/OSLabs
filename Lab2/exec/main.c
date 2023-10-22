#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


#include "lib/planner.h"
#include "lib/macroses.h"

#define INVALID_ARGIMENTS_ERROR_MESSSAGE \
"ERROR: Wrong arguments.\nThere should be 2 arguments: first - filename of image and second - K\n"

#define DATA_N_PARAMS_INITIALIZATION_ERROR \
"ERROR: Runtime error while initializing tech_data and tech_params\n"

#define CREATING_PIPE_ERROR \
"ERROR: Can not create interprocess pipe\n"

#define CREATING_PROCESS_ERROR \
"ERROR: Can not create process\n"

tech_data* read_tech_data(const char* filename);
tech_params* read_tech_params(const char* str);

void handle_message(wrapper* message);

/*
    Arguments: <image_filename> <K>
*/
int main(int argc, char** argv) {

    if (argc != 3) {
        ERROR(
            INVALID_ARGIMENTS_ERROR_MESSSAGE,
            INVALID_ARGUMENTS_ERRO
        );
    } 

    tech_data* data = read_tech_data(argv[1]);
    tech_params* params = read_tech_params(argv[2]);

    if (data == NULL || params == NULL) {
        ERROR(
            DATA_N_PARAMS_INITIALIZATION_ERROR,
            RUNTIME_ERROR
        );
    }


    // Make pipe
    int fd[2];
    if (pipe(fd) == -1) {
        ERROR(
            CREATING_PIPE_ERROR,
            RUNTIME_ERROR
        );
    }
    
    // Launch planner process and hand over data and paramethers to planner process

    pid_t pid = fork();

    if (pid == -1) {
        ERROR(
            CREATING_PROCESS_ERROR,
            RUNTIME_ERROR
        )
    } else if (pid > 0) {
        int pipe_in_no = fd[0];
        int pipe_out_no = fd[1];

        close(pipe_out_no);

        wrapper message;
        do {
            handle_message(&message);
        } while (message.code != END_CODE);
    } else {
        planner(data, params, fd);
    }

    // Write results in file



    return 0;
}
