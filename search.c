/****************************************************************
* search.c - Search using several search algorithms, and measure time.
*
* Command args:   arg1: number to search for (int)
*                 arg2: file to search (file already in increasing order)
*                 arg3: size of file
* Algorithms:     search_lin
*                 search_binary
*                 search_binary_rec
* Compile with:   read_file.c
*                 error.c
*                 search_routines.c
* Link with:      -lrt (no dynamic-linker needed), for clock_gettime
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int read_file(char* file, int* buffer, int n);
void error_exit_1(const char* fmt, const char* msg1);
void error_exit_2(const char* fmt, const char* msg1, const char* msg2);

int search_lin(int, int*, int);
int search_binary(int, int*, int);
void search_binary_rec(int*, int, int*, int, int);

int 
main(int argc, char** argv)
{
    int v, n, i;
    int* i_ptr = &i;
    int* buff_ptr;
    time_t sec_1, sec_2;
    long nano_1, nano_2;
    double delta;
    struct timespec tspec, *tspec_ptr;

    if ( (argc != 4) )
	error_exit_2("%s: syntax is %s <integer to search for> <which file>" 
		     " <# of integers to search>\n", argv[0], argv[0]);

    tspec_ptr = &tspec;

    v = atoi(argv[1]);
    n = atoi(argv[3]);
    buff_ptr = malloc(n*sizeof(int));
    n = read_file(argv[2], buff_ptr, n);

    // linear seach
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    i = search_lin(v, buff_ptr, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    delta = (nano_2 - nano_1)/1000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100000.0;
    printf("\tfound %d at position %d.\n", v, i);
    printf("Linear search took %g milliseconds.\n\n", delta);

    // binary search
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    i = search_binary(v, buff_ptr, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    delta = (nano_2 - nano_1)/1000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100000.0;
    printf("\tfound %d at position %d.\n", v, i);
    printf("Binary search took %g milliseconds.\n\n", delta);

    // binary search (recursive)
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    i = -1; // default to 'not found'
    search_binary_rec(i_ptr, v, buff_ptr, 0, n-1);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    delta = (nano_2 - nano_1)/1000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100000.0;
    printf("\tfound %d at position %d.\n", v, i);
    printf("Binary search(recursive) took %g milliseconds.\n\n", delta);

    exit(EXIT_SUCCESS);
}
