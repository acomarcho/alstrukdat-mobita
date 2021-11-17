#include "dropoff.h"

void dropoff(List* inProgressList, Stack* bag, POINT mobitaLoc, ListDin listBangunan, int* hvyItems, int* kecilCount, int* speedboostCount, int* bag_capacity, int* VIPItemCount, boolean* returnToSender, int* money, int* deliveredCount) {
  /* Implementasi command DROP_OFF */
  if (LL_isEmpty(*inProgressList))
  {
    printf("[!] Tidak ada pesanan yang dapat diantarkan!\n");
  }
  else
  {
    Item item = ST_TOP(*bag);
    if (item.dest == getLocationName(mobitaLoc, listBangunan))
    { // Lokasi benar!
      int prize;
      switch (item.jenis)
      {
      case 'N':
        printf("Pesanan Normal Item berhasil diantarkan.\n");
        prize = 200;
        break;
      case 'H':
        printf("Pesanan Heavy Item berhasil diantarkan.\n");
        (*hvyItems) --;
        if (item.isKecil == true)
        {
          (*kecilCount) --;
        }
        if (*hvyItems - *kecilCount == 0)
        {
          // Aktivasi speedboost
          *speedboostCount = 10;
          printf("Speedboost teraktivasi!\n");
        }
        prize = 400;
        break;
      case 'P':
        printf("Pesanan Perishable Item berhasil diantarkan.\n");
        (*bag_capacity) ++;
        printf("[!] Capacity bag Mobita bertambah 1 menjadi %d!\n", *bag_capacity);
        prize = 400;
        break;
      case 'V':
        printf("Pesanan VIP Item berhasil diantarkan.\n");
        (*VIPItemCount) --;
        if (!(*returnToSender))
        {
          printf("[!] Mobita mendapatkan ability Return to Sender!\n");
          *returnToSender = true;
        }
        if (*VIPItemCount == 0)
        {
          printf("[!] Semua pesanan VIP telah diantarkan!\n");
        }
        prize = 600;
        break;
      }
      *money += prize;
      (*deliveredCount) ++;
      printf("Uang yang didapatkan: %d Yen\n", prize);
      // Hapus dari inProgressList dan bag.
      Item tmp;
      LL_deleteFirst(inProgressList, &tmp);
      ST_pop(bag, &tmp);
    }
    else
    { // Lokasi salah.
      printf("Tidak ada pesanan yang dapat diantarkan!\n");
    }
  }
}