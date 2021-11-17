#include "inventory.h"

void handleInventory(ListPos* inventory, List* inProgressList, Stack* bag, int* bag_capacity, ListDin listBangunan, POINT* mobitaLoc, TIME* gameTime, int* kecilCount) {
  /* Implementasi command inventory DAN implementasi gadget-gadget. */
  showInventory(*inventory);
  printf("Gadget mana yang ingin digunakan? (Ketik 0 jika ingin kembali)\n\n");
  printf("        ENTER COMMAND: ");
  advWord();
  printf("\n");
  int invIdx = wordToInt(currentWord) - 1;
  if (LP_ELMT(*inventory, invIdx) == LP_VAL_UNDEF || invIdx < 0 || invIdx > 4)
  {
    printf("Tidak ada Gadget yang dapat digunakan!\n");
  }
  else
  {
    /* === KAIN PEMBUNGKUS WAKTU === */
    if (LP_ELMT(*inventory, invIdx) == 1)
    {
      printf("Kain Pembungkus Waktu berhasil digunakan!\n");
      // Update inProgressList
      Address p = LL_FIRST(*inProgressList);
      boolean foundPerishable = false;
      while (p != NULL && !foundPerishable)
      {
        if (NODE_INFO(p).jenis == 'P')
        {
          printf("[!] Mengembalikan durasi perishable (%c -> %c) ke durasi semula.\n", NODE_INFO(p).start, NODE_INFO(p).dest);
          NODE_INFO(p).sisa_waktu = NODE_INFO(p).hangus;
          foundPerishable = true;
        }
        else
        {
          p = NODE_NEXT(p);
        }
      }
      // Update stack
      if (foundPerishable)
      {
        for (int i = ST_IDX_TOP(*bag); i >= 0; i++)
        {
          if ((*bag).buffer[i].jenis == 'P')
          {
            (*bag).buffer[i].sisa_waktu = (*bag).buffer[i].hangus;
            break;
          }
        }
      }
      else
      {
        printf("[!] Gadget digunakan, tapi tidak ditemukan perishable item pada tas.\n");
      }
    }
    /* === SENTER PEMBESAR === */
    else if (LP_ELMT(*inventory, invIdx) == 2)
    {
      printf("Senter Pembesar berhasil digunakan!\n");
      (*bag_capacity) *= 2;
      if (*bag_capacity > 100)
      {
        (*bag_capacity) = 100;
      }
      printf("[!] Kapasitas tas Mobita sekarang adalah %d.\n", *bag_capacity);
    }
    /* === PINTU KEMANA SAJA === */
    else if (LP_ELMT(* inventory, invIdx) == 3)
    {
      printf("Pintu Kemana Saja berhasil digunakan!\n");
      boolean foundLoc = false;
      POINT to;
      char toChar;
      while (!foundLoc)
      {
        printf("Masukkan lokasi (misal A): ");
        advWord();
        char loc = currentWord.contents[0];
        for (int i = 0; i < listBangunan.nEff; i++)
        {
          if (listBangunan.buffer[i].locName == loc)
          {
            foundLoc = true;
            to = listBangunan.buffer[i].locCoords;
            toChar = loc;
            break;
          }
        }
        if (!foundLoc)
        {
          printf("[!] Lokasi tersebut tidak ditemukan. Silakan coba lokasi lain.\n");
        }
      }
      *mobitaLoc = to;
      printf("[!] Mobita sekarang berada di lokasi %c (%d, %d).\n", toChar, Absis(to), Ordinat(to));
    }
    /* === MESIN WAKTU === */
    else if (LP_ELMT(*inventory, invIdx) == 4)
    {
      printf("Mesin Waktu berhasil digunakan!\n");
      Time(*gameTime) -= 50;
      if (Time(*gameTime) < 0)
      {
        Time(*gameTime) = 0;
      }
      printf("[!] Waktu Mobita sekarang adalah %d.\n", Time(*gameTime));
    }
    /* === SENTER PENGECIL === */
    else if (LP_ELMT(*inventory, invIdx) == 5)
    {
      printf("Senter Pengecil berhasil digunakan!\n");
      if (ST_TOP(*bag).jenis != 'H')
      {
        printf("[!] Gadget digunakan, tapi tumpukan teratas dari tas bukanlah Heavy Item.\n");
      }
      else
      {
        if (ST_TOP(*bag).isKecil == true)
        {
          printf("[!] Gadget digunakan, tapi tumpukan teratas tas sudah dalam kondisi dikecilkan.\n");
        }
        else
        {
          (*kecilCount) ++;
          ST_TOP(*bag).isKecil = true;
          NODE_INFO(*inProgressList).isKecil = true;
          printf("[!] Berhasil memberikan efek senter pengecil untuk Heavy Item (%c -> %c)!\n", ST_TOP(*bag).start, ST_TOP(*bag).dest);
        }
      }
    }
    LP_ELMT(*inventory, invIdx) = LP_VAL_UNDEF;
  }
}