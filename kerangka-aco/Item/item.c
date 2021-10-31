#include "item.h"

Item CreateItem(int entryTime, char startLoc, char destLoc,  char itemType, int perishTime, int leftoverTime, Item* item) {
  Item newItem;
  newItem.entryTime = entryTime;
  newItem.startLoc = startLoc;
  newItem.destLoc = destLoc;
  newItem.itemType = itemType;
  newItem.perishTime = perishTime;
  newItem.leftoverTime = leftoverTime;
  *item = newItem;
}

boolean isItemEqual(Item item1, Item item2) {
  return (item1.entryTime == item2.entryTime) && (item1.startLoc == item2.startLoc) && (item1.destLoc == item2.destLoc) && (item1.itemType == item2.itemType) && (item1.perishTime == item2.perishTime) && (item1.leftoverTime == item2.leftoverTime);
}