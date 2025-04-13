#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum {
    SUCCESS = 0,
    ERROR_ZERO = 1,
} ErrorCode;

int sum(int count, ...);
int sub(int count, ...);
int mult(int count, ...);
int div(int count, ...);

#endif