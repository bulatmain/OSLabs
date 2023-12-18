#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}

long long fact(long long n) {
    if (n < 0) {
        fprintf(stderr, "Error: fact of negative number: %lld\n", n);
        exit(-1);
    }
    if (n == 1 || n == 0) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

float E(int x) {
    float e = 0;
    for (int i = 0; i < x; ++i) {
        float nf = (float)fact(i);
        if (nf < 0) {
            printf("Error: long long overflow while calculating factorial!\n");
            return 0;
        }
        e += 1.f / nf;
    }
    return e;
}