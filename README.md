# MatrixTweak

Here you can find:

+ A Step-by-step Showcase of Matrix Row Reduction to Reduced Row Echelon Forms... and

+ ... a detailed demonstration of Matrix Multiplication... and

+ A showcase of calculating determinants using the recursive method.

Apparently, a lot of online tools that do matrix row-reduction either only produce echelon forms, or only show the answer without procedures. So this might be something you may want to use when ~~It's about to be deadline of MATH1030 homework~~ you need to practice row-reduction and check your answers step-by-step.

The same problem occurs when students attempt to do matrix multiplication using online tools. The **Matrix Multiplication** tool I posted should make it easier.

## Updates

Calculation of Determinants now available.

## Row Reduction

### How to use

Download and put `RowReduce.bat` and `main.exe` under the same directory.

Start `RowReduce.bat` and input the matrix:

To reduce a $m$ by $n$ matrix, the input should consist of $m+1$ rows.

The first row of input consists of 2 integers, m and n, separated by a space.

For the following rows, the $m+1$th row of the input should include all entries of the $m$th row of the matrix, separated by a space between adjacent entries.

### Input Example

For a matrix written like:

$$\begin{bmatrix}
2&5&8&1\\
1&0&6&-3\\
-5&9&0&3\\
\end{bmatrix}$$

You should type:

```
3 4
2 5 8 1
1 0 6 -3
-5 9 0 3
```
... into the console.

### Results

A typical output looks like this:

```
3 4
-3 3 -2 7
3 1 1 -9
-1 -1 -2 7
Iterating from (0,0)
-----(R0)*(-1/3) yields:
----------
+1   -1   +2/3 -7/3
+3   +1   +1   -9
-1   -1   -2   +7
----------


-----(R1)-(3/1)*(R0) yields:
----------
+1   -1   +2/3 -7/3
+0   +4   -1   -2
-1   -1   -2   +7
----------


-----(R2)+(1/1)*(R0) yields:
----------
+1   -1   +2/3 -7/3
+0   +4   -1   -2
+0   -2   -4/3 +14/3
----------


Iterating from (1,1)
-----(R1)*(+1/4) yields:
----------
+1   -1   +2/3 -7/3
+0   +1   -1/4 -1/2
+0   -2   -4/3 +14/3
----------


-----(R2)+(2/1)*(R1) yields:
----------
+1   -1   +2/3 -7/3
+0   +1   -1/4 -1/2
+0   +0   -11/6 +11/3
----------


Iterating from (2,2)
-----(R2)*(-6/11) yields:
----------
+1   -1   +2/3 -7/3
+0   +1   -1/4 -1/2
+0   +0   +1   -2   
----------


Iterating from (3,3)
Reverse Elimination:
-----(R1)+(1/4)*(R2) yields:
----------
+1   -1   +2/3 -7/3
+0   +1   +0   -1
+0   +0   +1   -2
----------


-----(R0)-(2/3)*(R2) yields:
----------
+1   -1   +0   -1
+0   +1   +0   -1
+0   +0   +1   -2
----------


-----(R0)+(1/1)*(R1) yields:
----------
+1   +0   +0   -2
+0   +1   +0   -1
+0   +0   +1   -2
----------


----------
+1   +0   +0   -2
+0   +1   +0   -1
+0   +0   +1   -2
----------
```

You can find:

+ The resulted matrix in reduced-row-echelon-form...

+ Every row-operation required...

+ Types and discriptions of row-operations, which is the same as those on 1030 lecture note.

... in the program's output.

Pause to view or copy the steps and result, then type any key to kill the program.

## Matrix Multiplication

### How to use

Download and put `matmult.exe` and `matmult.bat` under the same directory.

Start `matmult.bat` and input the two matrices.

If the first matrix is $m$x$n$, the second must be $n$x$p$, so that the product of two matrices is defined.

The input consists of $m+n+1$ lines:

The first line of input should consist of 3 integers, each separated from the next with a space.

The next $m$ lines should each consist of one row from the first matrix, in top-down order, separated by spaces.

The following %n% lines should each consist of one row from the second matrix, in top-down order, separated by spaces.

### Input Example

To calculate $AB$ where:

$$ AB= \begin{bmatrix}
6&5\\
1&2\\
\end{bmatrix}
\begin{bmatrix}
2&-1&3\\
1&0&4\\
\end{bmatrix}$$

