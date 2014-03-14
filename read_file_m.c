/***********************************************************************
* read_file.c - Read a file containing integers into a buffer.
* Note:         integers saved as: <number of integers><int1><int2>...
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void error_exit_1(const char* fmt, const char* msg1);
void error_exit_2(const char* fmt, const char* msg1, const char* msg2);

int 
read_file(char* file, int* buffer, int n)
{

    int fd;

    if ( ( -1 == (fd = open(file, O_RDONLY)) ) )
	error_exit_1("error: can't open file %s\n", file);

    // pos 0 has the number of integers in file
    if ( ( -1 == read(fd, buffer, 4) ) )
	error_exit_1("error: can't read from file %s.\n", file);
    n = (buffer[0] < n)?buffer[0]:n;
    if ( ( -1 == read(fd, buffer, n*sizeof(int)) ) )
	error_exit_1("error: can't read from file %s.\n", file);

    close (fd);
    return n;
}

int 
main(int argc, char** argv)
{

    int buffer[2000000], n, i;
    int *ptr = buffer;
    n = read_file(argv[1], ptr, 2000000);

    for (i=0; i < n; i++)
	printf("buffer[%d] = %d\n", i, buffer[i]);

    exit(EXIT_SUCCESS);
}
