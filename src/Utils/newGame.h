#ifndef NEWGAME_H
#define NEWGAME_H

#include "../FileMachine/filemachine.h"
#include "../WordMachine/wordmachine.h"
#include "../Item/item.h"
#include "../LinkedList/list_linked.h"
#include "../Listdin/listdin.h"
#include "../Map/map.h"
#include "../Matrix/matrix.h"
#include "../PColor/pcolor.h"
#include "../Point/point.h"
#include "../Queue/queue.h"
#include "../Time/time.h"
#include "../Stack/stack.h"
#include "../ListPos/listpos.h"
#include <stdio.h>

void newGame(int* mapX, int* mapY, int* hqX, int* hqY, ListDin* listBangunan, POINT *HQ, POINT *mobitaLoc, int* banyakLokasi, Matrix *adjMatrix, Map *map, int* banyakPesanan, Queue *quePesanan);
/* Membaca konfigurasi dari suatu file */

#endif