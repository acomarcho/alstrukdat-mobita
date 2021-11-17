#ifndef MOVE_H
#define MOVE_H

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
#include "updatePerishables.h"
#include <stdio.h>

void move(POINT* mobitaLoc, ListDin listBangunan, Map map, int* speedboostCount, TIME* gameTime, List* inProgressList, Stack* bag, int hvyItems, int kecilCount);
/* Implementasi command MOVE */

#endif