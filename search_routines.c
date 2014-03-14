/****************************************************************
* - search_routines.c: Various search routines
****************************************************************/

#include <stdio.h>

int 
search_lin(int v, int* A, int n)
{
    int i;
    for (i = 0; i < n; i++){
	if ( (v == A[i]) )
	    return i;
    }

    return -1;
}

int 
search_binary(int v, int* A, int n)
{
    int low, mid, high;
    low = 0;
    high = n-1;
  
    while ( (low <= high) ){
	mid = (low+high)/2;
	if ( (v < A[mid]) )
	    high = mid - 1;
	else if ( (v > A[mid]) )
	    low = mid + 1;
	else
	    return mid;
    }

    return -1;
}

// note that for 0-based array, high = n-1
void 
search_binary_rec(int* r, int v, int* A, int low, int high)
{
  int mid;

  if ( (low <= high) ){
      mid = (low+high)/2;
      if ( (v < A[mid]) )
	  search_binary_rec(r, v, A, low, mid - 1);
      else if ( (v > A[mid]) )
	  search_binary_rec(r, v, A, mid + 1, high);
      else
	  *r = mid;
  }
}

