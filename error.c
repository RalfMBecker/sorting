#include <stdio.h>
#include <stdlib.h>

void 
error_exit_1(const char* fmt, const char* msg1)
{
    fprintf(stderr, fmt, msg1);
    exit(EXIT_FAILURE);
}

void 
error_exit_2(const char* fmt, const char* msg1, const char* msg2)
{
    fprintf(stderr, fmt, msg1, msg2);
    exit(EXIT_FAILURE);
}
