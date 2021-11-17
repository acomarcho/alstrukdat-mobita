#include "pickup.h"

void pickup(List* toDoList, POINT mobitaLoc, ListDin listBangunan, int VIPItemCount, Stack* bag, int bag_capacity, int* hvyItems, int* speedboostCount, List* inProgressList) {
  /* Implementasi command PICK_UP */
  // Cek apakah ada pesanan di toDoList
  boolean found = false;
  int idx = 0;
  Address p = LL_FIRST(*toDoList);
  while (p != NULL && !found)
  {
    if (NODE_INFO(p).start == getLocationName(mobitaLoc, listBangunan))
    {
      found = true;
    }
    else
    {
      p = NODE_NEXT(p);
      idx++;
    }
  }
  if (found)
  {
    if (VIPItemCount > 0 && NODE_INFO(p).jenis != 'V')
    {
      printf("[!] Mobita tidak bisa mengambil pick up dari lokasi ini karena perlu mengantar VIP Item terlebih dahulu.\n");
    }
    else
    {
      // Ada toDoList yang sesuai dengan lokasi sekarang
      if (ST_IDX_TOP(*bag) == bag_capacity - 1)
      {
        // Bag penuh.
        printf("Kapasitas tas penuh.\n");
      }
      else
      {
        // Bag tidak penuh.
        Item item = NODE_INFO(p);
        switch (item.jenis)
        {
        case 'N':
          printf("Pesanan berupa Normal Item berhasil diambil!\n");
          break;
        case 'H':
          printf("Pesanan berupa Heavy Item berhasil diambil!\n");
          *hvyItems += 1;
          printf("[!] Mobita sedang mengangkut %d buah Heavy Item(s).\n", *hvyItems);
          if (*speedboostCount > 0)
          {
            printf("[!] Speedboost dinonaktifkan karena mengangkut Heavy Item.\n");
            *speedboostCount = 0;
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
        LL_insertFirst(inProgressList, item);
        // Masukkan item ke tas.
        ST_push(bag, item);
        // Hapus dari toDoList
        Item tmp;
        LL_deleteAt(toDoList, idx, &tmp);
      }
    }
  }
  else
  {
    printf("[!] Pesanan tidak ditemukan!\n");
  }
}