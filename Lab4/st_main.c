#include <stdio.h>
#include <stdlib.h>

#include "derivative.h"
#include "e.h"


int main() {
    int run = 1;

    while (run) {
        int command = 0;
        printf(
            "Usage:\n"
            "\t\b-1 - exit\n"
            "\t1 - calculate derivative\n"
            "\t2 - calculate e\n"
            "Command: "
        );
        scanf("%d", &command);

        if (command == -1) {
            run = 0;
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
        }
    }


    return 0;
}