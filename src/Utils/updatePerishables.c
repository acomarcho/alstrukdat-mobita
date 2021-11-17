#include "updatePerishables.h"

void updatePerishables(List *inProgressList, Stack *bag, int time)
{
  // Update inProgressList.
  Address prev = NULL;
  Address p = LL_FIRST(*inProgressList);
  List newList;
  LL_CreateList(&newList);
  while (p != NULL)
  {
    if (NODE_INFO(p).jenis == 'P')
    {
      NODE_INFO(p).sisa_waktu -= time;
      if (NODE_INFO(p).sisa_waktu > 0)
      {
        LL_insertLast(&newList, NODE_INFO(p));
      }
      else
      {
        printf("[!] Gagal mengirimkan perishable (%c -> %c) karena waktu sudah habis.\n", NODE_INFO(p).start, NODE_INFO(p).dest);
      }
    }
    else
    {
      LL_insertLast(&newList, NODE_INFO(p));
    }
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
    if (tmp.jenis == 'P')
    {
      tmp.sisa_waktu -= time;
      if (tmp.sisa_waktu > 0)
      {
        ST_push(&tmpBag, tmp);
      }
      // Jika habis, tidak usah dipush.
    }
    else
    {
      ST_push(&tmpBag, tmp);
    }
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
