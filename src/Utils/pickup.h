#ifndef PICKUP_H
#define PICKUP_H

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

void pickup(List* toDoList, POINT mobitaLoc, ListDin listBangunan, int VIPItemCount, Stack* bag, int bag_capacity, int* hvyItems, int* speedboostCount, List* inProgressList);
/* Implementasi command PICK_UP */

#endif