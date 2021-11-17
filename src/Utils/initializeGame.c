#include "initializeGame.h"

void initializeGame(ListDin* listBangunan, TIME* gameTime, int* money, int* bag_capacity, List* toDoList, List* inProgressList, Stack* bag, ListPos* inventory, int* hvyItems, int* speedboostCount, int* VIPItemCount, boolean* returnToSender, int* kecilCount, int* deliveredCount) {
  /* Menginisialisasi variabel-variabel awal game */
  LD_CreateListDin(listBangunan, 30);
  CreateTime(gameTime);
  *money = 15000;
  *bag_capacity = 3;
  LL_CreateList(toDoList);
  LL_CreateList(inProgressList);
  ST_CreateStack(bag);
  CreateListPos(inventory);
  *hvyItems = 0;
  *speedboostCount = 0;
  *VIPItemCount = 0;
  *returnToSender = false;
  *kecilCount = 0;
  *deliveredCount = 0;
}