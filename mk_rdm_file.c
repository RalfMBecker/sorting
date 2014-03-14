/***********************************************************************
* mk_rdm_file.c - create a file of random integers
* Note:   We do not check if arg2 >= RAND_MAX, or the random
*         integers fit into data size int.
* Cmd args:    arg1: filename
*              arg2: how many 
*              arg3: min value
*              arg4: max value (1 larger than...)
*              arg5: no random: nrdm_inc/nrdm_dec (optional)
* File storage: <n><int1><int2>....
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

void error_exit_1(const char* fmt, const char* msg1);
void error_exit_2(const char* fmt, const char* msg1, const char* msg2);

int 
main(int argc, char** argv)
{
  
    int i, n, fd, min, max;
    int* buff_ptr;

    if ( (argc < 5) || (argc > 6) )
	error_exit_1("error: usage %s <file_name> <# of integers> "
		     "<min> <max> <(optional)nrdm_inc/nrdm_dec\n", argv[0]);
  
    if ( (fd = open(argv[1], O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR)) < 0)
	error_exit_2("%s: cannot open file %s.\n", argv[0], argv[1]);

    min = atoi(argv[3]);
    max = atoi(argv[4]);
    if ( (min > max) )
	error_exit_1("%s: min(arg3) must be smaller than max(arg4)\n", argv[0]);

    n = atoi(argv[2]);
    if ( ( NULL == (buff_ptr = malloc((n+1) * sizeof(int))) ) )
	error_exit_1("%s: can't allocate space for random numbers.\n", argv[0]);
    (*buff_ptr) = n; // actual # of integers in file

    if ( (argc !=6) ){
	srand(time(0));
	for (i = 1; i <= n; i++)
	    buff_ptr[i] = rand()%(max - min) + min;
    }
    else{
	if ( ( n != (max - min + 1) ) )
	    error_exit_1("%s: must have arg2 = arg4 - arg3 + 1\n", argv[0]);
	else if ( (strcmp(argv[5], "nrdm_inc") == 0) ){
	    for (i = 1; i <= n; i++)
		buff_ptr[i] = i + min - 1;
	}
	else if ( (strcmp(argv[5], "nrdm_dec") == 0) ){
	    for (i = 1; i <= n; i++)
		buff_ptr[i] = max - i + 1;
	}
	else
	    error_exit_2("%s: invalid option %s\n", argv[0], argv[5]);
    } // end else
      

    if ( ( -1 == write(fd, buff_ptr, (n+1)*sizeof(int)) ) )
	error_exit_2("%s: can't write to file %s.\n", argv[0], argv[1]);

    free(buff_ptr);
    close(fd);

    exit(EXIT_SUCCESS);
}

void 
error_exit_1(const char* fmt, const char* msg1){

    fprintf(stderr, fmt, msg1);
    exit(EXIT_FAILURE);
}

void 
error_exit_2(const char* fmt, const char* msg1, const char* msg2){

    fprintf(stderr, fmt, msg1, msg2);
    exit(EXIT_FAILURE);
}
