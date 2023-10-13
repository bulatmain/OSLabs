#define inf __INT_MAX__
#define eps 1e-9

#define dez(f) (f < 0 ? (-f) < eps : f < eps)

#define ERROR(message, fp, ERROR_CODE) { \
    printf((message));       \
    if ((fp) != NULL) {      \
        fclose((fp));        \
    }                        \
    exit(ERROR_CODE);        \
}

#define ERR_DIV_BY_ZERO_CODE -1
#define ERR_EMPTY_FILE -2
#define READ_FROM_PIPE_ERROR -3
#define DUP2_ERROR -4
#define INVALID_ARG_ERROR -5
#define OPENING_FILE_ERROR -6
#define BAD_CREATE_PIPE_ERROR -7
#define BAD_CREATE_CHILD_ERROR -8
#define END_CODE 1
#define OK_CODE 0