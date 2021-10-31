/*
  NIM: 13520119
  Nama: Marchotridyo
  Tanggal: 18 Oktober
  Topik Praktikum: ADT Stack
  Deskripsi: Pra-praktikum
*/

#include "stack.h"

/* *** Konstruktor/Kreator *** */
void ST_CreateStack(Stack *s) {
  /* I.S. sembarang; */
  /* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
  /* - Index top bernilai IDX_UNDEF */
  /* Proses : Melakukan alokasi, membuat sebuah s kosong */
  ST_IDX_TOP(*s) = ST_IDX_UNDEF;
}

/* ************ Prototype ************ */
boolean ST_isEmpty(Stack s) {
  /* Mengirim true jika s kosong: lihat definisi di atas */
  return ST_IDX_TOP(s) == ST_IDX_UNDEF;
}

boolean ST_isFull(Stack s) {
  /* Mengirim true jika tabel penampung nilai s stack penuh */
  return ST_IDX_TOP(s) == ST_CAPACITY - 1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void ST_push(Stack *s, Item val) {
  /* Menambahkan val sebagai elemen Stack s */
  /* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
  /* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */
  ST_IDX_TOP(*s) ++;
  ST_TOP(*s) = val;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void ST_pop(Stack *s, Item *val) {
  /* Menghapus val dari Stack s */
  /* I.S. s tidak mungkin kosong */
  /* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */
  *val = ST_TOP(*s);
  ST_IDX_TOP(*s) --;
}