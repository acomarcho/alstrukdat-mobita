#include "updateSenterPengecil.h"

void updateSenterPengecil(List *inProgressList, Stack *bag, int *kecilCount) {
  /* Mengembalikan item yang memiliki efek senter pengecil menjadi tidak kecil lagi. */
  // Update inProgressList.
  Address p = LL_FIRST(*inProgressList);
  List newList;
  LL_CreateList(&newList);
  while (p != NULL)
  {
    if (NODE_INFO(p).jenis == 'H' && NODE_INFO(p).isKecil == true)
    {
      NODE_INFO(p).isKecil = false;
      printf("[!] Efek senter pengecil pada heavy item (%c -> %c) dinonaktifkan.\n", NODE_INFO(p).start, NODE_INFO(p).dest);
      (*kecilCount) --;
    }
    LL_insertLast(&newList, NODE_INFO(p));
    p = NODE_NEXT(p);
  }
  *inProgressList = newList;
  // Update bag.
  Stack tmpBag;
  ST_CreateStack(&tmpBag);
  while (!ST_isEmpty(*bag))
  {
    Item tmp;
    ST_pop(bag, &tmp);
    if (tmp.jenis == 'H' && tmp.isKecil == true)
    {
      tmp.isKecil = false;
    }
    ST_push(&tmpBag, tmp);
  }
  // tmpBag terbalik.
  ST_CreateStack(bag);
  while (!ST_isEmpty(tmpBag))
  {
    Item tmp;
    ST_pop(&tmpBag, &tmp);
    ST_push(bag, tmp);
  }
}