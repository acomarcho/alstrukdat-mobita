#ifndef INVENTORY_H
#define INVENTORY_H

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

void handleInventory(ListPos* inventory, List* inProgressList, Stack* bag, int* bag_capacity, ListDin listBangunan, POINT* mobitaLoc, TIME* gameTime, int* kecilCount);
/* Implementasi command inventory DAN implementasi gadget-gadget. */

#endif