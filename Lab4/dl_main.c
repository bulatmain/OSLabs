#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#define crash_on(boolean) if (boolean) { fprintf(stderr, "Error at file %s, line %d\n", __FILE__, __LINE__); exit(1); }
#define handle(i) crash_on(i == -1)

static int impl = 0;
static void *library = NULL;

static float (*Derivative)(float, float);
static float (*E)(int);


void load_lib() {
    if (impl == 0) {
        library = dlopen("./libimpl1.so", RTLD_LAZY);
    } else {
        library = dlopen("./libimpl2.so", RTLD_LAZY);
    }
    crash_on(library == NULL);

    Derivative = (float(*)(float, float))dlsym(library, "Derivative");
    E = (float(*)(int))dlsym(library, "E");
}


int main() {
    int run = 1;

    load_lib();

        while (run) {
        int command = 0;
        printf(
            "Usage:\n"
            "\t\b-1 - exit\n"
            "\t0 - change implementation\n"
            "\t1 - calculate derivative\n"
            "\t2 - calculate e\n"
            "Command: "
        );
        scanf("%d", &command);

        if (command == -1) {
            run = 0;
        } else if (command == 0) {
            // change implementation
            impl = 1 - impl;
            dlclose(library);
            load_lib();
        } else if (command == 1) {
            // prime
            float A = 0, deltaX = 0;
            printf(
                "Input A and deltaX to find value of derivative of cos(x) at A :\n"
                "\tA: "
            );
            scanf("%f", &A);
            printf("\tdeltaX: ");
            scanf("%f", &deltaX);

            float result = Derivative(A, deltaX);

            printf("Result: %f\n", result);
        } else if (command == 2) {
            // rebase
            int x = 0;
            printf("Input level of accuracy of value of e: ");
            scanf("%d", &x);

            float result = E(x);

            printf("Result: %f\n", result);
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}