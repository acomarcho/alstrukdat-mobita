#include <stdio.h>
#include "move.h"

void MOVEPos(char *POS_First, char POS_Moved)
/* Mengeset Nama Koordinat Mobita setelah berpindah */
{
    *POS_First = POS_Moved;
}

void MOVEKoordinat(POINT *Coor_First, POINT Coor_Moved)
/* Mengeset Koorddinat Mobita setelah berpindah */
{
    *Coor_First = Coor_Moved;
}
