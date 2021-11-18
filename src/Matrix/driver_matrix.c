/*
    Driver ADT Matrix
*/
#include <stdio.h>
#include "matrix.h"

int main()
{
    int Col, Row;
    scanf("%d %d", &Row, &Col);
    Matrix M;
    readMatrix(&M, Row, Col);
    displayMatrix(M);
}
// gcc -o driver_matrix driver_matrix.c matrix.c