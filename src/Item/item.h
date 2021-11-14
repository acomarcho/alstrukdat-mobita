/* File : item.h */
/* Definisi ADT Item */

#ifndef ITEM_H
#define ITEM_H
#include "../Boolean/boolean.h"

/* Definisi elemen dan address */
typedef struct {
    int masuk;      // waktu masuk
    int nilai;
    int hangus;     // menyimpan batas waktu hangus
    int sisa_waktu; // sisa waktu sebelum perishable item hangus
    char start;
    char dest;
    char jenis;
    boolean isKecil;
} Item;

void CreateItem(Item *i, int masuk, char start, char dest, char jenis);
/* Proses: Mendeklarasikan Item */
/* I.S. sembarang */
/* F.S. terbentuk sebuah item */

void CreatePerishableItem(Item *i, int masuk, char start, char dest, int hangus);
/* Proses: Mendeklarasikan Perishable Item */
/* I.S. sembarang */
/* F.S. terbentuk sebuah perishable item */


/* ===== SELEKTOR ===== */
#define MASUK(i) (i).masuk
#define JENIS(i) (i).jenis
#define NILAI(i) (i).nilai
#define SISA_WAKTU(i) (i).sisa_waktu
#define HANGUS(i) (i).hangus
#define START(i) (i).start
#define DESTINATION(i) (i).dest


void displayItem(Item i);
/* Proses: Menampilkan sebuah item dengan format "Waktu : Asal -> Tujuan (Jenis Item)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

void displayToDoItem(Item i);
/* Proses: Menampilkan sebuah item dengan format "Asal -> Tujuan (Jenis Item)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

void displayInProgItem(Item i);
/* Proses: Menampilkan sebuah item dengan format "Jenis Item (Tujuan: Tujuan)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

boolean isItemSame(Item i1, Item i2);
/* Proses: Membandingkan kedua kesamaan antara 2 item */
/* I.S. i1 dan i2 terdefinisi */
/* F.S. Mengeluarkan true jika i1 == i2. False jika sebaliknya */

#endif