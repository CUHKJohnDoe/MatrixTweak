# MatrixTweak

A Step-by-step Showcase of Matrix Row Reduction to Reduced Row Echelon Forms.

Apparently, a lot of online tools that do matrix row-reduction either only produce echelon forms, or only show the answer without procedures. So this might be something you may want to use when ~~It's about to be deadline of MATH1030 homework~~ you need to practice row-reduction and check your answers step-by-step.

The same problem occurs when students attempt to do matrix multiplication using online tools. The **Matrix Multiplication** tool I posted should make it easier.

## Updates

There's also a program for *matrix multiplication* now!

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

## May You Never Fail MATH1030!!!

I'll keep updating the repo with any potentially useful matrix hacks to play with! Matrix-inverse, Idempotence and Nilpotence checker coming soon!!

~~This doubles as a C++ practice for me in the meantime.~~
