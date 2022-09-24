# MatrixTweak

A Step-by-step Showcase of Matrix Row Reduction to Reduced Row Echelon Forms.

Apparently, a lot of online tools that do matrix row-reduction either only produce echelon forms, or only show the answer without procedures. So this might be something you may want to use when ~~It's about to be deadline of MATH1030 homework~~ you need to practice row-reduction and check your answers step-by-step.

## How to use

Download and put `RowReduce.bat` and `main.exe` under the same directory.

Start `RowReduce.bat` and input the matrix:

To reduce a $m$ by $n$ matrix, the input should consist of $m+1$ rows.

The first row of input consists of 2 integers, m and n, separated by a space.

For the following rows, the $m+1$th row of the input should include all entries of the $m$th row of the matrix, separated by a space between adjacent entries.

## Input Example

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

## Results

You can find:

+ The resulted matrix in reduced-row-echelon-form...

+ Every row-operation required...

+ Types and discriptions of row-operations, which is the same as those on 1030 lecture note.

... in the program's output.

Pause to view or copy the steps and result, then type any key to kill the program.

## May You Never Fail MATH1030!!!
