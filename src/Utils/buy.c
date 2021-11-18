#include "buy.h"

void buy(POINT mobitaLoc, POINT HQ, ListPos* inventory, int* money) {
  /* Implementasi command BUY */
  if (EQ(mobitaLoc, HQ))
  {
    if (getEmptySlot(*inventory) == LP_CAPACITY)
    {
      printf("Inventory Mobita sudah penuh!\n");
    }
    else
    {
      printf("Uang Mobita sekarang: %d Yen\n", *money);
      printf("Gadget yang tersedia:\n");
      printf("1. Kain Pembungkus Waktu (800 Yen)\n");
      printf("2. Senter Pembesar (1200 Yen)\n");
      printf("3. Pintu Kemana Saja (1500 Yen)\n");
      printf("4. Mesin Waktu (3000 Yen)\n");
      printf("5. Senter Pengecil (800 Yen)\n");
      printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n\n");
      printf("        ENTER COMMAND: ");
      advWord();
      printf("\n");
      int gadget = wordToInt(currentWord);
      while (gadget < 0 || gadget > 5 ){
        printf("Nomor gadget tidak valid.\n");
        buy(mobitaLoc, HQ, inventory, money);
        return;
      }
      if (gadget == 0)
      {
        printf("Anda memilih untuk kembali.\n");
      }
      else
      {
        int gadgetPrice;
        switch (gadget)
        {
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
        if (*money < gadgetPrice)
        {
          printf("Uang tidak cukup untuk membeli gadget!\n");
        }
        else
        {
          switch (gadget)
          {
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
          *money -= gadgetPrice;
          addToInventory(inventory, gadget);
          printf("Uang Mobita sekarang: %d Yen\n", *money);
        }
      }
    }
  }
  else
  {
    printf("Mobita harus berada di HQ untuk bisa melakukan command BUY!\n");
  }
}