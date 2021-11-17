#include "showState.h"

void showState(POINT mobitaLoc, ListDin listBangunan, TIME gameTime, int money, List toDoList, List inProgressList)
{
  /* Menunjukkan state game sekarang */
  printf("======================================================================\n");
  char locName = getLocationName(mobitaLoc, listBangunan);
  printf("Mobita berada di posisi %c (%d,%d)\n", locName, Absis(mobitaLoc), Ordinat(mobitaLoc));
  printf("Waktu: %d\n", Time(gameTime));
  printf("Uang yang dimiliki: %d Yen\n", money);
  if (LL_length(toDoList) > 0)
  {
    printf("Jumlah pesanan yang harus dikerjakan: %d\n", LL_length(toDoList) + LL_length(inProgressList));
  }
  printf("======================================================================\n");
}