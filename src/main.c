/* ADT, standard library */
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

/* Utils */
#include "Utils/showState.h"
#include "Utils/updatePerishables.h"
#include "Utils/initializeGame.h"
#include "Utils/newGame.h"
#include "Utils/loadGame.h"
#include "Utils/move.h"
#include "Utils/handleToDo.h"
#include "Utils/showHelp.h"
#include "Utils/pickup.h"
#include "Utils/dropoff.h"
#include "Utils/inventory.h"
#include "Utils/buy.h"
#include "Utils/returnToSender.h"
#include "Utils/saveGame.h"
#include "Utils/other.h"
#include "Utils/updateSenterPengecil.h"

// gcc -o main main.c FileMachine/filemachine.c WordMachine/wordmachine.c WordMachine/charmachine.c Item/item.c LinkedList/list_linked.c LinkedList/node.c Listdin/listdin.c Map/map.c Matrix/matrix.c PColor/pcolor.c Point/point.c Queue/queue.c Time/time.c Stack/stack.c ListPos/listpos.c Utils/showState.c Utils/updatePerishables.c Utils/initializeGame.c Utils/newGame.c Utils/loadGame.c Utils/move.c Utils/handleToDo.c Utils/showHelp.c Utils/pickup.c Utils/dropoff.c Utils/inventory.c Utils/buy.c Utils/returnToSender.c Utils/saveGame.c Utils/other.c Utils/updateSenterPengecil.c

