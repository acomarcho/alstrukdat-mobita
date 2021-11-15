#include "FileMachine/filemachine.h"
#include "WordMachine/wordmachine.h"
#include "Item/item.h"
#include "LinkedList/list_linked.h"
#include "Listdin/listdin.h"
#include "Map/map.h"
#include "Matrix/matrix.h"
#include "PColor/pcolor.h"
#include "Point/point.h"
#include "Queue/queue.h"
#include "Time/time.h"
#include "Stack/stack.h"
#include "ListPos/listpos.h"
#include <stdio.h>

// gcc -o main main.c FileMachine/filemachine.c WordMachine/wordmachine.c WordMachine/charmachine.c Item/item.c LinkedList/list_linked.c LinkedList/node.c Listdin/listdin.c Map/map.c Matrix/matrix.c PColor/pcolor.c Point/point.c Queue/queue.c Time/time.c Stack/stack.c ListPos/listpos.c

void showState(POINT mobitaLoc, ListDin listBangunan, TIME gameTime, int money, List toDoList, List inProgressList) {
  /* Menunjukkan state game sekarang */
  printf("======================================================================\n");
  char locName = getLocationName(mobitaLoc, listBangunan);
  printf("Mobita berada di posisi %c (%d,%d)\n", locName, Absis(mobitaLoc), Ordinat(mobitaLoc));
  printf("Waktu: %d\n", Time(gameTime));
  printf("Uang yang dimiliki: %d Yen\n", money);
  if (LL_length(toDoList) > 0) {
    printf("Jumlah pesanan yang harus dikerjakan: %d\n", LL_length(toDoList) + LL_length(inProgressList));
  }
  printf("======================================================================\n");
}

void updatePerishables(List* inProgressList, Stack* bag, int time) {
  // Update inProgressList.
  Address prev = NULL;
  Address p = LL_FIRST(*inProgressList);
  List newList; LL_CreateList(&newList);
  while (p != NULL) {
    if (NODE_INFO(p).jenis == 'P') {
      NODE_INFO(p).sisa_waktu -= time;
      if (NODE_INFO(p).sisa_waktu > 0) {
        LL_insertLast(&newList, NODE_INFO(p));
      } else {
        printf("[!] Gagal mengirimkan perishable (%c -> %c) karena waktu sudah habis.\n", NODE_INFO(p).start, NODE_INFO(p).dest);
      }
    } else {
      LL_insertLast(&newList, NODE_INFO(p));
    }
    p = NODE_NEXT(p);
  }
  *inProgressList = newList;
  // Update bag.
  Stack tmpBag; ST_CreateStack(&tmpBag);
  while (!ST_isEmpty(*bag)) {
    Item tmp; ST_pop(bag, &tmp);
    if (tmp.jenis == 'P') {
      tmp.sisa_waktu -= time;
      if (tmp.sisa_waktu > 0) {
        ST_push(&tmpBag, tmp);
      }
      // Jika habis, tidak usah dipush.
    } else {
      ST_push(&tmpBag, tmp);
    }
  }
  // tmpBag terbalik.
  ST_CreateStack(bag);
  while (!ST_isEmpty(tmpBag)) {
    Item tmp; ST_pop(&tmpBag, &tmp);
    ST_push(bag, tmp);
  }
}

void cetakBag(Stack bag) {
  /* For debugging purposes only */
  for (int i = bag.idxTop; i >= 0; i --) {
    if (bag.buffer[i].jenis != 'P') {
      printf("<%c>: %c -> %c\n", bag.buffer[i].jenis, bag.buffer[i].start, bag.buffer[i].dest);
    } else {
      printf("<%c>: %c -> %c dengan sisa %d\n", bag.buffer[i].jenis, bag.buffer[i].start, bag.buffer[i].dest, bag.buffer[i].sisa_waktu);
    }
  }
}

void printListBangunan(ListDin l) {
  /* For debugging purposes only */
  printf("=== LIST BANGUNAN ===\n");
  for (int i = 0; LD_isIdxEff(l, i); i ++) {
    Bangunan b = LD_ELMT(l, i);
    printf("%c: (%d, %d)\n", b.locName, Absis(b.locCoords), Ordinat(b.locCoords));
  }
}