The first matrix is 2-by-2 while the second is 2-by-3.

Thus $m=2$, $n=2$, and $p=3$.

... you should type:

```
2 2 3
6 5
1 2
2 -1 3
1 0 4
```

... into the console.

### Results

A typical result should look like this:

```
2 2 3
6 5
1 2
2 -1 3
1 0 4
Assume the resulting matrix is C.
Starting from 1-th row:

A(1-th row) dot B(1-th col) is:  +6*2+5*1=17
=> C(1,1)=17

A(1-th row) dot B(2-th col) is:  +6*-1+5*0=-6
=> C(1,2)=-6

A(1-th row) dot B(3-th col) is:  +6*3+5*4=38
=> C(1,3)=38

Starting from 2-th row:

A(2-th row) dot B(1-th col) is:  +1*2+2*1=4
=> C(2,1)=4

A(2-th row) dot B(2-th col) is:  +1*-1+2*0=-1
=> C(2,2)=-1

A(2-th row) dot B(3-th col) is:  +1*3+2*4=11
=> C(2,3)=11

The resulting matrix is:
----------
17 -6 38
4 -1 11 
----------
```

You can find:

+ The resulting matrix...

+ ... and how every entry of the matrix is acquired.

... in the program's output.

~~I know the algebra is a little bit hard to read, yet I'm too lazy to format that thing up the fact that no one pays for my work... so whatever.~~

## Calculating Determinant

A step-by-step (again) showcase of calculating determinant of a matrix.

### How to Use

Download and put `det.exe` and `det.bat` under the same directory.

Start `det.bat` and follow the instructions.

### Modes of Calculations

The program currently implements two modes of calculation. 

The first mode is `by definition`, which recursively expands the determinant always about its first row; the second mode is `optimized`, which would attempt to expands the determinant about its row or column with *the least non-zero entries* to simplify calculations. Both modes have an average-case time complexity of $O(k^n)$ for an $n \times n$ matrix.

As some students may know, determinant of a matrix can be evaluated by performing the gaussian elimination, which has better time complexity of only $O(n^3)$ for an $n \times n$ matrix. However, as gaussian elimination is already covered in other parts, this method is not included in the determinant tool.

This tool is meant for smaller matrices, and implements only a naive algorithm as more a *step-wise showcase of how things are done* than an optimization; otherwise the program would take very long to run, or the outputs would be too messy to read.

### Example of Evaluating a Determinant

$$ det \begin{bmatrix}
3&-12&21\\
-5&19&-34\\
1&-3&7\\
\end{bmatrix} = -3 $$

```
Input the size of the matrix.
>>> 3
Input the entries of the matrix. 
--------------------
3 -12 21
-5 19 -34
1 -3 7
--------------------
Select the mode of computation - 0 for by definition, 1 for optimized:
Mode(#)>>> 0
| 3 -12 21  |
| -5 19 -34  |
| 1 -3 7  |
Iterating from row 0.Sub-matrix with size 2 removing row 0 and column 0 is:
| 19 -34  |
| -3 7  |
Iterating from row 0.Sub-matrix with size 1 removing row 0 and column 0 is:
| 7  |
It has a size of 1, and thus its determinant is 7
Sub-matrix with size 1 removing row 0 and column 1 is:
| -3  |
It has a size of 1, and thus its determinant is -3
It has the size of 2, and a determinant of 31.
Sub-matrix with size 2 removing row 0 and column 1 is:
| -5 -34  |
| 1 7  |
Iterating from row 0.Sub-matrix with size 1 removing row 0 and column 0 is:
| 7  |
It has a size of 1, and thus its determinant is 7
Sub-matrix with size 1 removing row 0 and column 1 is:
| 1  |
It has a size of 1, and thus its determinant is 1
It has the size of 2, and a determinant of -1.
Sub-matrix with size 2 removing row 0 and column 2 is:
| -5 19  |
| 1 -3  |
Iterating from row 0.Sub-matrix with size 1 removing row 0 and column 0 is:
| -3  |
It has a size of 1, and thus its determinant is -3
Sub-matrix with size 1 removing row 0 and column 1 is:
| 1  |
It has a size of 1, and thus its determinant is 1
It has the size of 2, and a determinant of -4.
It has the size of 3, and a determinant of -3.
The determinant of the matrix is: -3
```

## May You Never Fail MATH1030!!!

~~This doubles as a C++ practice for me in the meantime.~~
