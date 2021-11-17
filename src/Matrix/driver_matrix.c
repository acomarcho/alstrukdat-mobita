/*
    Driver ADT Matrix
*/
#include <stdio.h>
#include "matrix.h"

int main()
{
    int nRow, nCol;
    int i, j, Col, Row;
    scanf("%d %d", &Row, &Col);
    Matrix M;
    readMatrix(&M, Row, Col);
    scanf("%d %d", &nRow, &nCol);
    displayMatrix(M);
    CreateMatrix(nRow, nCol, &M);
    scanf("%d %d", &i, &j);
    isIdxValid(i, j);
    getLastIdxRow(M);
    getLastIdxCol(M);
    isIdxEff(M, i, j);
    getElmtDiagonal(M, i);
    Matrix M1;
    int Row1, Col1;
    scanf("%d %d", &Row1, &Col1);
    Matrix M2 = addMatrix(M, M1);
    displayMatrix(M2);
    Matrix M3 = subtractMatrix(M2, M1);
    displayMatrix(M3);
    M3 = multiplyMatrix(M2, M1);
    displayMatrix(M3);
    M3 = multiplyConst(M2, 4);
    displayMatrix(M3);
    pMultiplyConst(&M3, 8);
    displayMatrix(M3);
    if (isEqual(M1, M2))
    {
        printf("M1 dan M2 is Equal\n");
    }
    if (isNotEqual(M1, M2))
    {
        printf("M1 dan M2 is'nt Equal\n");
    }
    if (isSizeEqual(M2, M3))
    {
        printf("Size M2 dan M3 is Equal\n");
    }
    printf("%d\n", count(M1));
    if (isSquare(M))
    {
        printf("M is matriks persegi\n");
    }
    if (isSymmetric(M))
    {
        printf("M is matriks simetri\n");
    }
    if (isIdentity(M))
    {
        printf("M is matriks identitas\n");
    }
    if (isSparse(M))
    {
        printf("M is matriks sparse\n");
    }
    displayMatrix(inverse1(M));
    pInverse1(&M3);
    displayMatrix(M3);
    printf("%f\n", determinant(M));
    transpose(&M);
    displayMatrix(M);
    copyMatrix(M1, &M);
    displayMatrix(M1);
    return 0;
}
// gcc -o driver_matrix driver_matrix.c matrix.c