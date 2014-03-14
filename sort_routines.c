2/*******************************************************************
* sort_routines.c - Various sort routines
* Args:         arg1: buffer to sort in place
*               arg2: size of buffer
* Routines:     Insertion sort (n) (input for n data points)
*               Selection sort (n)
*               Merge sort (n-1)
*               Heap sort (n)
* Note: size sometimes is number of elements, sometimes last array 
*       element. Not good; for production, should choose one. 
*       See above for what is used for which algorithm.
********************************************************************/

#include <string.h>
#include <math.h>

int 
sort_insertion(int* A, int n)
{
    int key, i, j;
    if (n <= 1)
	return 0;
    for (i = 1; i < n; i++){
	key = A[i];
	j = i - 1;
	while ( (j >= 0) && (A[j] > key) ){
	    A[j+1] = A[j];
	    j--;
	}
	A[j+1] = key;
    }

    return 0;
}

void 
sort_selection(int* A, int n)
{
    int i, j, min, min_i;

    for (i = 0; i < n-1; i++){
	min = A[i];
	min_i = i;
	    for (j = i+1; j < n; j++){
		if ( (A[j] < min) ){
		    min = A[j];
		    min_i = j;
		}
	    }
	    A[min_i] = A[i];
	    A[i] = min;
    }
}

// merge sort procedures
void 
merge(int* A, int p, int q, int r)
{
    int n_L, n_R, i, j, k;

    n_L = q - p + 1;   // number of elements in array, but recall 0-based
    n_R = r-q;
    int L[n_L], R[n_R];

    memcpy(L, A + p, n_L * sizeof(int));
    memcpy(R, A + (q+1), n_R * sizeof(int));
    // L[n_L] = R[n_R] = sentinel;

    i = j = 0;
    k = p;
    while ( (i < n_L) && (j < n_R) )
	A[k++] = (L[i] <= R[j])?L[i++]:R[j++];

    // distribute those remaining after either L or R are exhausted
    while ( (i < n_L) )
	A[k++] = L[i++];
    while ( (j < n_R) )
	A[k++] = R[j++];
}

void 
sort_merge(int* A, int p, int r)
{
    int q;

    if ( (p < r) ){
	q = (p+r)/2;
	sort_merge(A, p, q);
	sort_merge(A, q+1, r);
	merge(A, p, q, r);
    }
}

// heap sort procedures
// for parent/child relationships, recall we have 0-based counting
int
parent(int i)
{
    if (i < 0)
	return -1;
    return floor((i-1)/2);
}

int
leftChild(int i)
{
    if (i < 0)
	return -1;
    return 2*i + 1;
}

int
rightChild(int i)
{
    if (i < 0)
	return -1;
    return 2*(i + 1);
}

void // we skip bound check
swap(int* A, int i, int j)
{
    int tmp;

    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void
maxHeapify(int* A, int heapSizeA, int i)
{
    int l, r, largest;

    l = leftChild(i);
    r = rightChild(i);

    largest = ( (l < heapSizeA) && (A[l] > A[i]) )?l:i;
    largest = ( (r < heapSizeA) && (A[r] > A[largest]) )?r:largest;
    if ( (largest != i) ){
	swap(A, i, largest);
	maxHeapify(A, heapSizeA, largest);
   }
}

void
buildMaxHeap(int* A, int sizeA)
{
    int i;

    // for where to start, recall 0-based counting again
    if (sizeA > 1){
	for (i = ( (int) floor(sizeA/2) ) - 1; i >= 0; i--)
	    maxHeapify(A, sizeA, i);
    }
}

void
sort_heap(int* A, int sizeA)
{
    int i;
    int heapSizeA = sizeA;

    buildMaxHeap(A, sizeA);
    for (i = sizeA - 1; i >= 1; i--){ // again, recall 0-based counting
	swap(A, 0, i);
	--heapSizeA;
	maxHeapify(A, heapSizeA, 0);
    }
} 
