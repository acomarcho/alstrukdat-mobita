#include "move.h"

void move(POINT* mobitaLoc, ListDin listBangunan, Map map, int* speedboostCount, TIME* gameTime, List* inProgressList, Stack* bag, int hvyItems, int kecilCount) {
  /* Implementasi command MOVE */
  printf("Posisi yang dapat dicapai:\n");
  adjacentLocations lokasiTujuan = getAdjacentLocations(*mobitaLoc, listBangunan, map);
  for (int j = 0; j < lokasiTujuan.length; j++)
  {
    Bangunan bangunanAdj = LD_ELMT(listBangunan, lokasiTujuan.buffer[j]);
    printf("%d. %c (%d,%d)\n", j + 1, bangunanAdj.locName, Absis(bangunanAdj.locCoords), Ordinat(bangunanAdj.locCoords));
  }
  printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
  printf("\n        ENTER COMMAND: ");
  advWord();
  printf("\n");
  int pilihan = wordToInt(currentWord);
  if (pilihan == 0)
  {
    printf("Anda memilih untuk kembali.\n");
  }
  else if (pilihan < 0 || pilihan > lokasiTujuan.length)
  {
    printf("[!] Input Anda tidak sesuai.\n");
  }
  else
  {
    int idxBangunan = lokasiTujuan.buffer[pilihan - 1];
    Bangunan bangunan = LD_ELMT(listBangunan, idxBangunan);
    Absis(*mobitaLoc) = Absis(bangunan.locCoords);
    Ordinat(*mobitaLoc) = Ordinat(bangunan.locCoords);
    printf("Mobita sekarang berada di titik %c (%d,%d)!\n", bangunan.locName, Absis(*mobitaLoc), Ordinat(*mobitaLoc));
    if (*speedboostCount > 0)
    {
      printf("[!] Bergerak dengan speedboost!\n");
      (*speedboostCount) --;
      if (*speedboostCount % 2 == 0)
      {
        increaseTime(gameTime, 1);
        updatePerishables(inProgressList, bag, 1);
      }
      if (*speedboostCount == 0)
      {
        printf("[!] Speedboost Mobita telah habis.\n");
      }
    }
    else
    {
      increaseTime(gameTime, 1 + hvyItems - kecilCount);
      updatePerishables(inProgressList, bag, 1 + hvyItems - kecilCount);
      if (hvyItems - kecilCount > 0)
      {
        printf("[!] Terdapat tambahan %d waktu karena Mobita mengangkut Heavy Item.\n", hvyItems - kecilCount);
      }
    }
  }
}