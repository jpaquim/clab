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

scalar_l eq(scalar a, scalar b) {
    return a == b;
}

scalar_l ne(scalar a, scalar b) {
    return a != b;
}

scalar_l lt(scalar a, scalar b) {
    return a < b;
}

scalar_l le(scalar a, scalar b) {
    return a <= b;
}

scalar_l gt(scalar a, scalar b) {
    return a > b;
}

scalar_l ge(scalar a, scalar b) {
    return a >= b;
}

scalar_l or(scalar_l a, scalar_l b) {
    return a || b;
}

scalar_l and(scalar_l a, scalar_l b) {
    return a && b;
}

scalar_l xor(scalar_l a, scalar_l b) {
    return or(and(a, !b), and(!a, b));
}
