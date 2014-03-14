Implementation of some sort routines. Algorithms based on Cormen alt.,
with counting adjusted for 0-based arrays.

The algorithms come with helper functions to create arrays of integers:
    - mk_rdm_int.c (make rdm, increasing, decreasing arrays. Arrays are
                    saved as <size><val_0>val_1>...<val<(n-1)> ) 
    - read_file.c (needed to read the above files)
    - error.c (some related error functions)

Everything is documented fairly extensively in the files, and with error
functions in case of incorrect usage. 