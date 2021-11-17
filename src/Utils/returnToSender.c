#include "returnToSender.h"

void handleReturn(boolean returnToSender, List* inProgressList, Stack* bag, List* toDoList, int* hvyItems, int* kecilCount) {
  /* Implementasi command RETURN */
  if (!returnToSender)
  {
    printf("[!] Mobita tidak memiliki ability return to sender!\n");
  }
  else
  {
    if (LL_isEmpty(*inProgressList))
    {
      printf("[!] Mobita tidak memiliki barang yang bisa dikembalikan!\n");
    }
    else
    {
      Item tmp = ST_TOP(*bag);
      if (tmp.jenis == 'V')
      {
        printf("[!] Mobita tidak bisa mengembalikan VIP item!\n");
      }
      else
      {
        // Jika perishable, reset waktunya.
        if (tmp.jenis == 'P')
        {
          tmp.sisa_waktu = tmp.hangus;
        }
        if (tmp.jenis == 'H')
        {
          (*hvyItems) --;
          if (tmp.isKecil == true)
          {
            tmp.isKecil = false;
            (*kecilCount) --;
          }
        }
        Item unused;
        LL_deleteFirst(inProgressList, &unused);
        ST_pop(bag, &unused);
        LL_insertLast(toDoList, tmp);
        printf("Ability return to sender berhasil!\n");
        printf("[!] Item jenis %c (%c -> %c) berhasil dikembalikan.\n", tmp.jenis, tmp.start, tmp.dest);
      }
    }
  }
}