/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori list dinamik */

#ifndef LISTDIN_H
#define LISTDIN_H

#include "../ADT/boolean.h"
#include "../ADT/point.h"

/*  Kamus Umum */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef struct {
   char locName;
   POINT locCoords;
} Bangunan; /* type elemen list */
typedef int IdxType;

typedef struct
{
    Bangunan* buffer; /* memori tempat penyimpan elemen (container) */
    int nEff;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ukuran elemen */
} ListDin;
/* Indeks yang digunakan [0..capacity-1] */
/* Jika l adalah : ListDin, cara deklarasi dan akses: */
/* Deklarasi : l : ListDin */
/* Maka cara akses:
   l.nEff  untuk mengetahui banyaknya elemen
   l.buffer    untuk mengakses seluruh nilai elemen list
   l.buffer[i] untuk mengakses elemen ke-i */
/* Definisi :
  list kosong: l.nEff = 0
  Definisi elemen pertama : l.buffer[i] dengan i=0
  Definisi elemen terakhir yang terdefinisi: l.buffer[i] dengan i=l.nEff */

/* ********** SELEKTOR ********** */
#define LD_NEFF(l) (l).nEff
#define LD_BUFFER(l) (l).buffer
#define LD_ELMT(l, i) (l).buffer[i]
#define LD_CAPACITY(l) (l).capacity

/* Konstruktor : create list kosong  */
void LD_CreateListDin(ListDin *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

Bangunan LD_CreateBangunan(char locName, int row, int col);
// Membentuk bangunan dengan locName dan posisi (row, col)

void LD_dealocate(ListDin *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

boolean LD_isIdxEff(ListDin l, IdxType idx);
// Mengembalikan apakah idx merupakan index efektif.

int LD_length(ListDin l);
// Mengembalikan panjang dari ListDin.

void LD_insertLast(ListDin *l, Bangunan val);
// Memasukkan val ke akhir ListDin.

#endif