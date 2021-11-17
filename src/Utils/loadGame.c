#include "loadGame.h"

void loadGame(int* banyakLokasi, ListDin* listBangunan, int* mapX, int* mapY, int* hqX, int* hqY, POINT* HQ, Matrix* adjMatrix, Map* map, Queue* quePesanan, int* banyakPesanan, TIME* gameTime, int* money, POINT* mobitaLoc, List* toDoList, List* inProgressList, int* bag_capacity, Stack* bag, ListPos* inventory, int* hvyItems, int* speedboostCount, int* VIPItemCount, boolean* returnToSender, int* kecilCount, int* deliveredCount) {
  /* Load game dari suatu file */
  printf("Masukkan nama file save: ");
  advWord();
  startLine(currentWord.contents);
  while (endLine)
  {
    printf("[!] File save tidak ditemukan!\n");
    printf("Masukkan nama file save: ");
    advWord();
    startLine(currentWord.contents);
  }
  printf("File save ditemukan!\n");
  printf("Loading save...\n");
  /* BACA BANGUNAN */
  *banyakLokasi = fWordToInt(currentLine.contents[0]);
  for (int i = 0; i < *banyakLokasi; i++)
  {
    advLine();
    Bangunan b = LD_CreateBangunan(currentLine.contents[0].contents[0], fWordToInt(currentLine.contents[1]), fWordToInt(currentLine.contents[2]));
    LD_insertLast(listBangunan, b);
  }
  /* BACA UKURAN MAP */
  advLine();
  *mapX = fWordToInt(currentLine.contents[0]);
  *mapY = fWordToInt(currentLine.contents[1]);
  /* BACA LOKASI HEADQUARTERS */
  advLine();
  *hqX = fWordToInt(currentLine.contents[0]);
  *hqY = fWordToInt(currentLine.contents[1]);
  *HQ = MakePOINT(*hqX, *hqY);
  /* BACA ADJACENCY MATRIX */
  CreateMatrix(*banyakLokasi, *banyakLokasi, adjMatrix);
  for (int i = 0; i < *banyakLokasi; i++)
  {
    advLine();
    for (int j = 0; j < currentLine.length; j++)
    {
      ELMT(*adjMatrix, i, j) = fWordToInt(currentLine.contents[j]);
    }
  }
  CreateMap(*mapX, *mapY, *listBangunan, *adjMatrix, map);
  /* BACA QUEUE PESANAN */
  Q_CreateQueue(quePesanan);
  advLine();
  *banyakPesanan = fWordToInt(currentLine.contents[0]);
  for (int i = 0; i < *banyakPesanan; i++)
  {
    advLine();
    /* Parse item */
    int masuk = fWordToInt(currentLine.contents[0]);
    int nilai = fWordToInt(currentLine.contents[1]);
    int hangus = fWordToInt(currentLine.contents[2]);
    int sisa_waktu = fWordToInt(currentLine.contents[3]);
    char start = currentLine.contents[4].contents[0];
    char dest = currentLine.contents[5].contents[0];
    char jenis = currentLine.contents[6].contents[0];
    boolean isKecil = fWordToInt(currentLine.contents[7]);
    Item it;
    CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
    Q_enqueue(quePesanan, it);
  }
  /* BACA TIME */
  advLine();
  Time(*gameTime) = fWordToInt(currentLine.contents[0]);
  /* BACA MONEY */
  advLine();
  *money = fWordToInt(currentLine.contents[0]);
  /* BACA LOKASI MOBITA */
  advLine();
  *mobitaLoc = MakePOINT(fWordToInt(currentLine.contents[0]), fWordToInt(currentLine.contents[1]));
  /* BACA TO DO LIST */
  advLine();
  int toDoCount = fWordToInt(currentLine.contents[0]);
  for (int i = 0; i < toDoCount; i++)
  {
    advLine();
    /* Parse item */
    int masuk = fWordToInt(currentLine.contents[0]);
    int nilai = fWordToInt(currentLine.contents[1]);
    int hangus = fWordToInt(currentLine.contents[2]);
    int sisa_waktu = fWordToInt(currentLine.contents[3]);
    char start = currentLine.contents[4].contents[0];
    char dest = currentLine.contents[5].contents[0];
    char jenis = currentLine.contents[6].contents[0];
    boolean isKecil = fWordToInt(currentLine.contents[7]);
    Item it;
    CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
    LL_insertLast(toDoList, it);
  }
  /* BACA IN PROGRESS LIST */
  advLine();
  int inProgressCount = fWordToInt(currentLine.contents[0]);
  for (int i = 0; i < inProgressCount; i++)
  {
    advLine();
    /* Parse item */
    int masuk = fWordToInt(currentLine.contents[0]);
    int nilai = fWordToInt(currentLine.contents[1]);
    int hangus = fWordToInt(currentLine.contents[2]);
    int sisa_waktu = fWordToInt(currentLine.contents[3]);
    char start = currentLine.contents[4].contents[0];
    char dest = currentLine.contents[5].contents[0];
    char jenis = currentLine.contents[6].contents[0];
    boolean isKecil = fWordToInt(currentLine.contents[7]);
    Item it;
    CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
    LL_insertLast(inProgressList, it);
  }
  /* BACA BAG CAPACITY */
  advLine();
  *bag_capacity = fWordToInt(currentLine.contents[0]);
  /* BACA BAG */
  advLine();
  int banyakBag = fWordToInt(currentLine.contents[0]);
  for (int i = 0; i < banyakBag; i++)
  {
    advLine();
    /* Parse item */
    int masuk = fWordToInt(currentLine.contents[0]);
    int nilai = fWordToInt(currentLine.contents[1]);
    int hangus = fWordToInt(currentLine.contents[2]);
    int sisa_waktu = fWordToInt(currentLine.contents[3]);
    char start = currentLine.contents[4].contents[0];
    char dest = currentLine.contents[5].contents[0];
    char jenis = currentLine.contents[6].contents[0];
    boolean isKecil = fWordToInt(currentLine.contents[7]);
    Item it;
    CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
    ST_push(bag, it);
  }
  /* BACA INVENTORY */
  advLine();
  LP_ELMT(*inventory, 0) = fWordToInt(currentLine.contents[0]);
  LP_ELMT(*inventory, 1) = fWordToInt(currentLine.contents[1]);
  LP_ELMT(*inventory, 2) = fWordToInt(currentLine.contents[2]);
  LP_ELMT(*inventory, 3) = fWordToInt(currentLine.contents[3]);
  LP_ELMT(*inventory, 4) = fWordToInt(currentLine.contents[4]);
  /* BACA hvyItems */
  advLine();
  *hvyItems = fWordToInt(currentLine.contents[0]);
  /* BACA speedboostCount */
  advLine();
  *speedboostCount = fWordToInt(currentLine.contents[0]);
  /* BACA VIPItemCount */
  advLine();
  *VIPItemCount = fWordToInt(currentLine.contents[0]);
  /* BACA returnToSender */
  advLine();
  *returnToSender = fWordToInt(currentLine.contents[0]);
  /* BACA kecilCount */
  advLine();
  *kecilCount = fWordToInt(currentLine.contents[0]);
  /* BACA deliveredCount */
  advLine();
  *deliveredCount = fWordToInt(currentLine.contents[0]);
}