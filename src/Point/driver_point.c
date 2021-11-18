/*
    Driver ADT point
*/
#include <stdio.h>
#include "point.h"

int main()
{
    POINT P1, P2;
    int x, y;
    boolean SbX = true;
    scanf("%d %d", &x, &y);
    P1 = MakePOINT(x, y);
    printf("Point P1 : %d %d\n", x, y);
}