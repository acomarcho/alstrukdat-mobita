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
    scanf("%d %d", &x, &y);
    TulisPOINT(P1);
    P2 = MakePOINT(x, y);
    TulisPOINT(P2);
    if (EQ(P1, P2) == true)
    {
        printf("P1 dan P2 Equivalent\n");
    }
    if (NEQ(P1, P2) == true)
    {
        printf("P1 dan P2 tidak Equivalent\n");
    }
    if (IsOrigin(P1))
    {
        printf("P1 merupakan titik origin\n");
    }
    else
    {
        printf("P1 bukan titik origin\n");
    }
    if (IsOnSbX(P1))
    {
        printf("P1 berada di sumbu X\n");
    }
    if (IsOnSbX(P1))
    {
        printf("P1 berada di sumbu Y\n");
    }
    printf("P1 berada dikuadran ", Kuadran(P1));
    printf("P2 berada dikuadran ", Kuadran(P2));
    TulisPOINT(NextX(P1));
    TulisPOINT(NextY(P1));
    TulisPOINT(PlusDelta(P1, 2, 3));
    TulisPOINT(MirrorOf(P1, SbX));
    printf("%d", Jarak0(P1));
    printf("%d", Panjang(P1, P2));
    Geser(&P1, 3, 5);
    TulisPOINT(P1);
    GeserKeSbX(&P1);
    TulisPOINT(P1);
    GeserKeSbY(&P1);
    TulisPOINT(P1);
    Mirror(&P1, SbX);
    TulisPOINT(P1);
    Putar(&P1, 1.745); // P1 diputar sejauh 1.745 radian
    TulisPOINT(P1);
    return 0;
}