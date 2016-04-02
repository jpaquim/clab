#ifndef SCALAR_H
#define SCALAR_H

// debugging macros
#include <stdio.h>
#define print_var(f,x) do printf(#x " = " f "\n",x); while (0)
#define print_int(x) print_var("%d",x)
#define print_float(x) print_var("%g",x)

#include <math.h>    // for pow, atan2, etc.
#include <stdbool.h> // for bool

#define inf INFINITY

typedef double scalar;
// typedef float scalar;

typedef scalar (*unary_function)(scalar);
typedef scalar (*binary_function)(scalar,scalar);

// unary operations, for use with arrayfun


// binary operations, for use with bsxfun

// returns a+b
scalar plus(scalar a, scalar b);

// returns a-b
scalar minus(scalar a, scalar b);

// returns a*b
scalar times(scalar a, scalar b);

// returns a/b
scalar divide(scalar a, scalar b);

// integer division, round towards 0
scalar idivide(scalar a, scalar b);

// returns a mod b
scalar mod(scalar a, scalar b);

// returns remainder of integer division
scalar rem(scalar a, scalar b);

// returns a^b
scalar power(scalar a, scalar b);

// binary maximum of two numbers
scalar max(scalar a, scalar b);

// binary minimum of two numbers
scalar min(scalar a, scalar b);

// atan2 in degrees
scalar atan2d(scalar a, scalar b);

#endif
