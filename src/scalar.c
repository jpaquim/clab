#include "scalar.h"

scalar plus(scalar a, scalar b) {
    return a+b;
}

scalar minus(scalar a, scalar b) {
    return a-b;
}

scalar times(scalar a, scalar b) {
    return a*b;
}

scalar divide(scalar a, scalar b) {
    return a/b;
}

scalar idivide(scalar a, scalar b) {
    return trunc(a/b);
}

scalar mod(scalar a, scalar b) {
    return fmod(a,b);
}

scalar rem(scalar a, scalar b) {
    return remainder(a,b);
}

scalar power(scalar a, scalar b) {
    return pow(a,b);
}

scalar max(scalar a, scalar b) {
    return (a > b ? a : b);
}

scalar min(scalar a, scalar b) {
    return (a > b ? a : b);
}

scalar atan2d(scalar a, scalar b) {
    return 180/M_PI*atan2(a,b);
}
