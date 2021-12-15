## Linear Algebra Library for C

# An Overveiw
This is a library of C functions that work with matrices.  It is still
currently in development and lacking many features.

# Current Features
This library supports a type `matrix_t` that is to be declared as follows:
```
	matrix_t * matrix = init_matrix(string-declaration-of-matrix);
```
Where string-declaration-of-matrix is a string of the following format:
```
	name_of_matrix = [elem1 elem2 ... elemN; elem1 elem2 ... elemN; ...]
```
Similar to how MATLAB and octave define matrices (the above is semi-whitespace
dependent and whitespace should be noted).


This will generate a `matrix_t` object for which the following operations are supported:
 - addition
 - subtraction
 - Transposition Operator '
