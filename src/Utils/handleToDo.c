#include "handleToDo.h"

void handleToDo(Queue* quePesanan, TIME gameTime, int* VIPItemCount, List* toDoList) {
  /* Handle memasukkan pesanan ke To-Do List */
  while (!Q_isEmpty(*quePesanan) && Q_HEAD(*quePesanan).masuk <= Time(gameTime))
  {
    Item poppedItem;
    Q_dequeue(quePesanan, &poppedItem);
    if (poppedItem.jenis == 'V')
    {
      (*VIPItemCount) ++;
      printf("[!] VIP item masuk ke dalam TO_DO! Mobita tidak bisa pick-up item lain.\n");
      LL_insertFirst(toDoList, poppedItem);
    }
    else
    {
      LL_insertLast(toDoList, poppedItem);
    }
  }
}