#include "saveGame.h"

void saveGame(ListDin listBangunan, int mapX, int mapY, POINT HQ,  POINT mobitaLoc, Matrix adjMatrix, Queue quePesanan, TIME gameTime, int money, List toDoList, List inProgressList, int bag_capacity, Stack bag, ListPos inventory, int hvyItems, int speedboostCount, int VIPItemCount, boolean returnToSender, int kecilCount, int deliveredCount) {
  /* Implementasi command SAVE_GAME */
  // Simpan pada file.
  printf("Masukkan nama file penyimpanan (contoh: save.txt): ");
  advWord();
  FILE *fpointer = fopen(currentWord.contents, "w");
  // Banyak bangunan
  fprintf(fpointer, "%d\n", listBangunan.nEff);
  // Bangunannya
  for (int i = 0; i < listBangunan.nEff; i++)
  {
    Bangunan b = listBangunan.buffer[i];
    fprintf(fpointer, "%c %d %d\n", b.locName, Absis(b.locCoords), Ordinat(b.locCoords));
  }
  // Ukuran map
  fprintf(fpointer, "%d %d\n", mapX, mapY);
  // Lokasi HQ
  fprintf(fpointer, "%d %d\n", Absis(HQ), Ordinat(HQ));
  // Adjacency matrix
  for (int i = 0; i <= getLastIdxRow(adjMatrix); i++)
  {
    for (int j = 0; j <= getLastIdxCol(adjMatrix); j++)
    {
      if (j != getLastIdxCol(adjMatrix))
      {
        fprintf(fpointer, "%d ", adjMatrix.contents[i][j]);
      }
      else
      {
        fprintf(fpointer, "%d\n", adjMatrix.contents[i][j]);
      }
    }
  }
  // Queue Pesanan
  fprintf(fpointer, "%d\n", Q_length(quePesanan));
  if (!Q_isEmpty(quePesanan))
  {
    for (int i = Q_IDX_HEAD(quePesanan); i <= Q_IDX_TAIL(quePesanan); i++)
    {
      Item it = quePesanan.buffer[i];
      fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
    }
  }
  // Time
  fprintf(fpointer, "%d\n", Time(gameTime));
  // Money
  fprintf(fpointer, "%d\n", money);
  // Lokasi Mobita
  fprintf(fpointer, "%d %d\n", Absis(mobitaLoc), Ordinat(mobitaLoc));
  // To-do List
  fprintf(fpointer, "%d\n", LL_length(toDoList));
  Address p = LL_FIRST(toDoList);
  while (p != NULL)
  {
    Item it = NODE_INFO(p);
    fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
    p = NODE_NEXT(p);
  }
  // In-progress List
  fprintf(fpointer, "%d\n", LL_length(inProgressList));
  p = LL_FIRST(inProgressList);
  while (p != NULL)
  {
    Item it = NODE_INFO(p);
    fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
    p = NODE_NEXT(p);
  }
  // Bag capacity
  fprintf(fpointer, "%d\n", bag_capacity);
  // Bag
  fprintf(fpointer, "%d\n", ST_IDX_TOP(bag) + 1);
  for (int i = 0; i <= ST_IDX_TOP(bag); i++)
  {
    Item it = bag.buffer[i];
    fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
  }
  // List inventory
  fprintf(fpointer, "%d %d %d %d %d\n", LP_ELMT(inventory, 0), LP_ELMT(inventory, 1), LP_ELMT(inventory, 2), LP_ELMT(inventory, 3), LP_ELMT(inventory, 4));
  // hvyItems
  fprintf(fpointer, "%d\n", hvyItems);
  // speedboostCount
  fprintf(fpointer, "%d\n", speedboostCount);
  // VIPItemCount
  fprintf(fpointer, "%d\n", VIPItemCount);
  // returnToSender
  fprintf(fpointer, "%d\n", returnToSender); // 1 = true; 0 = false
  // kecilCount
  fprintf(fpointer, "%d\n", kecilCount);
  // deliveredCount
  fprintf(fpointer, "%d\n", deliveredCount);

  fclose(fpointer);

  printf("[!] Progress berhasil disimpan di %s!\n", currentWord.contents);
}