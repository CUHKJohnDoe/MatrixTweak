#include <bits/stdc++.h>
using namespace std;


/**
 * @brief Greatest Common Divisor. The library one for this is only available on C++ 17.
 * 
 */
int _gcd_(int oprA, int oprB){
    return oprB>0?_gcd_(oprB,oprA%oprB):oprA;
}

/**
 * @brief Struct for Fractions, which includes the absolute values of numerator and denominator, as well as a boolean sign.
 * 
 */
typedef struct frac{
    int nume;
    int deno;
    bool sign;
    /**
     * @brief Set the fraction so that its value equals the given integer.
     */
    void init(int val){
        nume=abs(val);
        deno=1;
        sign=(val>0);
    }
    /**
     * @brief Set the fraction so that it equals to x/y.
     */
    void init(int x, int y){
        nume=abs(x);
        deno=abs(y);
        sign=true;
        if(x<0){sign=!sign;}
        if(y<0){sign=!sign;}
        round();
    }
    /**
     * @brief Round the fraction to the most simple form.
     */
    void round(){
        if(isZero()){deno=1; sign=true; return;}
        if(nume<0){nume=-nume; sign=!sign;}
        if(deno<0){deno=-deno; sign=!sign;}
        int tmpgcd=_gcd_(nume,deno);
        nume/=tmpgcd;
        deno/=tmpgcd;
    }

    bool isZero(){
        return nume==0;
    }
    /**
     * @brief Return the fraction's value as a double.
     */
    double toDeci(){
        return (double)nume/(double)deno*(sign?(1):(-1));
    }
    
};


frac** mat;

int _row_=0,_col_=0;

/**
 * @brief Return the inverted fraction (1/opr).
 */
frac frcinv(frac opr){
    frac nfrc;
    nfrc.init(opr.deno,opr.nume);
    nfrc.sign=opr.sign;
    nfrc.round();
    return nfrc;
}
/**
 * @brief Return the reverted fraction (-opr).
 */
frac frcrev(frac opr){
    frac nfrc;
    nfrc.init(opr.nume,opr.deno);
    nfrc.sign=!opr.sign;
    nfrc.round();
    return nfrc;
}
/**
 * @brief Return the sum of two fractions (oprA+oprB).
 */
frac frcadd(frac oprA, frac oprB){
    int comDeno=oprA.deno*oprB.deno;
    int anume=oprA.nume*(comDeno/oprA.deno)*(oprA.sign?1:(-1));
    int bnume=oprB.nume*(comDeno/oprB.deno)*(oprB.sign?1:(-1));
    frac nfrc;
    nfrc.init(anume+bnume,comDeno);
    nfrc.round();
    return nfrc;
}

/**
 * @brief Return the difference of the two fractions (oprA-oprB).
 */
frac frcmin(frac oprA, frac oprB){
    return frcadd(oprA,frcrev(oprB));
}

/**
 * @brief Return the product of the two fractions (oprA*oprB).
 */
frac frcmul(frac oprA, frac oprB){
    frac nfrc;
    nfrc.init(oprA.nume*oprB.nume,oprA.deno*oprB.deno);
    nfrc.sign=(oprA.sign==oprB.sign);
    nfrc.round();
    return nfrc;
}

/**
 * @brief Return the quotient of the two fractions (oprA/oprB).
 * @note This is only allowed when   toDeci(oprB)!=0.0d;  .
 */
frac frcdiv(frac oprA, frac oprB){
    return frcmul(oprA,frcinv(oprB));
}

/**
 * @brief Look for the first non-zero entry in the matrix of a designated column after a starting index. The left-most column is considered column 0.
 * @return The row number of the first non-zero entry found: If a non-zero entry is found; (-1) if no such entry is found. The upper-most row is considered row 0.
 */
int cscan(int colNum, int startInd){
    int curRow=startInd;
    while(curRow<_row_){
        if(!mat[curRow][colNum].isZero()){
            return curRow;
        }   curRow++;
    }
    return -1;
}

void _printMat_(){
    printf("----------\n");
    for(int i=0;i<_row_;++i){
        inloop: for(int j=0;j<_col_;++j){
            if(mat[i][j].deno==1){
                printf("%c%d   ",mat[i][j].sign?'+':'-',mat[i][j].nume);
            } else{
                printf("%c%d/%d ",mat[i][j].sign?'+':'-',mat[i][j].nume,mat[i][j].deno);
            }
        }
        printf("\n");
    }
    printf("----------\n\n\n");
}

/**
 * @brief Look for the first non-zero entry in the matrix of a designated row after a starting index. The upper-most column is considered row 0.
 * @return The column number of the first non-zero entry found: If a non-zero entry is found; (-1) if no such entry is found. The left-most column is considered column 0.
 */
int rscan(int rowNum, int startInd){
    int curCol=startInd;
    while(curCol<_col_){
        if(!mat[rowNum][curCol].isZero()){
            return curCol;
        }   curCol++;
    }
    return -1;
}




