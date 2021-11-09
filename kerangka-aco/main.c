#include <stdio.h>
#include <stdlib.h>
#include "ADT/mesinfile.h"
#include "Listdin/listdin.h"
#include "Map/map.h"
#include "Queue/queue.h"
#include "ADT/wordmachine.h"
#include "Stack/stack.h"
#include "LinkedList/list_linked.h"
#include "ADT/listpos.h"

void printWord(fWord word) {
  for (int i = 0; i < word.length; i ++) {
    printf("%c", word.contents[i]);
  }
}

int wordToInt(fWord word) {
  int num = 0;
  for (int i = 0; i < word.length; i ++) {
    num = num * 10 + word.contents[i] - 48;
  }
  return num;
}

int wordToInt2(Word word) {
  int num = 0;
  for (int i = 0; i < word.length; i ++) {
    num = num * 10 + word.contents[i] - 48;
  }
  return num;
}

void printListBangunan(ListDin l) {
  printf("=== LIST BANGUNAN ===\n");
  for (int i = 0; LD_isIdxEff(l, i); i ++) {
    Bangunan b = LD_ELMT(l, i);
    printf("%c: (%d, %d)\n", b.locName, Absis(b.locCoords), Ordinat(b.locCoords));
  }
}

int main() {
  // ======================== BACA KONFIGURASI ======================== //
  // Buat ListDin.
  ListDin listBangunan;
  LD_CreateListDin(&listBangunan, 30);
  // Baca file; Line pertama: ukuran peta
  startLine("konfigurasi.txt");
  int N, M;
  N = wordToInt(currentLine.contents[0]);
  M = wordToInt(currentLine.contents[1]);
  // printf("Ukuran peta Anda adalah %d x %d.\n", N, M);
  // Line kedua: Koordinat headquarters
  advLine();
  int hqX, hqY;
  hqX = wordToInt(currentLine.contents[0]);
  hqY = wordToInt(currentLine.contents[1]);
  Bangunan HQ = LD_CreateBangunan('8', hqX, hqY);
  LD_insertLast(&listBangunan, HQ);
  // printf("HQ terletak di koordinat (%d,%d).\n", hqX, hqY);
  // Line ketiga: Jumlah lokasi
  advLine();
  int jumlahLokasi;
  jumlahLokasi = wordToInt(currentLine.contents[0]);
  // printf("Anda memasukkan %d lokasi.\n", jumlahLokasi);
  // Input lokasi.
  for (int i = 0; i < jumlahLokasi; i ++) {
    advLine();
    char locName = currentLine.contents[0].contents[0];
    int x, y;
    x = wordToInt(currentLine.contents[1]);
    y = wordToInt(currentLine.contents[2]);
    Bangunan inputLoc = LD_CreateBangunan(locName, x, y);
    LD_insertLast(&listBangunan, inputLoc);
  }
  // printListBangunan(listBangunan);
  // Buat matrix adjMatrix
  Matrix adjMatrix;
  CreateMatrix(jumlahLokasi + 1, jumlahLokasi + 1, &adjMatrix);
  for (int i = 0; i < jumlahLokasi + 1; i ++) {
    advLine();
    for (int j = 0; j < currentLine.length; j ++) {
      ELMT(adjMatrix, i, j) = wordToInt(currentLine.contents[j]);
    }
  }
  // Buat peta!
  Map map;
  CreateMap(N, M, listBangunan, adjMatrix, &map);
  // // Uji peta.
  // displayMap(map, listBangunan);
  // // Uji perihal adjacency matrix.
  // for (int i = 0; i < LD_length(listBangunan); i ++) {
  //   POINT loc = LD_ELMT(listBangunan, i).locCoords;
  //   adjacentLocations toProcess = getAdjacentLocations(loc, listBangunan, map);
  //   printf("Lokasi yang bisa ditempuh dari titik %c (%d, %d): \n", LD_ELMT(listBangunan, i).locName, Absis(loc), Ordinat(loc));
  //   for (int j = 0; j < toProcess.length; j ++) {
  //     Bangunan bangunanAdj = LD_ELMT(listBangunan, toProcess.buffer[j]);
  //     printf("%c (%d, %d)\n", bangunanAdj.locName, Absis(bangunanAdj.locCoords), Ordinat(bangunanAdj.locCoords));
  //   }
  // }
  // Baca jumlah pesanan.
  advLine();
  int jumlahPesanan;
  jumlahPesanan = wordToInt(currentLine.contents[0]);
  Queue quePesanan;
  Q_CreateQueue(&quePesanan);
  // Loop pada jumlah pesanan.
  for (int i = 0; i < jumlahPesanan; i ++) {
    advLine();
    Item newItem;
    int argCount = currentLine.length;
    int entryTime = wordToInt(currentLine.contents[0]);
    char startLoc = currentLine.contents[1].contents[0];
    char destLoc = currentLine.contents[2].contents[0];
    char itemType = currentLine.contents[3].contents[0];
    if (argCount == 4) {
      CreateItem(entryTime, startLoc, destLoc, itemType, -1, -1, &newItem);
    } else {
      CreateItem(entryTime, startLoc, destLoc, itemType, wordToInt(currentLine.contents[4]), wordToInt(currentLine.contents[5]), &newItem);
    }
    Q_enqueue(&quePesanan, newItem);
  }
  // Q_displayQueue(quePesanan);
  // printf("\n");
  // ======================== END OF BACA KONFIGURASI ======================== //
  // ======================== INISIALISASI GAME ======================== //
  int time = 1;
  int money = 15000;
  POINT Headquarters = MakePOINT(hqX, hqY);
  POINT mobitaLoc = MakePOINT(hqX, hqY);
  Stack bag; ST_CreateStack(&bag);
  List toDoList; LL_CreateList(&toDoList);
  List inProgressList; LL_CreateList(&inProgressList);
  ListPos inventory; CreateListPos(&inventory);
  // yang sudah ada: map, quePesanan, listBangunan.
  // ======================== END OF INISIALISASI GAME ======================== //
  // ======================== TES MESIN KATA ======================== //
  // boolean end = false;
  // printf("Masukkan command: ");
  // startWord();
  // do {
  //   printf("Anda memasukkan command: ");
  //   for (int i = 0; i < currentWord.length; i ++) {
  //     printf("%c", currentWord.contents[i]);
  //   }
  //   printf("\n");
  //   printf("Masukkan command: ");
  //   advWord();
  // } while (!end);
  // ======================== END OF TES MESIN KATA ======================== //
  // ======================== LOOP GAME ======================== //
  boolean end = false;
  boolean firstCommand = true;
  while (!end) {
    // MASUKKAN KE TO-DO LIST ELEMEN YANG ADA DI QUEUE PESANAN APABILA WAKTU SESUAI
    while (Q_HEAD(quePesanan).entryTime <= time) {
      Item poppedItem;
      Q_dequeue(&quePesanan, &poppedItem);
      LL_insertLast(&toDoList, poppedItem);
    }
    // TAMPILKAN INFO STATE GAME SEKARANG
    printf("======================================================================\n");
    char locName = getLocationName(mobitaLoc, listBangunan);
    printf("Mobita berada di posisi %c (%d,%d)\n", locName, Absis(mobitaLoc), Ordinat(mobitaLoc));
    printf("Waktu: %d\n", time);
    printf("Uang yang dimiliki: %d Yen\n", money);
    if (LL_length(toDoList) > 0) {
      printf("Jumlah pesanan yang harus dikerjakan: %d\n", LL_length(toDoList));
    }
    printf("======================================================================\n");
    printf("ENTER COMMAND: ");
    if (firstCommand) {
      startWord();
      firstCommand = false;
    } else {
      advWord();
    }
    // CEK COMMAND
    if (isWordEqual(currentWord, "MAP")) { // COMMAND MAP
      displayMap(map, listBangunan, toDoList, inProgressList, mobitaLoc);
    } else if (isWordEqual(currentWord, "TO_DO")) { // COMMAND TO-DO
      printf("Pesanan pada To Do List:\n");
      // Traversal pada toDoList.
      Address p = LL_FIRST(toDoList);
      if (p == NULL) {
        printf("Tidak ada pesanan pada To Do List.\n");
      } else {
        int num = 1;
        do {
          Item item = INFO(p);
          switch(item.itemType) {
            case 'N':
              printf("%d. %c -> %c (Normal Item)", num, item.startLoc, item.destLoc);
              break;
            case 'H':
              printf("%d. %c -> %c (Heavy Item)", num, item.startLoc, item.destLoc);
              break;
            case 'P':
              printf("%d. %c -> %c (Perishable Item)", num, item.startLoc, item.destLoc);
              break;
            case 'V':
              printf("%d. %c -> %c (VIP Item)", num, item.startLoc, item.destLoc);
              break;
          }
          num ++;
          p = NEXT(p);
          printf("\n");
        } while (p != NULL);
      }
    } else if (isWordEqual(currentWord, "IN_PROGRESS")) { // COMMAND IN-PROGRESS
      printf("Pesanan yang sedang diantarkan:\n");
      // Traversal pada toDoList.
      Address p = LL_FIRST(inProgressList);
      if (p == NULL) {
        printf("Tidak ada pesanan yang sedang diantarkan.\n");
      } else {
        int num = 1;
        do {
          Item item = INFO(p);
          switch(item.itemType) {
            case 'N':
              printf("%d. Normal Item (Tujuan: %c)", num, item.destLoc);
              break;
            case 'H':
              printf("%d. Heavy Item (Tujuan: %c)", num, item.destLoc);
              break;
            case 'P':
              printf("%d. Perishable Item (Tujuan: %c)", num, item.destLoc);
              break;
            case 'V':
              printf("%d. VIP Item (Tujuan: %c)", num, item.destLoc);
              break;
          }
          num ++;
          p = NEXT(p);
          printf("\n");
        } while (p != NULL);
      }
    } else if (isWordEqual(currentWord, "MOVE")) {  // COMMAND MOVE
      printf("Posisi yang dapat dicapai:\n");
      adjacentLocations lokasiTujuan = getAdjacentLocations(mobitaLoc, listBangunan, map);
      for (int j = 0; j < lokasiTujuan.length; j ++) {
        Bangunan bangunanAdj = LD_ELMT(listBangunan, lokasiTujuan.buffer[j]);
        printf("%d. %c (%d,%d)\n", j + 1, bangunanAdj.locName, Absis(bangunanAdj.locCoords), Ordinat(bangunanAdj.locCoords));
      }
      printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
      printf("ENTER COMMAND: ");
      advWord();
      int pilihan = wordToInt2(currentWord);
      if (pilihan == 0) {
        printf("Anda memilih untuk kembali.\n");
      } else {
        int idxBangunan = lokasiTujuan.buffer[pilihan - 1];
        Bangunan bangunan = LD_ELMT(listBangunan, idxBangunan);
        Absis(mobitaLoc) = Absis(bangunan.locCoords);
        Ordinat(mobitaLoc) = Ordinat(bangunan.locCoords);
        printf("Mobita sekarang berada di titik %c (%d,%d)!\n", bangunan.locName, Absis(mobitaLoc), Ordinat(mobitaLoc));
        time ++;
      }
    } else if (isWordEqual(currentWord, "PICK_UP")) { // COMMAND PICK_UP
      // Cari item pada toDoList.
      boolean found = false;
      int idx = 0;
      Address p = LL_FIRST(toDoList);
      while (p != NULL && !found) {
        if (INFO(p).startLoc == getLocationName(mobitaLoc, listBangunan)) {
          found = true;
        } else {
          p = NEXT(p);
          idx ++;
        }
      }
      if (found) {
        Item item = INFO(p);
        switch(item.itemType) {
          case 'N':
            printf("Pesanan berupa Normal Item berhasil diambil!\n");
            break;
          case 'H':
            printf("Pesanan berupa Heavy Item berhasil diambil!\n");
            break;
          case 'P':
            printf("Pesanan berupa Perishable Item berhasil diambil!\n");
            break;
          case 'V':
            printf("Pesanan berupa VIP Item berhasil diambil!\n");
            break;
        }
        // Masukkan item ke inProgressList
        LL_insertFirst(&inProgressList, item);
        // Masukkan item ke tas.
        ST_push(&bag, item);
        // Hapus dari toDoList
        Item tmp;
        LL_deleteAt(&toDoList, idx, &tmp);
      } else {
        printf("Pesanan tidak ditemukan!\n");
      }
    } else if (isWordEqual(currentWord, "DROP_OFF")) {
      if (LL_isEmpty(inProgressList)) {
        printf("Tidak ada pesanan yang dapat diantarkan!\n");
      } else {
        Item item = INFO(LL_FIRST(inProgressList));
        if (item.destLoc == getLocationName(mobitaLoc, listBangunan)) { // Lokasi benar!
          int prize;
          switch (item.itemType) {
            case 'N':
              printf("Pesanan Normal Item berhasil diantarkan.\n");
              prize = 200;
              break;
            case 'H':
              printf("Pesanan Heavy Item berhasil diantarkan.\n");
              prize = 400;
              break;
            case 'P':
              printf("Pesanan Perishable Item berhasil diantarkan.\n");
              prize = 400;
              break;
            case 'V':
              printf("Pesanan VIP Item berhasil diantarkan.\n");
              prize = 600;
              break;
          }
          money += prize;
          printf("Uang yang didapatkan: %d Yen\n", prize);
          // Hapus dari inProgressList dan bag.
          Item tmp;
          LL_deleteFirst(&inProgressList, &tmp);
          ST_pop(&bag, &tmp);
        } else { // Lokasi salah.
          printf("Tidak ada pesanan yang dapat diantarkan!\n");
        }
      }
    } else if (isWordEqual(currentWord, "BUY")) { // COMMAND BUY
      if ((Absis(mobitaLoc) == Absis(Headquarters)) && (Ordinat(mobitaLoc) == Ordinat(Headquarters))) {
        if (!isFull(inventory)) {
          printf("Uang Anda sekarang: %d Yen\n", money);
          printf("Gadget yang tersedia:\n");
          printf("1. Kain Pembungkus Waktu (800 Yen)\n");
          printf("2. Senter Pembesar (1200 Yen)\n");
          printf("3. Pintu Kemana Saja (1500 Yen)\n");
          printf("4. Mesin Waktu (3000 Yen)\n");
          printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n\n");
          int pilihan_buy;
          for (;;) {
            printf("ENTER COMMAND: ");
            advWord();
            pilihan_buy = wordToInt2(currentWord);
            if ((pilihan_buy >= 0) && (pilihan_buy <= 4)) {
              break;
            } else {
              printf("Input tidak valid.\n");
            }
          }
          if (pilihan_buy == 0) {
            printf("Anda memilih untuk kembali.\n");
          } else if (pilihan_buy == 1) {
            if (money >= 800) {
              money -= 800;
              send_to_inventory(&inventory, pilihan_buy);
              printf("Kain Pembungkus Waktu berhasil dibeli!\n");
              printf("Uang Anda sekarang: %d Yen\n", money);
            } else {
              printf("Uang tidak cukup untuk membeli gadget!\n");
            }
          } else if (pilihan_buy == 2) {
            if (money >= 1200) {
              money -= 1200;
              send_to_inventory(&inventory, pilihan_buy);
              printf("Senter Pembesar berhasil dibeli!\n");
              printf("Uang Anda sekarang: %d Yen\n", money);
            } else {
              printf("Uang tidak cukup untuk membeli gadget!\n");
            }
          } else if (pilihan_buy == 3) {
            if (money >= 1500) {
              money -= 1500;
              send_to_inventory(&inventory, pilihan_buy);
              printf("Pintu Kemana Saja berhasil dibeli!\n");
              printf("Uang Anda sekarang: %d Yen\n", money);
            } else {
              printf("Uang tidak cukup untuk membeli gadget!\n");
            }
          } else if (pilihan_buy == 4) {
            if (money >= 3000) {
              money -= 3000;
              send_to_inventory(&inventory, pilihan_buy);
              printf("Mesin Waktu berhasil dibeli!\n");
              printf("Uang Anda sekarang: %d Yen\n", money);
            } else {
              printf("Uang tidak cukup untuk membeli gadget!\n");
            }
          }
        } else {
          printf("Inventory penuh. Anda tidak dapat membeli gadget.\n");
        }
      } else {
        printf("Anda tidak sedang berada di Headquarters\n");
      }
    } else if (isWordEqual(currentWord, "INVENTORY")) { // COMMAND INVENTORY
      for (int i = 0; i < LP_CAPACITY; i++) {
        printf("%d. ", i+1);
        if (LP_ELMT(inventory, i) == LP_VAL_UNDEF) {
          printf("-\n");
        } else if (LP_ELMT(inventory, i) == 1) {
          printf("Kain Pembungkus Waktu\n");
        } else if (LP_ELMT(inventory, i) == 2) {
          printf("Senter Pembesar\n");
        } else if (LP_ELMT(inventory, i) == 3) {
          printf("Pintu Kemana Saja\n");
        } else if (LP_ELMT(inventory, i) == 4) {
          printf("Mesin Waktu\n");
        }
      }
      printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n\n");
      int pilihan_inventory;
      for (;;) {
        printf("ENTER COMMAND: ");
        advWord();
        pilihan_inventory = wordToInt2(currentWord);
        if ((pilihan_inventory >= 0) && (pilihan_inventory <= LP_CAPACITY)) {
          break;
        } else {
          printf("Input tidak valid.\n");
        }
      }
      if (pilihan_inventory == 0) {
        printf("Anda memilih untuk kembali.\n");
      } else {
        for (int i = 1; i <= LP_CAPACITY; i++) {
          if (i == pilihan_inventory) {
            if (LP_ELMT(inventory, i-1) == LP_VAL_UNDEF) {
              printf("Tidak ada Gadget yang dapat digunakan!\n");
            } else if (LP_ELMT(inventory, i-1) == 1) {
              LP_ELMT(inventory, i-1) = LP_VAL_UNDEF;
              printf("Kain Pembungkus Waktu berhasil digunakan!\n");
            } else if (LP_ELMT(inventory, i-1) == 2) {
              LP_ELMT(inventory, i-1) = LP_VAL_UNDEF;
              printf("Senter Pembesar berhasil digunakan!\n");
            } else if (LP_ELMT(inventory, i-1) == 3) {
              LP_ELMT(inventory, i-1) = LP_VAL_UNDEF;
              printf("Pintu Kemana Saja berhasil digunakan!\n");
            } else if (LP_ELMT(inventory, i-1) == 4) {
              LP_ELMT(inventory, i-1) = LP_VAL_UNDEF;
              printf("Mesin Waktu berhasil digunakan!\n");
            }
            break;
          }
        }
      }
    } else if (isWordEqual(currentWord, "HELP")) { // COMMAND HELP
      printf("1. MOVE -> Untuk berpindah ke lokasi selanjutnya\n");
      printf("2. PICK_UP -> Untuk mengambil item di lokasi sekarang\n");
      printf("3. DROP_OFF -> Untuk mengantarkan item ke lokasi sekarang\n");
      printf("4. MAP -> Untuk memunculkan peta\n");
      printf("5. TO_DO -> Untuk menampilkan pesanan yang masuk ke To Do List\n");
      printf("6. IN_PROGRESS -> Untuk menampilkan pesanan yang sedang dikerjakan\n");
      printf("7. BUY -> Untuk menampilkan gadget yang dapat dibeli dan membelinya\n");
      printf("8. INVENTORY -> Untuk melihat gadget yang dimiliki dan menggunakannya\n");
      printf("9. HELP -> Untuk mengeluarkan list command dan kegunaannya\n");
    }
  }
  // ======================== END OF LOOP GAME ======================== //
  return 0;
}