void printLogo() {
  printf("  __  __       _     _ _        \n");
  printf(" |  \\/  |     | |   (_) |       \n");
  printf(" | \\  / | ___ | |__  _| |_ __   \n");
  printf(" | |\\/| |/ _ \\| '_ \\| | __/ _` |\n");
  printf(" | |  | | (_) | |_) | | || (_| |\n");
  printf(" |_|  |_|\\___/|_.__/|_|\\__\\__,_|\n");
  printf(" \\ \\ / / __|                    \n");
  printf("  \\ V /\\__ \\_                   \n");
  printf("  _\\_/_|___(_)  _  ____  __     \n");
  printf(" |  __ \\|  __ \\| |/ /  \\/  |    \n");
  printf(" | |__) | |__) | ' /| \\  / |    \n");
  printf(" |  ___/|  ___/|  < | |\\/| |    \n");
  printf(" | |    | |    | . \\| |  | |    \n");
  printf(" |_|    |_|    |_|\\_\\_|  |_|    \n");                                 
}

int main() {
  /* ===================== */
  /* STATE GAME            */
  /* ===================== */
  ListDin listBangunan;
  int mapX, mapY;               // ukuran matrix, x * y
  int hqX, hqY;                 // letak headquarters (x, y)
  int banyakLokasi;             // banyak lokasi
  Matrix adjMatrix;             // adjacency matrix
  Map map;                      // peta
  int banyakPesanan;            // banyak pesanan
  Queue quePesanan;             // urutan pesanan, dari konfigurasi
  TIME gameTime;                // waktu game
  int money;                    // uang mobita
  POINT HQ;                     // letak HQ
  POINT mobitaLoc;              // lokasi Mobita
  List toDoList;                // to-do list
  List inProgressList;          // in-progress list
  int bag_capacity;             // kapasitas bag
  Stack bag;                    // bag
  ListPos inventory;            // inventory
  int hvyItems;                 // banyaknya heavy item pada bag
  int speedboostCount;          // banyaknya lokasi yang bisa dilalui dengan speedboost
  int VIPItemCount;             // banyak VIP item
  boolean returnToSender;       // ability return to sender
  int kecilCount;               // jumlah heavy item yang dikecilkan
  int deliveredCount;           // banyak item yang berhasil diantar
  /* Bagian inisialisasi game */
  LD_CreateListDin(&listBangunan, 30);
  CreateTime(&gameTime);
  money = 15000;
  bag_capacity = 3;
  LL_CreateList(&toDoList);
  LL_CreateList(&inProgressList);
  ST_CreateStack(&bag);
  CreateListPos(&inventory);
  hvyItems = 0;
  speedboostCount = 0;
  VIPItemCount = 0;
  returnToSender = false;
  kecilCount = 0;
  deliveredCount = 0;
  /* ===================== */
  /* MAIN MENU             */
  /* ===================== */
  printLogo();
  printf("===== MAIN MENU =====\n");
  printf("Command yang diterima:\n");
  printf(">> NEW GAME\n>> EXIT\n>> LOAD GAME\n");
  /* Mulai baca word */
  boolean isInMainMenu = true;
  boolean end = false;
  printf("ENTER COMMAND: ");
  startWord();
  while (isInMainMenu) {
    if (isWordEqual(currentWord, "NEW GAME")) {
      printf("Masukkan nama file konfigurasi: ");
      advWord();
      startLine(currentWord.contents);
      while (endLine) {
        printf("[!] File konfigurasi tidak ditemukan!\n");
        printf("Masukkan nama file konfigurasi: ");
        advWord();
        startLine(currentWord.contents);
      }
      // File sudah ditemukan.
      printf("File konfigurasi ditemukan!\n");
      printf("Loading konfigurasi...\n");
      // Load besar map.
      mapX = fWordToInt(currentLine.contents[0]);
      mapY = fWordToInt(currentLine.contents[1]);
      // Load koordinat headquarters.
      advLine();
      hqX = fWordToInt(currentLine.contents[0]);
      hqY = fWordToInt(currentLine.contents[1]);
      Bangunan hq = LD_CreateBangunan('8', hqX, hqY);
      LD_insertLast(&listBangunan, hq);
      HQ = MakePOINT(hqX, hqY);
      mobitaLoc = MakePOINT(hqX, hqY);
      // Load jumlah lokasi.
      advLine();
      banyakLokasi = fWordToInt(currentLine.contents[0]);
      // Input masing-masing lokasi.
      for (int i = 0; i < banyakLokasi; i ++) {
        advLine();
        char locName = currentLine.contents[0].contents[0];
        int x, y;
        x = fWordToInt(currentLine.contents[1]);
        y = fWordToInt(currentLine.contents[2]);
        Bangunan inputLoc = LD_CreateBangunan(locName, x, y);
        LD_insertLast(&listBangunan, inputLoc);
      }
      // Dari list bangunan, inisialisasi adjMatrix.
      CreateMatrix(banyakLokasi + 1, banyakLokasi + 1, &adjMatrix);
      for (int i = 0; i < banyakLokasi + 1; i ++) {
        advLine();
        for (int j = 0; j < currentLine.length; j ++) {
          ELMT(adjMatrix, i, j) = fWordToInt(currentLine.contents[j]);
        }
      }
      // Buat peta!
      CreateMap(mapX, mapY, listBangunan, adjMatrix, &map);
      // Baca jumlah pesanan.
      advLine();
      banyakPesanan = fWordToInt(currentLine.contents[0]);
      Q_CreateQueue(&quePesanan);
      for (int i = 0; i < banyakPesanan; i ++) {
        advLine();
        Item newItem;
        int argCount = currentLine.length;
        int entryTime = fWordToInt(currentLine.contents[0]);
        char startLoc = currentLine.contents[1].contents[0];
        char destLoc = currentLine.contents[2].contents[0];
        char itemType = currentLine.contents[3].contents[0];
        if (argCount == 4) {
          CreateItem(&newItem, entryTime, startLoc, destLoc, itemType);
        } else {
          CreatePerishableItem(&newItem, entryTime, startLoc, destLoc, fWordToInt(currentLine.contents[4]));
        }
        Q_enqueue(&quePesanan, newItem);
      }
      isInMainMenu = false;
    } else if (isWordEqual(currentWord, "EXIT")) {
      printf("Anda memilih untuk keluar dari game.\n");
      end = true;
      isInMainMenu = false;
    } else if (isWordEqual(currentWord, "LOAD GAME")) {
      printf("Masukkan nama file save: ");
      advWord();
      startLine(currentWord.contents);
      while (endLine) {
        printf("[!] File save tidak ditemukan!\n");
        printf("Masukkan nama file save: ");
        advWord();
        startLine(currentWord.contents);
      }
      printf("File save ditemukan!\n");
      printf("Loading save...\n");
      /* BACA BANGUNAN */
      banyakLokasi = fWordToInt(currentLine.contents[0]);
      for (int i = 0; i < banyakLokasi; i ++) {
        advLine();
        Bangunan b = LD_CreateBangunan(currentLine.contents[0].contents[0], fWordToInt(currentLine.contents[1]), fWordToInt(currentLine.contents[2]));
        LD_insertLast(&listBangunan, b);
      }
      /* BACA UKURAN MAP */
      advLine();
      mapX = fWordToInt(currentLine.contents[0]);
      mapY = fWordToInt(currentLine.contents[1]);
      /* BACA LOKASI HEADQUARTERS */
      advLine();
      hqX = fWordToInt(currentLine.contents[0]);
      hqY = fWordToInt(currentLine.contents[1]);
      HQ = MakePOINT(hqX, hqY);
      /* BACA ADJACENCY MATRIX */
      CreateMatrix(banyakLokasi, banyakLokasi, &adjMatrix);
      for (int i = 0; i < banyakLokasi; i ++) {
        advLine();
        for (int j = 0; j < currentLine.length; j ++) {
          ELMT(adjMatrix, i, j) = fWordToInt(currentLine.contents[j]);
        }
      }
      CreateMap(mapX, mapY, listBangunan, adjMatrix, &map);
      /* BACA QUEUE PESANAN */
      Q_CreateQueue(&quePesanan);
      advLine();
      banyakPesanan = fWordToInt(currentLine.contents[0]);
      for (int i = 0; i < banyakPesanan; i ++) {
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
        Item it; CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
        Q_enqueue(&quePesanan, it);
      }
      /* BACA TIME */
      advLine();
      Time(gameTime) = fWordToInt(currentLine.contents[0]);
      /* BACA MONEY */
      advLine();
      money = fWordToInt(currentLine.contents[0]);
      /* BACA LOKASI MOBITA */
      advLine();
      mobitaLoc = MakePOINT(fWordToInt(currentLine.contents[0]), fWordToInt(currentLine.contents[1]));
      /* BACA TO DO LIST */
      advLine();
      int toDoCount = fWordToInt(currentLine.contents[0]);
      for (int i = 0; i < toDoCount; i ++) {
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
        Item it; CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
        LL_insertLast(&toDoList, it);
      }
      /* BACA IN PROGRESS LIST */
      advLine();
      int inProgressCount = fWordToInt(currentLine.contents[0]);
      for (int i = 0; i < inProgressCount; i ++) {
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
        Item it; CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
        LL_insertLast(&inProgressList, it);
      }
      /* BACA BAG CAPACITY */
      advLine();
      bag_capacity = fWordToInt(currentLine.contents[0]);
      /* BACA BAG */
      advLine();
      int banyakBag = fWordToInt(currentLine.contents[0]);
      for (int i = 0; i < banyakBag; i ++) {
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
        Item it; CreateItemFull(&it, masuk, nilai, hangus, sisa_waktu, start, dest, jenis, isKecil);
        ST_push(&bag, it);
      }
      /* BACA INVENTORY */
      advLine();
      LP_ELMT(inventory, 0) = fWordToInt(currentLine.contents[0]);
      LP_ELMT(inventory, 1) = fWordToInt(currentLine.contents[1]);
      LP_ELMT(inventory, 2) = fWordToInt(currentLine.contents[2]);
      LP_ELMT(inventory, 3) = fWordToInt(currentLine.contents[3]);
      LP_ELMT(inventory, 4) = fWordToInt(currentLine.contents[4]);
      /* BACA hvyItems */
      advLine();
      hvyItems = fWordToInt(currentLine.contents[0]);
      /* BACA speedboostCount */
      advLine();
      speedboostCount = fWordToInt(currentLine.contents[0]);
      /* BACA VIPItemCount */
      advLine();
      VIPItemCount = fWordToInt(currentLine.contents[0]);
      /* BACA returnToSender */
      advLine();
      returnToSender = fWordToInt(currentLine.contents[0]);
      /* BACA kecilCount */
      advLine();
      kecilCount = fWordToInt(currentLine.contents[0]);
      /* BACA deliveredCount */
      advLine();
      deliveredCount = fWordToInt(currentLine.contents[0]);
      isInMainMenu = false;
    } else {
      printf("[!] Command Anda tidak dikenali. Silakan ulangi.\n");
      printf("ENTER COMMAND: ");
      advWord();
    }
  }
  /* Game! */
  while (!end) {
    if (Q_isEmpty(quePesanan) && LL_isEmpty(toDoList) && LL_isEmpty(inProgressList)) {
      if (NEQ(mobitaLoc, HQ)) {
        printf("[!] Tidak ada pesanan lagi yang bisa diantarkan. Kembali ke headquarters!\n");
      } else {
        printf("======================================================================\n");
        printf("Permainan selesai!\n");
        printf("Mobita berhasil mengantarkan %d pesanan dengan penunjuk in-game time akhir %d.\n", deliveredCount, Time(gameTime));
        end = true;
        break;
      }
    }
    /* Memasukkan pesanan yang sudah waktunya masuk ke to-do list. */
    while (!Q_isEmpty(quePesanan) && Q_HEAD(quePesanan).masuk <= Time(gameTime)) {
      Item poppedItem;
      Q_dequeue(&quePesanan, &poppedItem);
      if (poppedItem.jenis == 'V') {
        VIPItemCount ++;
        printf("[!] VIP item masuk ke dalam TO_DO! Mobita tidak bisa pick-up item lain.\n");
        LL_insertFirst(&toDoList, poppedItem);
      } else {
        LL_insertLast(&toDoList, poppedItem);
      }
    }
    /* Tunjukkan state game */
    showState(mobitaLoc, listBangunan, gameTime, money, toDoList, inProgressList);
    for (;;) {
      printf("ENTER COMMAND: ");
      advWord();
      if ((isWordEqual(currentWord, "MOVE")) || (isWordEqual(currentWord, "PICK_UP")) || (isWordEqual(currentWord, "DROP_OFF")) || (isWordEqual(currentWord, "MAP")) || (isWordEqual(currentWord, "TO_DO")) || (isWordEqual(currentWord, "IN_PROGRESS")) || (isWordEqual(currentWord, "BUY")) || (isWordEqual(currentWord, "INVENTORY")) || (isWordEqual(currentWord, "HELP")) || (isWordEqual(currentWord, "RETURN")) || (isWordEqual(currentWord, "SAVE_GAME"))) {
        break;
      } else {
        printf("[!] Command tidak valid. Ketik HELP untuk melihat command valid.\n");
      }
    }
    if (isWordEqual(currentWord, "MAP")) {
      displayMap(map, listBangunan, toDoList, inProgressList, mobitaLoc);
    } else if (isWordEqual(currentWord, "TO_DO")) {
      displayToDo(toDoList);
    } else if (isWordEqual(currentWord, "IN_PROGRESS")) {
      displayInProgress(inProgressList);
    } else if (isWordEqual(currentWord, "MOVE")) {
      printf("Posisi yang dapat dicapai:\n");
      adjacentLocations lokasiTujuan = getAdjacentLocations(mobitaLoc, listBangunan, map);
      for (int j = 0; j < lokasiTujuan.length; j ++) {
        Bangunan bangunanAdj = LD_ELMT(listBangunan, lokasiTujuan.buffer[j]);
        printf("%d. %c (%d,%d)\n", j + 1, bangunanAdj.locName, Absis(bangunanAdj.locCoords), Ordinat(bangunanAdj.locCoords));
      }
      printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
      printf("ENTER COMMAND: ");
      advWord();
      int pilihan = wordToInt(currentWord);
      if (pilihan == 0) {
        printf("Anda memilih untuk kembali.\n");
      } else if (pilihan < 0 || pilihan > lokasiTujuan.length) {
        printf("[!] Input Anda tidak sesuai.\n");
      } else {
        int idxBangunan = lokasiTujuan.buffer[pilihan - 1];
        Bangunan bangunan = LD_ELMT(listBangunan, idxBangunan);
        Absis(mobitaLoc) = Absis(bangunan.locCoords);
        Ordinat(mobitaLoc) = Ordinat(bangunan.locCoords);
        printf("Mobita sekarang berada di titik %c (%d,%d)!\n", bangunan.locName, Absis(mobitaLoc), Ordinat(mobitaLoc));
        if (speedboostCount > 0) {
          printf("[!] Bergerak dengan speedboost!\n");
          speedboostCount --;
          if (speedboostCount % 2 == 0) {
            increaseTime(&gameTime, 1);
            updatePerishables(&inProgressList, &bag, 1);
          }
          if (speedboostCount == 0) {
            printf("[!] Speedboost Mobita telah habis.\n");
          }
        } else {
          increaseTime(&gameTime, 1 + hvyItems - kecilCount);
          updatePerishables(&inProgressList, &bag, 1 + hvyItems - kecilCount);
          if (hvyItems - kecilCount > 0) {
            printf("[!] Terdapat tambahan %d waktu karena Mobita mengangkut Heavy Item.\n", hvyItems - kecilCount);
          }
        }
      } 
    } else if (isWordEqual(currentWord, "PICK_UP")) {
      // Cek apakah ada pesanan di toDoList
      boolean found = false;
      int idx = 0;
      Address p = LL_FIRST(toDoList);
      while (p != NULL && !found) {
        if (NODE_INFO(p).start == getLocationName(mobitaLoc, listBangunan)) {
          found = true;
        } else {
          p = NODE_NEXT(p);
          idx ++;
        }
      }
      if (found) {
        if (VIPItemCount > 0 && NODE_INFO(p).jenis != 'V') {
          printf("[!] Mobita tidak bisa mengambil pick up dari lokasi ini karena perlu mengantar VIP Item terlebih dahulu.\n");
        } else {
          // Ada toDoList yang sesuai dengan lokasi sekarang
          if (ST_IDX_TOP(bag) == bag_capacity - 1) {
            // Bag penuh.
            printf("Kapasitas tas penuh.\n");
          } else {
            // Bag tidak penuh.
            Item item = NODE_INFO(p);
            switch(item.jenis) {
              case 'N':
                printf("Pesanan berupa Normal Item berhasil diambil!\n");
                break;
              case 'H':
                printf("Pesanan berupa Heavy Item berhasil diambil!\n");
                hvyItems ++;
                printf("[!] Mobita sedang mengangkut %d buah Heavy Item(s).\n", hvyItems);
                if (speedboostCount > 0) {
                  printf("[!] Speedboost dinonaktifkan karena mengangkut Heavy Item.\n");
                  speedboostCount = 0;
                }
                break;
              case 'P':
                printf("Pesanan berupa Perishable Item berhasil diambil!\n");
                printf("[!] Pantau durasi yang Mobita punya melalui command IN_PROGRESS.\n");
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
          }
        }
      } else {
        printf("[!] Pesanan tidak ditemukan!\n");
      }
    } else if (isWordEqual(currentWord, "DROP_OFF")) {
      if (LL_isEmpty(inProgressList)) {
        printf("[!] Tidak ada pesanan yang dapat diantarkan!\n");
      } else {
        Item item = ST_TOP(bag);
        if (item.dest == getLocationName(mobitaLoc, listBangunan)) { // Lokasi benar!
          int prize;
          switch (item.jenis) {
            case 'N':
              printf("Pesanan Normal Item berhasil diantarkan.\n");
              prize = 200;
              break;
            case 'H':
              printf("Pesanan Heavy Item berhasil diantarkan.\n");
              hvyItems --;
              if (item.isKecil == true) {
                kecilCount --;
              }
              if (hvyItems - kecilCount == 0) {
                // Aktivasi speedboost
                speedboostCount = 10;
                printf("Speedboost teraktivasi!\n");
              }
              prize = 400;
              break;
            case 'P':
              printf("Pesanan Perishable Item berhasil diantarkan.\n");
              bag_capacity ++;
              printf("[!] Capacity bag Mobita bertambah 1 menjadi %d!\n", bag_capacity);
              prize = 400;
              break;
            case 'V':
              printf("Pesanan VIP Item berhasil diantarkan.\n");
              VIPItemCount --;
              if (!returnToSender) {
                printf("[!] Mobita mendapatkan ability Return to Sender!\n");
                returnToSender = true;
              }
              if (VIPItemCount == 0) {
                printf("[!] Semua pesanan VIP telah diantarkan!\n");
              }
              prize = 600;
              break;
          }
          money += prize;
          deliveredCount ++;
          printf("Uang yang didapatkan: %d Yen\n", prize);
          // Hapus dari inProgressList dan bag.
          Item tmp;
          LL_deleteFirst(&inProgressList, &tmp);
          ST_pop(&bag, &tmp);
        } else { // Lokasi salah.
          printf("Tidak ada pesanan yang dapat diantarkan!\n");
        }
      }
    } else if (isWordEqual(currentWord, "HELP")) {
      printf("1. MOVE -> Untuk berpindah ke lokasi selanjutnya\n");
      printf("2. PICK_UP -> Untuk mengambil item di lokasi sekarang\n");
      printf("3. DROP_OFF -> Untuk mengantarkan item ke lokasi sekarang\n");
      printf("4. MAP -> Untuk memunculkan peta\n");
      printf("5. TO_DO -> Untuk menampilkan pesanan yang masuk ke To Do List\n");
      printf("6. IN_PROGRESS -> Untuk menampilkan pesanan yang sedang dikerjakan\n");
      printf("7. BUY -> Untuk menampilkan gadget yang dapat dibeli dan membelinya\n");
      printf("8. INVENTORY -> Untuk melihat gadget yang dimiliki dan menggunakannya\n");
      printf("9. HELP -> Untuk mengeluarkan list command dan kegunaannya\n");
      printf("10. RETURN -> Mengembalikan barang teratas di tas apabila memiliki ability return to sender.\n");
      printf("11. SAVE_GAME -> Menyimpan state game sekarang agar nanti bisa di-load.\n");
    } else if (isWordEqual(currentWord, "INVENTORY")) {
      showInventory(inventory);
      printf("Gadget mana yang ingin digunakan? (Ketik 0 jika ingin kembali)\n\n");
      printf("ENTER COMMAND: ");
      advWord();
      int invIdx = wordToInt(currentWord) - 1;
      if (LP_ELMT(inventory, invIdx) == LP_VAL_UNDEF || invIdx < 0 || invIdx > 4) {
        printf("Tidak ada Gadget yang dapat digunakan!\n");
      } else {
        if (LP_ELMT(inventory, invIdx) == 1) {
          printf("Kain Pembungkus Waktu berhasil digunakan!\n");
          // Update inProgressList
          Address p = LL_FIRST(inProgressList);
          boolean foundPerishable = false;
          while (p != NULL && !foundPerishable) {
            if (NODE_INFO(p).jenis == 'P') {
              printf("[!] Mengembalikan durasi perishable (%c -> %c) ke durasi semula.\n", NODE_INFO(p).start, NODE_INFO(p).dest);
              NODE_INFO(p).sisa_waktu = NODE_INFO(p).hangus;
              foundPerishable = true;
            } else {
              p = NODE_NEXT(p);
            }
          }
          // Update stack
          if (foundPerishable) {
            for (int i = ST_IDX_TOP(bag); i >= 0; i ++) {
              if (bag.buffer[i].jenis == 'P') {
                bag.buffer[i].sisa_waktu = bag.buffer[i].hangus;
                break;
              }
            }
          } else {
            printf("[!] Gadget digunakan, tapi tidak ditemukan perishable item pada tas.\n");
          }
        } else if (LP_ELMT(inventory, invIdx) == 2) {
          printf("Senter Pembesar berhasil digunakan!\n");
          bag_capacity *= 2;
          if (bag_capacity > 100) {
            bag_capacity = 100;
          }
          printf("[!] Kapasitas tas Mobita sekarang adalah %d.\n", bag_capacity);
        } else if (LP_ELMT(inventory, invIdx) == 3) {
          printf("Pintu Kemana Saja berhasil digunakan!\n");
          boolean foundLoc = false;
          POINT to;
          char toChar;
          while (!foundLoc) {
            printf("Masukkan lokasi (misal A): ");
            advWord();
            char loc = currentWord.contents[0];
            for (int i = 0; i < listBangunan.nEff; i ++) {
              if (listBangunan.buffer[i].locName == loc) {
                foundLoc = true;
                to = listBangunan.buffer[i].locCoords;
                toChar = loc;
                break;
              }
            }
            if (!foundLoc) {
              printf("[!] Lokasi tersebut tidak ditemukan. Silakan coba lokasi lain.\n");
            }
          }
          mobitaLoc = to;
          printf("[!] Mobita sekarang berada di lokasi %c (%d, %d).\n", toChar, Absis(to), Ordinat(to));
        } else if (LP_ELMT(inventory, invIdx) == 4) {
          printf("Mesin Waktu berhasil digunakan!\n");
          Time(gameTime) -= 50;
          if (Time(gameTime) < 0) {
            Time(gameTime) = 0;
          }
          printf("[!] Waktu Mobita sekarang adalah %d.\n", Time(gameTime));
        } else if (LP_ELMT(inventory, invIdx) == 5) {
          printf("Senter Pengecil berhasil digunakan!\n");
          if (ST_TOP(bag).jenis != 'H') {
            printf("[!] Gadget digunakan, tapi tumpukan teratas dari tas bukanlah Heavy Item.\n");
          } else {
            if (ST_TOP(bag).isKecil == true) {
              printf("[!] Gadget digunakan, tapi tumpukan teratas tas sudah dalam kondisi dikecilkan.\n");
            } else {
              kecilCount ++;
              ST_TOP(bag).isKecil = true;
              NODE_INFO(inProgressList).isKecil = true;
              printf("[!] Berhasil memberikan efek senter pengecil untuk Heavy Item (%c -> %c)!\n", ST_TOP(bag).start, ST_TOP(bag).dest);
            }
          }
        }
        LP_ELMT(inventory, invIdx) = LP_VAL_UNDEF;
      }
    } else if (isWordEqual(currentWord, "BUY")) {
      if (EQ(mobitaLoc, HQ)) {
        if (getEmptySlot(inventory) == LP_CAPACITY) {
          printf("Inventory Mobita sudah penuh!\n");
        } else {
          printf("Uang Mobita sekarang: %d Yen\n", money);
          printf("Gadget yang tersedia:\n");
          printf("1. Kain Pembungkus Waktu (800 Yen)\n");
          printf("2. Senter Pembesar (1200 Yen)\n");
          printf("3. Pintu Kemana Saja (1500 Yen)\n");
          printf("4. Mesin Waktu (3000 Yen)\n");
          printf("5. Senter Pengecil (800 Yen)\n");
          printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n\n");
          printf("ENTER COMMAND: ");
          advWord();
          int gadget = wordToInt(currentWord);
          if (gadget < 1 || gadget > 5) {
            printf("Nomor gadget tidak valid.\n");
          } else {
            int gadgetPrice;
            switch(gadget) {
              case 1:
                gadgetPrice = 800;
                break;
              case 2: 
                gadgetPrice = 1200;
                break;
              case 3:
                gadgetPrice = 1500;
                break;
              case 4:
                gadgetPrice = 3000;
                break;
              case 5:
                gadgetPrice = 800;
                break;
            }
            if (money < gadgetPrice) {
              printf("Uang tidak cukup untuk membeli gadget!\n");
            } else {
              switch(gadget) {
                case 1:
                  printf("Kain Pembungkus Waktu berhasil dibeli!\n");
                  break;
                case 2:
                  printf("Senter Pembesar berhasil dibeli!\n");
                  break;
                case 3:
                  printf("Pintu Kemana Saja berhasil dibeli!\n");
                  break;
                case 4:
                  printf("Mesin Waktu berhasil dibeli!\n");
                  break;
                case 5:
                  printf("Senter Pengecil berhasil dibeli!\n");
                  break;
              }
              money -= gadgetPrice;
              addToInventory(&inventory, gadget);
              printf("Uang Mobita sekarang: %d Yen\n", money);
            }
          }
        }
      } else {
        printf("Mobita harus berada di HQ untuk bisa melakukan command BUY!\n");
      }
    } else if (isWordEqual(currentWord, "RETURN")) {
      if (!returnToSender) {
        printf("[!] Mobita tidak memiliki ability return to sender!\n");
      } else {
        if (LL_isEmpty(inProgressList)) {
          printf("[!] Mobita tidak memiliki barang yang bisa dikembalikan!\n");
        } else {
          Item tmp = ST_TOP(bag);
          if (tmp.jenis == 'V') {
            printf("[!] Mobita tidak bisa mengembalikan VIP item!\n");
          } else {
            // Jika perishable, reset waktunya.
            if (tmp.jenis == 'P') {
              tmp.sisa_waktu = tmp.hangus;
            }
            if (tmp.jenis == 'H') {
              hvyItems --;
              if (tmp.isKecil == true) {
                tmp.isKecil = false;
                kecilCount --;
              }
            }
            Item unused;
            LL_deleteFirst(&inProgressList, &unused);
            ST_pop(&bag, &unused);
            LL_insertLast(&toDoList, tmp);
            printf("Ability return to sender berhasil!\n");
            printf("[!] Item jenis %c (%c -> %c) berhasil dikembalikan.\n", tmp.jenis, tmp.start, tmp.dest);
          }
        }
      } 
    } else if (isWordEqual(currentWord, "SAVE_GAME")) {
      // Simpan pada file.
      printf("Masukkan nama file penyimpanan (contoh: save.txt): ");
      advWord();
      FILE* fpointer = fopen(currentWord.contents, "w");
      // Banyak bangunan
      fprintf(fpointer, "%d\n", listBangunan.nEff);
      // Bangunannya
      for (int i = 0; i < listBangunan.nEff; i ++) {
        Bangunan b = listBangunan.buffer[i];
        fprintf(fpointer, "%c %d %d\n", b.locName, Absis(b.locCoords), Ordinat(b.locCoords));
      }
      // Ukuran map
      fprintf(fpointer, "%d %d\n", mapX, mapY);
      // Lokasi HQ
      fprintf(fpointer, "%d %d\n", Absis(HQ), Ordinat(HQ));
      // Adjacency matrix
      for (int i = 0; i <= getLastIdxRow(adjMatrix); i ++) {
        for (int j = 0; j <= getLastIdxCol(adjMatrix); j ++) {
          if (j != getLastIdxCol(adjMatrix)) {
            fprintf(fpointer, "%d ", adjMatrix.contents[i][j]);
          } else {
            fprintf(fpointer, "%d\n", adjMatrix.contents[i][j]);
          }
        }
      }
      // Queue Pesanan
      fprintf(fpointer, "%d\n", Q_length(quePesanan));
      if (!Q_isEmpty(quePesanan)) {
        for (int i = Q_IDX_HEAD(quePesanan); i <= Q_IDX_TAIL(quePesanan); i ++) {
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
      while (p != NULL) {
        Item it = NODE_INFO(p);
        fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
        p = NODE_NEXT(p);
      }
      // In-progress List
      fprintf(fpointer, "%d\n", LL_length(inProgressList));
      p = LL_FIRST(inProgressList);
      while (p != NULL) {
        Item it = NODE_INFO(p);
        fprintf(fpointer, "%d %d %d %d %c %c %c %d\n", it.masuk, it.nilai, it.hangus, it.sisa_waktu, it.start, it.dest, it.jenis, it.isKecil);
        p = NODE_NEXT(p);
      }
      // Bag capacity
      fprintf(fpointer, "%d\n", bag_capacity);
      // Bag
      fprintf(fpointer, "%d\n", ST_IDX_TOP(bag) + 1);
      for (int i = 0; i <= ST_IDX_TOP(bag); i ++) {
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
    }
  }
  return 0;
}