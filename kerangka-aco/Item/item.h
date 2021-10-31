#ifndef __ITEM_H__
#define __ITEM_H__

#include "../ADT/boolean.h"

typedef struct {
  int entryTime;
  char startLoc;
  char destLoc;
  char itemType;
  int perishTime;
  int leftoverTime;
} Item;

Item CreateItem(int entryTime, char startLoc, char destLoc,  char itemType, int perishTime, int leftoverTime, Item* item);
// Membuat item berdasarkan entryTime, startLoc, destLoc, itemType, perishTime, dan leftoverTime.

boolean isItemEqual(Item item1, Item item2);
// Mengecek apakah item1 == item2.

#endif