/* ADT BAG yang menyimpan item yang diambil dari lokasi Mobita */
/* Aturan masuk item bersifat LIFO (Last In First Out) */

#ifndef BAG_H
#define BAG_H

#include "boolean.h"
#include <stdlib.h>
#include "item.h"

/* KUANTITAS BAG */
#define MinCAPACITY 3
#define MaxCAPACITY 100

typedef char ElBag;
typedef struct
{
    int CAPACITY;
    int idxTop;
    Item bag[MaxCAPACITY]; /* Tabel penyimpan Elemen Berupa Item*/
} BAG;

/* ********* AKSES (Selektor) ********* */
/* Akses elemen ke k dari Bag B adalah sebagai berikut. */
#define IDX_TOP(B) (B).idxTop
#define CAPACITY(B) (B).CAPACITY
#define INFO(B, k) (B).bag[k]

void CreateBag(BAG *B);
/* Membuat Bag kosong dengan CAPACITY = 3 */

boolean IsEmptyBag(BAG B);
/* Mengecek Apakah Bag Kosong, Jika kosong Mengirimkan True, jika sebaliknya mengirimkan false */

boolean IsFullBag(BAG B);
/* Mengecek Apakah Bag Penuh, Jika penuh Mengirimkan True, jika sebaliknya mengirimkan false */

boolean IsBagMax(BAG B);
/* Mengecek apakah kapasitas dari Bag melebih kapasitas maksimum dari tas yang mungkin */

void IncreaseCapacity(BAG *B);
/* Menambahkan jumlah kapasitas dari BAG */

void GetItem(BAG *B, Item item);
/* Melakukan Get Elemen dengan mengikuti Aturan LIFO (Last In First Out) */

void Drop_Off(BAG *B, Item *item);
/* Melakukan penghapusan pada item yang ada di tas dengan mengikuti prinsip LIFO dimana item yang didrop out adalah item di tumpukan teratas */

boolean IsThere_Item(char jenis_Item, BAG bag);
/* Mengecek apakah ada jenis item tertentu di bag. Jika ya maka akan mengirimkan true, jika tidak maka akan mengirimkan false */

boolean iSthereDone(BAG B, char Dest);
/* Mengecek apakah terdapat item yang berada pada destination tersebut */

boolean isTheItemDone(BAG B, char Jenis_Item, char Dest);
/* Mengecek apakah Item tertentu berhasil diantarkan */

int NumberOfItemDone(BAG B, char Jenis_Item, char Dest);
/* Menghitung banyaknya item berjenis tertentu berhasil diantarkan ke destination */

#endif
