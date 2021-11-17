#ifndef RETURNTOSENDER_H
#define RETURNTOSENDER_H

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

void handleReturn(boolean returnToSender, List* inProgressList, Stack* bag, List* toDoList, int* hvyItems, int* kecilCount);
/* Implementasi command RETURN */

#endif