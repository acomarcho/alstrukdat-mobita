#include "other.h"

void cetakBag(Stack bag)
{
  /* For debugging purposes only */
  for (int i = bag.idxTop; i >= 0; i--)
  {
    if (bag.buffer[i].jenis != 'P')
    {
      printf("<%c>: %c -> %c\n", bag.buffer[i].jenis, bag.buffer[i].start, bag.buffer[i].dest);
    }
    else
    {
      printf("<%c>: %c -> %c dengan sisa %d\n", bag.buffer[i].jenis, bag.buffer[i].start, bag.buffer[i].dest, bag.buffer[i].sisa_waktu);
    }
  }
}

void printListBangunan(ListDin l)
{
  /* For debugging purposes only */
  printf("=== LIST BANGUNAN ===\n");
  for (int i = 0; LD_isIdxEff(l, i); i++)
  {
    Bangunan b = LD_ELMT(l, i);
    printf("%c: (%d, %d)\n", b.locName, Absis(b.locCoords), Ordinat(b.locCoords));
  }
}

void printLogo()
{
  printf("*****************************************\n");
  printf("||*************************************||\n");
  printf("||     __  __       _     _ _          ||\n");
  printf("||    |  \\/  |     | |   (_) |         ||\n");
  printf("||    | \\  / | ___ | |__  _| |_ __     ||\n");
  printf("||    | |\\/| |/ _ \\| '_ \\| | __/ _` |  ||\n");
  printf("||    | |  | | (_) | |_) | | || (_| |  ||\n");
  printf("||    |_|  |_|\\___/|_.__/|_|\\__\\__,_|  ||\n");
  printf("||    \\ \\ / / __|                      ||\n");
  printf("||     \\ V /\\__ \\_                     ||\n");
  printf("||     _\\_/_|___(_)  _  ____  __       ||\n");
  printf("||    |  __ \\|  __ \\| |/ /  \\/  |      ||\n");
  printf("||    | |__) | |__) | ' /| \\  / |      ||\n");
  printf("||    |  ___/|  ___/|  < | |\\/| |      ||\n");
  printf("||    | |    | |    | . \\| |  | |      ||\n");
  printf("||    |_|    |_|    |_|\\_\\_|  |_|      ||\n");
  printf("||                                     ||\n");
  printf("||*************************************||\n");
  printf("*****************************************\n");
}

void printMainMenu() {
  printf("[]============= MAIN MENU =============[]\n");
  printf("||                                     ||\n");
  printf("||         Command yang diterima:      ||\n");
  printf("||         >> NEW GAME                 ||\n");
  printf("||         >> EXIT                     ||\n");
  printf("||         >> LOAD GAME                ||\n");
  printf("||                                     ||\n");
  printf("[]*************************************[]\n");
  printf("*****************************************\n");
}