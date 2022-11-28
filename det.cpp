/**
 * @file det.cpp
 * @brief Step-by-step showcase of evaluating determinants. Applies only for square matrices with rational entries.
 * 
 * @note Doc-comments include details about the way the code relate to definitions and theorems mentioned in the lecture note.
 * 
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Simple struct for a small, square-matrix used internally for solving determinants.
 * 
 */
struct matrix{
    int** cont;
    int size;

    /**
     * @brief Initialize a (size x size) matrix with all zero entries.
     * 
     */
    void init(int _size){
        size=_size;
        cont=new int*[_size];
        for(int i=0;i<_size;++i){
            cont[i]=new int[_size];
            for(int j=0;j<_size;++j){
                cont[i][j]=0;
            }
        }
    }

    /**
     * @brief Set the entry at a certain row and column to be some value.
     * 
     */
    void valSet(int row, int col, int val){
        cont[row][col]=val;
    }

    /**
     * @brief Get the value of an entry at a certain row and column.
     * 
     */
    int valGet(int row, int col){
        return cont[row][col];
    }

    /**
     * @brief Free the matrix from memory.
     * 
     */
    void finalize(){
        for(int i=0;i<size;++i){
            delete [] cont[i];
        }
        delete [] cont;
    }
};

void printMatrix(matrix amat){
    for(int i=0;i<amat.size;++i){
        printf("| ");
        for(int j=0;j<amat.size;++j){
            printf("%d ",amat.valGet(i,j));
        }
        printf(" |\n");
    }
}

/**
 * @brief Finding a sub-matrix produced by excluding a certain row and a certain column from an original matrix.
 * Used for calculating determinant.
 * 
 * @return matrix Sub-matrix written as oriMat(rmRow|rmCol).
 */
matrix SubMatrix(matrix oriMat, int rmRow, int rmCol){
    matrix subMat;
    subMat.init(oriMat.size-1);

    // Record the positions to be updated in the original matrix a.k.a. use a "cursor".
    int oriRow=0, oriCol=0;

    while(oriRow<oriMat.size){
        // Skip past the current row if the row is to be excluded.
        if(oriRow==rmRow){
            ++oriRow;
            continue;
        } 
        // Record whether the cursor advances past the excluded row.
        bool rflag=(oriRow>rmRow);
        
        // Enumerate every entry in this row by checking the columns they belong to.
        oriCol=0;
        while(oriCol<oriMat.size){
            // Similarly skip past the current entry if it belongs to the column to be excluded.
            if(oriCol==rmCol){
                ++oriCol;
                continue;
            }
            // Record whether the cursor advances past the excluded column.
            bool cflag=(oriCol>rmCol);

            /**
             *  The removed row and column divide the matrix into four parts, A, B, C and D :
             *   A | B
             *   --+--
             *   C | D
             *  If the cursor (i, j) is in part A, it should be updated to value at (i, j) of the original matrix.
             *                      ...  part B,                              ... (i, j-1)
             *                      ...  part C,                              ... (i-1, j)
             *                      ...  part D,                              ... (i-1, j-1)
             *  The areas are identified by whether the cursor have advanced past the removed row and column, which are formerly
             *  recorded as rflag and cflag.
             *  Thus we have the relations:
             *  rflag       cflag       the part that the cursor belongs to
             *  false       false       A
             *  false       true        B
             *  true        false       C
             *  true        true        D
             */

            subMat.valSet(rflag?(oriRow-1):oriRow, cflag?(oriCol-1):oriCol, oriMat.valGet(oriRow, oriCol));

            oriCol++;
        }

        oriRow++;
    }

    printf("Sub-matrix with size %d removing row %d and column %d is:\n", subMat.size, rmRow, rmCol);
    
    return subMat;
}

/**
 *  @brief Evaluate the determinant of a matrix by definition.
 *  The value of the determinant is ALWAYS found recursively as sum of a constant times a determinant of sub-matrices expanded 
 *  about the FIRST ROW.
 *  Time-complexity of finding determinant of n-by-n matrix via this method is O(k^n).
 *  @return int64_t 
 */
int64_t doDetByDef(matrix detMat){
    printMatrix(detMat);

    /**
     *  If the matrix has size of 1, a.k.a. has only 1 entry:
     *  It's determinant is the value of its only entry.
     */
    if(detMat.size==1){
        printf("It has a size of 1, and thus its determinant is %d\n",detMat.valGet(0,0));
        return (int64_t)detMat.valGet(0,0);
    }

    int64_t res=0;
    printf("Iterating from row 0.");

    /**
     *  For matrices with size larger than 1:
     *  We enumerate all its sub-matrices. For i from 0 to detMat.size, find the determinants of sub-matrices of detMat
     *  excluding the first row and the i-th column.
     */
    matrix *subMats=new matrix[detMat.size];
    for(int i=0;i<detMat.size;++i){
        subMats[i]=SubMatrix(detMat,0,i);

        // Sum up all the determinants of sub-matrices weighting by the entries in first row and a negativity.
        int64_t subItem=(i%2)?(-1):1;
        subItem*=detMat.valGet(0,i);
        subItem*=doDetByDef(subMats[i]);
        res+=subItem;
    }

    // Free the sub-matrices from memory when their corresponding values of determinants are found.
    for(int i=0;i<detMat.size;++i){
        subMats[i].finalize();
    }
    delete [] subMats;

    printf("It has the size of %d, and a determinant of %d.\n", detMat.size, res);

    return res;
}

