/**
 * @file matmult.cpp
 * @brief A step-by-step demonstration of matrix multiplication.
 * @date 2022-09-30
 * 
 */
#include <bits/stdc++.h>

using namespace std;

// mxn matrix on the left.
int** lmat;

// nxp matrix on the right.
int** rmat;

// The resulting matrix.
int** ans;


int m,n,p;

/**
 * @brief Initialize three matrices.
 * Fill the given two matrices with entries from input.
 * Fill the resulting matrix with zeroes. (Somehow I didn't use malloc for this dynamically-stored matrix)
 */
void _init_(){
    cin>>m>>n>>p;
    lmat=new int*[m];
    rmat=new int*[n];
    ans=new int*[m];
    for(int i=0;i<m;++i){
        lmat[i]=new int[n];
        ans[i]=new int[p];
    }
    for(int i=0;i<n;++i){
        rmat[i]=new int[p];
    }

    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin>>lmat[i][j];
        }
    }

    for(int i=0;i<n;++i){
        for(int j=0;j<p;++j){
            cin>>rmat[i][j];
        }
    }

    for(int i=0;i<m;++i){
        for(int j=0;j<p;++j){
            ans[i][j]=0;
            // A bit of confusing to use malloc here.
        }
    }
}


/**
 * @brief Get the dot-product of a row of the left-matrix and a column of the right-matrix.
 * @note A column of an mxn matrix can be considered an m-dimensional vector;
 *       <p> A row of such mxn matrix can be considered an n-dimensional vector as well. </p>
 * 
 * @param leftRow The number of the row from the left-matrix, counted from the left.
 * @param rightColumn The number of the column from the right-matrix, counted from the top.
 */
int getDotProd(int leftRow, int rightColumn){
    int res=0;
    printf("A(%d-th row) dot B(%d-th col) is:  ",leftRow+1,rightColumn+1);
    for(int i=0;i<n;++i){
        res+=lmat[leftRow][i]*rmat[i][rightColumn];
        printf("%+d*%d",lmat[leftRow][i],rmat[i][rightColumn]);
    }
    printf("=%d\n",res);
    printf("=> C(%d,%d)=%d\n\n",leftRow+1,rightColumn+1,res);
    return res;
}

/**
 * @brief Perform the matrix multiplication of the two given matrices by definition.
 * @note The entry at i-th row and j-th column of the resulting matrix is the dot-product of
 * the i-th row-vector of the left-matrix and j-th column-vector of the right-matrix.
 */
void domult(){
    printf("Assume the resulting matrix is C.\n");
    int curRow=0;
    int curCol=0;
    while(curRow<m){
        printf("Starting from %d-th row:\n\n", curRow+1);
        curCol=0;
        while(curCol<p){
            ans[curRow][curCol]=getDotProd(curRow,curCol);
            ++curCol;
        }
        ++curRow;
    }

}

void _print_(){
    printf("The resulting matrix is:\n");
    printf("----------\n");
    for(int i=0;i<m;++i){
        for(int j=0;j<p;++j){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
    printf("----------");
}

/**
 * @brief Free all three matrices from the memory.
 * 
 */
void _free_(){
    for(int i=0;i<m;++i){
        delete [] lmat[i];
        delete [] ans[i];
    }
    for(int i=0;i<n;++i){
        delete [] rmat[i];
    }
    delete [] lmat;
    delete [] rmat;
    delete [] ans;
}

int main(){
    _init_();
    domult();
    _print_();
    _free_();
    return 0;

}