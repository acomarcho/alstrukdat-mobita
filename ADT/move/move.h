#ifndef MOVE_H
#define MOVE_H

#include "boolean.h"
#include "point.h"
#include "bag.h"
#include "TrashBox_Item.h"
#include "time.h"

void MOVEPos(char *POS_First, char POS_Moved);
/* Mengeset Nama Koordinat Mobita setelah berpindah */

void MOVEKoordinat(POINT *Coor_First, POINT Coor_Moved);
/* Mengeset Koorddinat Mobita setelah berpindah */

#endif