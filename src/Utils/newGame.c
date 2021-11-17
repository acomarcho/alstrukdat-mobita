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

void newGame(int* mapX, int* mapY, int* hqX, int* hqY, ListDin* listBangunan, POINT *HQ, POINT *mobitaLoc, int* banyakLokasi, Matrix *adjMatrix, Map *map, int* banyakPesanan, Queue *quePesanan) {
  /* Membaca konfigurasi dari suatu file */
  printf("Masukkan nama file konfigurasi: ");
  advWord();
  startLine(currentWord.contents);
  while (endLine)
  {
    printf("[!] File konfigurasi tidak ditemukan!\n");
    printf("Masukkan nama file konfigurasi: ");
    advWord();
    startLine(currentWord.contents);
  }
  // File sudah ditemukan.
  printf("File konfigurasi ditemukan!\n");
  printf("Loading konfigurasi...\n");
  // Load besar map.
  *mapX = fWordToInt(currentLine.contents[0]);
  *mapY = fWordToInt(currentLine.contents[1]);
  // Load koordinat headquarters.
  advLine();
  *hqX = fWordToInt(currentLine.contents[0]);
  *hqY = fWordToInt(currentLine.contents[1]);
  Bangunan hq = LD_CreateBangunan('8', *hqX, *hqY);
  LD_insertLast(listBangunan, hq);
  *HQ = MakePOINT(*hqX, *hqY);
  *mobitaLoc = MakePOINT(*hqX, *hqY);
  // Load jumlah lokasi.
  advLine();
  *banyakLokasi = fWordToInt(currentLine.contents[0]);
  // Input masing-masing lokasi.
  for (int i = 0; i < *banyakLokasi; i++)
  {
    advLine();
    char locName = currentLine.contents[0].contents[0];
    int x, y;
    x = fWordToInt(currentLine.contents[1]);
    y = fWordToInt(currentLine.contents[2]);
    Bangunan inputLoc = LD_CreateBangunan(locName, x, y);
    LD_insertLast(listBangunan, inputLoc);
  }
  // Dari list bangunan, inisialisasi adjMatrix.
  CreateMatrix(*banyakLokasi + 1, *banyakLokasi + 1, adjMatrix);
  for (int i = 0; i < *banyakLokasi + 1; i++)
  {
    advLine();
    for (int j = 0; j < currentLine.length; j++)
    {
      ELMT(*adjMatrix, i, j) = fWordToInt(currentLine.contents[j]);
    }
  }
  // Buat peta!
  CreateMap(*mapX, *mapY, *listBangunan, *adjMatrix, map);
  // Baca jumlah pesanan.
  advLine();
  *banyakPesanan = fWordToInt(currentLine.contents[0]);
  Q_CreateQueue(quePesanan);
  for (int i = 0; i < *banyakPesanan; i++)
  {
    advLine();
    Item newItem;
    int argCount = currentLine.length;
    int entryTime = fWordToInt(currentLine.contents[0]);
    char startLoc = currentLine.contents[1].contents[0];
    char destLoc = currentLine.contents[2].contents[0];
    char itemType = currentLine.contents[3].contents[0];
    if (argCount == 4)
    {
      CreateItem(&newItem, entryTime, startLoc, destLoc, itemType);
    }
    else
    {
      CreatePerishableItem(&newItem, entryTime, startLoc, destLoc, fWordToInt(currentLine.contents[4]));
    }
    Q_enqueue(quePesanan, newItem);
  }
}