void _replace_(int refRow, int tarRow){

    if(refRow==tarRow){return;}
    
    int refst=rscan(refRow,0);
    if(mat[tarRow][refst].isZero()){
        return;
    }


    int curCol=refst;
    frac rratio=frcdiv(mat[tarRow][refst],mat[refRow][refst]);
    while(curCol<_col_){
        mat[tarRow][curCol]=frcmin(mat[tarRow][curCol],frcmul(mat[refRow][curCol],rratio));
        curCol++;
    }

    printf("-----");
    printf("(R%d)%c(%d/%d)*(R%d) yields:\n",tarRow,rratio.sign?'-':'+',rratio.nume,rratio.deno,refRow);

    _printMat_();
}


void _swap_(int rowA, int rowB){
    if(rowA==rowB){return;}
    int curCol=0;
    frac tmpFrc;
    while(curCol<_col_){
        tmpFrc=mat[rowA][curCol];
        mat[rowA][curCol]=mat[rowB][curCol];
        mat[rowB][curCol]=tmpFrc;
        ++curCol;
    }

    printf("-----");
    printf("Exchange row (R%d) and row (R%d) yields:\n",rowA,rowB);
    _printMat_();
}

void _scale_(int tarRow){
    int stCol=rscan(tarRow,0);
    
    frac comRat=mat[tarRow][rscan(tarRow,0)];
    int curCol=stCol;
    while(curCol<_col_){
        mat[tarRow][curCol]=frcdiv(mat[tarRow][curCol],comRat);
        curCol++;
    }

    frac tmpRat=frcinv(comRat);

    printf("-----");
    printf("(R%d)*(%c%d/%d) yields:\n",tarRow,tmpRat.sign?'+':'-',tmpRat.nume,tmpRat.deno);
    _printMat_();
}

void doForwardElim(int beginRow, int beginCol){
    printf("Iterating from (%d,%d)\n",beginRow,beginCol);
    // Return if the elimination process is trivial. a.k.a if it begins at the last row or to the right of the last column.
    if(beginRow==_row_ || beginCol==_col_){return;}

    // If no pivot entry is found on the current column, move on to the next column.
    if(cscan(beginCol,beginRow)==-1){doForwardElim(beginRow,beginCol+1); return;}


    // Find the first row from the top with non-zero entry (pivot entry) on the begin-column column as the "base-row".
    // Swap the base-row with the zeroth row so that the base-row is on the top.
    _swap_(beginRow,cscan(beginCol,beginRow));

    // Scale the base-row so that it is uniform.
    _scale_(beginRow);

    int curRow=beginRow;
    while(curRow<_row_){
        _replace_(beginRow,curRow);
        curRow++;
    }
    doForwardElim(beginRow+1,beginCol+1);
}

void doBackwardElim(){
    printf("Reverse Elimination:\n");
    int pivCol=0;
    for(int curRow=_row_-1;curRow>=0;curRow--){
        pivCol=rscan(curRow,0);
        if(pivCol==-1){continue;}
        for(int i=curRow-1;i>=0;i--){
            if(!mat[i][pivCol].isZero()){
                _replace_(curRow,i);
            }
        }
    }
}



void _iniMat_(){
    mat=new frac*[_row_];

    for(int i=0;i<_row_;++i){
        mat[i]=new frac[_col_];
    }

    int rtmp=0;
    for(int i=0;i<_row_;++i){
        for(int j=0;j<_col_;++j){
            cin>>rtmp;
            mat[i][j].init(rtmp);
        }
    }
}

void _iniFrcMat_(){
    mat=new frac*[_row_];

    for(int i=0;i<_row_;++i){
        mat[i]=new frac[_col_];
    }

    int numetmp=0;
    int denotmp=0;
    char aflag=' ';
    for(int i=0;i<_row_;++i){
        for(int j=0;j<_col_;++j){
            scanf("%c%d/%d",&aflag,&numetmp,&denotmp);
            mat[i][j].init(numetmp*(aflag=='+'?(1):(-1)),denotmp);
        }
    }
}


void _freeMat_(){
    for(int i=0;i<_row_;++i){
        delete [] mat[i];
    }
    delete [] mat;
}

void _printSol_(){
    int curRow=0;
    while(curRow<_row_){
        for(int i=0;i<_col_-1;++i){
            if(mat[curRow][i].isZero()){
                continue;
            }
            printf("%c",mat[curRow][i].sign?'+':'-');
            if(!(mat[curRow][i].nume==mat[curRow][i].deno)){
                printf("%d",mat[curRow][i].nume);
            }
            if(mat[curRow][i].deno!=1){
                printf("/%d",mat[curRow][i].deno);
            }
            printf("x{%d}",i);
        }
        ++curRow;
    }
}



void _printFrc_(frac opr){
    printf("%c%d/%d\n",opr.sign?'+':'-',opr.nume,opr.deno);
}

void _printMeta_(frac opr){
    printf("(%d,%d,%c)",opr.nume,opr.deno,opr.sign?'T':'F');
}

void make(){
    _iniMat_();
    doForwardElim(0,0);
    doBackwardElim();
    _printMat_();
}

void test(){
    frac m,n,o;
    o.init(52,12);
    _printMeta_(o);
}


int main(){
    cin>>_row_>>_col_;
    
    make();

    _freeMat_();
    return 0;

}