#ifndef LOADGAME_H
#define LOADGAME_H

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

void loadGame(int* banyakLokasi, ListDin* listBangunan, int* mapX, int* mapY, int* hqX, int* hqY, POINT* HQ, Matrix* adjMatrix, Map* map, Queue* quePesanan, int* banyakPesanan, TIME* gameTime, int* money, POINT* mobitaLoc, List* toDoList, List* inProgressList, int* bag_capacity, Stack* bag, ListPos* inventory, int* hvyItems, int* speedboostCount, int* VIPItemCount, boolean* returnToSender, int* kecilCount, int* deliveredCount);
/* Load game dari suatu file */

#endif