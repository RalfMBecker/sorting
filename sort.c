/****************************************************************
* sort.c - Sort using several sorting algorithms, and measure time.
*
* Command args:   arg1: file to sort
*                 arg2: # of integers to sort
* Algorithms:     sort_insertion
*                 sort_selection
*                 sort_merge
*                 sort_heap
* Compile with:   read_file.c
*                 error.c
*                 sort_routines.c
* Link with:      -lrt (no dynamic-linker needed), for clock_gettime
*                 -lm for math.h
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int read_file(char* file, int* buffer, int n);
void error_exit_1(const char* fmt, const char* msg1);
void error_exit_2(const char* fmt, const char* msg1, const char* msg2);
void print_sorted(int*, int);

int sort_insertion(int* buff, int n);
void sort_selection(int* buff, int n);
void sort_merge(int*, int, int); 
void sort_heap(int* A, int sizeA);

int 
main(int argc, char** argv)
{
    int n;
    int* buff_ptr; 
    int* sorted_ptr;
    time_t sec_1, sec_2;
    long nano_1, nano_2;
    double delta;
    struct timespec tspec, *tspec_ptr;

    if ( (argc != 3) )
	error_exit_2("%s: syntax %s <file_to_sort> <# of integers to sort>\n", 
		     argv[0], argv[0]);

    tspec_ptr = &tspec;
    // clock_getres(CLOCK_PROCESS_CPUTIME_ID, tspec_ptr);
    // printf("supportes resolution of: seconds = %ld, nanoseconds = %ld\n",
    // tspec.tv_sec, tspec.tv_nsec);

    n = atoi(argv[2]); 
    buff_ptr = malloc(n*sizeof(int));
    sorted_ptr = malloc(n*sizeof(int));
    n = read_file(argv[1], buff_ptr, n);

    // insertion sort
    memcpy(sorted_ptr, buff_ptr, n*sizeof(int));
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    sort_insertion(sorted_ptr, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    // print_sorted(sorted_ptr, n);
    delta = (nano_2 - nano_1)/1000000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100.0;
    printf("\nInsertion sort took %g micro seconds.\n", (double) delta);

    // selection sort
    memcpy(sorted_ptr, buff_ptr, n*sizeof(int));
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    sort_selection(sorted_ptr, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    // print_sorted(sorted_ptr, n);
    delta = (nano_2 - nano_1)/1000000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100.0;
    printf("\nSelection sort took %g micro seconds.\n", (double) delta);

    // merge sort
    memcpy(sorted_ptr, buff_ptr, n*sizeof(int));
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    sort_merge(sorted_ptr, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    // print_sorted(sorted_ptr, n);
    delta = (nano_2 - nano_1)/1000000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100.0;
    printf("\nMerge sort took %g micro seconds.\n", (double) delta);

    // merge sort
    memcpy(sorted_ptr, buff_ptr, n*sizeof(int));
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_1 = tspec.tv_sec, nano_1 = tspec.tv_nsec;
    sort_heap(sorted_ptr, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, tspec_ptr);
    sec_2 = tspec.tv_sec, nano_2 = tspec.tv_nsec;
    // print_sorted(sorted_ptr, n);
    delta = (nano_2 - nano_1)/1000000.0;
    delta = (delta >= 0)?delta:-delta;
    delta += (sec_2 - sec_1)/100.0;
    printf("\nHeap sort took %g micro seconds.\n", (double) delta);

    exit(EXIT_SUCCESS);
}

void 
print_sorted(int* buffer, int n)
{
    int i;
    for (i = 0; i < n; i++){
	printf("%d\t", buffer[i]);
	if ( ((i%10) == 0) )
	    printf("\n");
    }
}