int main()
{
  /* ===================== */
  /* STATE GAME            */
  /* ===================== */
  ListDin listBangunan;
  int mapX, mapY;         // ukuran matrix, x * y
  int hqX, hqY;           // letak headquarters (x, y)
  int banyakLokasi;       // banyak lokasi
  Matrix adjMatrix;       // adjacency matrix
  Map map;                // peta
  int banyakPesanan;      // banyak pesanan
  Queue quePesanan;       // urutan pesanan, dari konfigurasi
  TIME gameTime;          // waktu game
  int money;              // uang mobita
  POINT HQ;               // letak HQ
  POINT mobitaLoc;        // lokasi Mobita
  List toDoList;          // to-do list
  List inProgressList;    // in-progress list
  int bag_capacity;       // kapasitas bag
  Stack bag;              // bag
  ListPos inventory;      // inventory
  int hvyItems;           // banyaknya heavy item pada bag
  int speedboostCount;    // banyaknya lokasi yang bisa dilalui dengan speedboost
  int VIPItemCount;       // banyak VIP item
  boolean returnToSender; // ability return to sender
  int kecilCount;         // jumlah heavy item yang dikecilkan
  int deliveredCount;     // banyak item yang berhasil diantar
  /* Bagian inisialisasi game */
  initializeGame(&listBangunan, &gameTime, &money, &bag_capacity, &toDoList, &inProgressList, &bag, &inventory, &hvyItems, &speedboostCount, &VIPItemCount, &returnToSender, &kecilCount, &deliveredCount);
  /* ===================== */
  /* MAIN MENU             */
  /* ===================== */
  printLogo();
  printMainMenu();
  /* Mulai baca word */
  boolean isInMainMenu = true;
  boolean end = false;
  printf("\n");
  printf("        ENTER COMMAND: ");
  startWord();
  printf("\n");
  while (isInMainMenu)
  {
    if (isWordEqual(currentWord, "NEW GAME"))
    {
      newGame(&mapX, &mapY, &hqX, &hqY, &listBangunan, &HQ, &mobitaLoc, &banyakLokasi, &adjMatrix, &map, &banyakPesanan, &quePesanan);
      isInMainMenu = false;
    }
    else if (isWordEqual(currentWord, "EXIT"))
    {
      printf("Anda memilih untuk keluar dari game.\n");
      end = true;
      isInMainMenu = false;
    }
    else if (isWordEqual(currentWord, "LOAD GAME"))
    {
      loadGame(&banyakLokasi, &listBangunan, &mapX, &mapY, &hqX, &hqY, &HQ, &adjMatrix, &map, &quePesanan, &banyakPesanan, &gameTime, &money, &mobitaLoc, &toDoList, &inProgressList, &bag_capacity, &bag, &inventory, &hvyItems, &speedboostCount, &VIPItemCount, &returnToSender, &kecilCount, &deliveredCount);
      isInMainMenu = false;
    }
    else
    {
      printf("[!] Command Anda tidak dikenali. Silakan ulangi.\n");
      printf("\n");
      printf("        ENTER COMMAND: ");
      advWord();
      printf("\n");
    }
  }
  /* Game! */
  while (!end)
  {
    /* Handle kondisi akhir (tidak ada yang bisa diantarkan lagi) */
    if (Q_isEmpty(quePesanan) && LL_isEmpty(toDoList) && LL_isEmpty(inProgressList))
    {
      if (NEQ(mobitaLoc, HQ))
      {
        printf("[!] Tidak ada pesanan lagi yang bisa diantarkan. Kembali ke headquarters!\n");
      }
      else
      {
        printf("======================================================================\n");
        printf("Permainan selesai!\n");
        printf("Mobita berhasil mengantarkan %d pesanan dengan penunjuk in-game time akhir %d.\n", deliveredCount, Time(gameTime));
        end = true;
        break;
      }
    }
    /* Memasukkan pesanan yang sudah waktunya masuk ke to-do list. */
    handleToDo(&quePesanan, gameTime, &VIPItemCount, &toDoList);
    /* Tunjukkan state game */
    showState(mobitaLoc, listBangunan, gameTime, money, toDoList, inProgressList);
    for (;;)
    {
      printf("\n");
      printf("        ENTER COMMAND: ");
      advWord();
      printf("\n");
      if ((isWordEqual(currentWord, "MOVE")) || (isWordEqual(currentWord, "PICK_UP")) || (isWordEqual(currentWord, "DROP_OFF")) || (isWordEqual(currentWord, "MAP")) || (isWordEqual(currentWord, "TO_DO")) || (isWordEqual(currentWord, "IN_PROGRESS")) || (isWordEqual(currentWord, "BUY")) || (isWordEqual(currentWord, "INVENTORY")) || (isWordEqual(currentWord, "HELP")) || (isWordEqual(currentWord, "RETURN")) || (isWordEqual(currentWord, "SAVE_GAME")))
      {
        break;
      }
      else
      {
        printf("[!] Command tidak valid. Ketik HELP untuk melihat command valid.\n");
      }
    }
    if (isWordEqual(currentWord, "MAP"))
    {
      displayMap(map, listBangunan, toDoList, inProgressList, mobitaLoc);
    }
    else if (isWordEqual(currentWord, "TO_DO"))
    {
      displayToDo(toDoList);
    }
    else if (isWordEqual(currentWord, "IN_PROGRESS"))
    {
      displayInProgress(inProgressList);
    }
    else if (isWordEqual(currentWord, "MOVE"))
    {
      move(&mobitaLoc, listBangunan, map, &speedboostCount, &gameTime, &inProgressList, &bag, hvyItems, kecilCount);
    }
    else if (isWordEqual(currentWord, "PICK_UP"))
    {
      pickup(&toDoList, mobitaLoc, listBangunan, VIPItemCount, &bag, bag_capacity, &hvyItems, &speedboostCount, &inProgressList);
    }
    else if (isWordEqual(currentWord, "DROP_OFF"))
    {
      dropoff(&inProgressList, &bag, mobitaLoc, listBangunan, &hvyItems, &kecilCount, &speedboostCount, &bag_capacity, &VIPItemCount, &returnToSender, &money, &deliveredCount);
    }
    else if (isWordEqual(currentWord, "HELP"))
    {
      showHelp();
    }
    else if (isWordEqual(currentWord, "INVENTORY"))
    {
      handleInventory(&inventory, &inProgressList, &bag, &bag_capacity, listBangunan, &mobitaLoc, &gameTime, &kecilCount);
    }
    else if (isWordEqual(currentWord, "BUY"))
    {
      buy(mobitaLoc, HQ, &inventory, &money);
    }
    else if (isWordEqual(currentWord, "RETURN"))
    {
      handleReturn(returnToSender, &inProgressList, &bag, &toDoList, &hvyItems, &kecilCount);
    }
    else if (isWordEqual(currentWord, "SAVE_GAME"))
    {
      saveGame(listBangunan, mapX, mapY, HQ, mobitaLoc, adjMatrix, quePesanan, gameTime, money, toDoList, inProgressList, bag_capacity, bag, inventory, hvyItems, speedboostCount, VIPItemCount, returnToSender, kecilCount, deliveredCount);
    }
  }
  return 0;
}
