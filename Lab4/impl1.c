#include <math.h>

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}

float bpow(float x, int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return x;
    } 
    float _p = bpow(x, n / 2);
    _p *= _p;
    if (n % 2 == 1) {
        _p *= x;
    }
    return _p;
}

float E(int x) {
    return bpow(1.f + 1.f/(float)x, x);
}