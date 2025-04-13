#include <stdio.h>
#include <stdarg.h>
#include "calculator.h"

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    return total;
}

int sub(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total -= va_arg(args, int);
    }

    va_end(args);
    return total;
}

int mult(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total *= va_arg(args, int);
    }

    va_end(args);
    return total;
}

int div(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = va_arg(args, int);
    for (int i = 0; i < count; i++) {
        int next = va_arg(args, int);

        if (next == 0) {
            va_end(args);
            return 1;
        }

        total /= next;
    }

    va_end(args);
    return total;
}