/**
 *  @brief Find the optimal row or column with least non-zero entries in a matrix. 
 *  Used in optimized calculation of determinant.
 *  @return int x
 *  that notates the:
 *  x-th row: when x>=0; 
 *  (-x-1)-th column: when x<0 
 *  @attention For a row and a column with the same numbers of non-zero entries, the row's index will be returned;
 *  For two or more rows or two or more columns with the same number of non-zero entries, the index of row or column corresponding
 *  to a smallest index will be returned.
 */
int Opt_RC(matrix aMat){
    // rNZVals[i] records the number of non-zero entries on the i-th row of the matrix.
    int* rNZVals;
    // cNZVals[i] records the number of non-zero entries on the i-th column of the matrix.
    int* cNZVals;
    rNZVals=new int[aMat.size];
    cNZVals=new int[aMat.size];
    for(int i=0;i<aMat.size;++i){
        rNZVals[i]=0;
        cNZVals[i]=0;
    }

    /**
     *  Count all non-zero entries in the matrix.
     *  Upon encountering a non-zero entry, add 1 to the counters of the row and the column it belongs to.
     */
    
    for(int i=0;i<aMat.size;++i){
        for(int j=0;j<aMat.size;++j){
            if(aMat.valGet(i,j)!=0){
                rNZVals[i]++;
                cNZVals[j]++;
            }
        }
    }

    /**
     *  Find the row or column that has the lowest counter of non-zero entries.
     *  A positive index marks a row, while a negative one marks a column.
     */
    int curMinVal=aMat.size+1;
    int curMinInd=aMat.size;
    for(int i=0;i<aMat.size;++i){
        if(rNZVals[i]<curMinVal){
            curMinVal=rNZVals[i];
            curMinInd=i;
        } if(cNZVals[i]<curMinVal){
            curMinVal=cNZVals[i];
            curMinInd=-i-1;
        }
    }
    
    // Free the arrays for counters from the memory.
    delete [] rNZVals;
    delete [] cNZVals;

    return curMinInd;
}

int64_t doDetByOpt(matrix detMat){
    printMatrix(detMat);

    // For matrix with size of 1, the value of its determinant is the same as that of its only entry.
    if(detMat.size==1){
        printf("It has a size of 1, and thus its determinant is %d\n",detMat.valGet(0,0));
        return (int64_t)detMat.valGet(0,0);
    }

    // Obtain the optimal row or column to start performing calculation,
    int optPiv=Opt_RC(detMat);

    // This is set to true if a row is chosen, and false for a column.
    bool rcflag=(optPiv>=0);
    if(!rcflag){ optPiv=-optPiv-1;}

    // Find the list of sub-matrices similarly.
    // Only this time, the row or column as weights is chosen as that with least non-zero entries instead of always the first row.
    matrix *subMats=new matrix[detMat.size];
    bool *submFlags=new bool[detMat.size];
    for(int i=0;i<detMat.size;++i){
        submFlags[i]=false;
    }
    if(rcflag){
        for(int i=0;i<detMat.size;++i){
            if(detMat.valGet(optPiv,i)==0){ continue; }
            submFlags[i]=true;
            subMats[i]=SubMatrix(detMat,optPiv,i);
        }
    } else {
        for(int i=0;i<detMat.size;++i){
            if(detMat.valGet(optPiv,i)==0){ continue; }
            submFlags[i]=true;
            subMats[i]=SubMatrix(detMat,i,optPiv);
        }
    }

    /**
     *  Sum up all contributions of sub-matrices.
     *  Each sub-matrix contributes to the value of overall determinant a value of their own determinant multiplied by a weight and
     *  a negativity.
     */
    int64_t res=0;
    for(int i=0;i<detMat.size;++i){
        int64_t subItem=((i%2)^(optPiv%2))?(-1):1;
        subItem*=rcflag?(detMat.valGet(optPiv,i)):(detMat.valGet(i,optPiv));
        if(subItem==0){ continue; }
        subItem*=doDetByOpt(subMats[i]);
        res+=subItem;
    }

    // Free the sub-matrices from memory.
    for(int i=0;i<detMat.size;++i){
        if(submFlags[i]){
            subMats[i].finalize();
        }
    } delete [] subMats;

    printf("The matrix with size %d has the determinant of %d.\n", detMat.size, res);
    return res;
}

int main(){
    int _size_;
    
    // Read the size of the matrix.
    printf("Input the size of the matrix.\n");
    printf(">>> ");
    scanf("%d",&_size_);
    printf("Input the entries of the matrix. \n");
    printf("--------------------\n");

    matrix det;
    det.init(_size_);

    // Read the entries of the matrix.
    int curVal;
    for(int i=0;i<_size_;++i){
        for(int j=0;j<_size_;++j){
            scanf("%d",&curVal);
            det.valSet(i,j,curVal);
        }
    }
    printf("--------------------\n");

    int _mode;
    printf("Select the mode of computation - 0 for by definition, 1 for optimized:\n");
    printf("Mode(#)>>> ");
    scanf("%d",&_mode);
    switch(_mode){
        case(0):{
            printf("The determinant of the matrix is: %d\n", doDetByDef(det));
            break;
        } case(1):{
            printf("The determinant of the matrix is: %d\n", doDetByOpt(det));
        } 
    }

    det.finalize();
    exit(0);
}