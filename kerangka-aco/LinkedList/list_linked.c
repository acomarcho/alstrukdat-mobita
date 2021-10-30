#include "list_linked.h"
#include <stdio.h>

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void LL_CreateList(List *l) {
  /* I.S. sembarang             */
  /* F.S. Terbentuk list kosong */
  LL_FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean LL_isEmpty(List l) {
  /* Mengirim true jika list kosong */
  return (LL_FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/
Item LL_getElmt(List l, int idx) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengembalikan nilai elemen l pada indeks idx */
  int i = 0;
  Address p = LL_FIRST(l);
  while (i < idx) {
    i ++;
    p = NEXT(p);
  }
  // i = idx
  return INFO(p);
}

void LL_setElmt(List *l, int idx, Item val) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
  int i = 0;
  Address p = LL_FIRST(*l);
  while (i < idx) {
    i ++;
    p = NEXT(p);
  }
  // i = idx
  INFO(p) = val; 
}

int LL_indexOf(List l, Item val) {
  /* I.S. l, val terdefinisi */
  /* F.S. Mencari apakah ada elemen list l yang bernilai val */
  /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
  /* Mengembalikan IDX_UNDEF jika tidak ditemukan */
  Address p = LL_FIRST(l);
  int idx = 0;
  boolean found = false;
  while (p != NULL && !found) {
    if (isItemEqual(INFO(p), val)) {
      found = true;
    }
    else {
      p = NEXT(p);
      idx ++;
    }
  }
  return found ? idx : LL_IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void LL_insertFirst(List *l, Item val) {
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
  /* Jika alokasi gagal: I.S.= F.S. */
  Address p = newNode(val);
  if (p != NULL) { // Alokasi berhasil
    NEXT(p) = *l;
    *l = p;
  }
}

void LL_insertLast(List *l, Item val) {
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen list di akhir: elemen terakhir yang baru */
  /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  if (LL_isEmpty(*l)) {
    LL_insertFirst(l, val);
  } else {
    Address p = newNode(val);
    if (p != NULL) {
      Address last = LL_FIRST(*l);
      while (NEXT(last) != NULL) {
        last = NEXT(last);
      }
      NEXT(last) = p;
    }
  }
}

void LL_insertAt(List *l, Item val, int idx) {
  /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
  /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  if (idx == 0) {
    LL_insertFirst(l, val);
  } else {
    Address p = newNode(val);
    if (p != NULL) {
      int ctr = 0;
      Address loc = LL_FIRST(*l);
      while (ctr < idx - 1) {
        ctr ++;
        loc = NEXT(loc);
      }
      NEXT(p) = NEXT(loc);
      NEXT(loc) = p;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void LL_deleteFirst(List *l, Item *val) {
  /* I.S. List l tidak kosong  */
  /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen pertama di-dealokasi */
  Address p = LL_FIRST(*l);
  *val = INFO(p);
  LL_FIRST(*l) = NEXT(p);
  free(p);
}

void LL_deleteLast(List *l, Item *val) {
  /* I.S. list tidak kosong */
  /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen terakhir di-dealokasi */
  Address p = LL_FIRST(*l);
  Address loc = NULL;
  while (NEXT(p) != NULL) {
    loc = p;
    p = NEXT(p);
  }
  if (loc == NULL) {
    LL_FIRST(*l) = NULL;
  } else {
    NEXT(loc) = NULL;
  }
  *val = INFO(p);
  free(p);
}

void LL_deleteAt(List *l, int idx, Item *val) {
  /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. val diset dengan elemen l pada indeks ke-idx. */
  /*      Elemen l pada indeks ke-idx dihapus dari l */
  if (idx == 0) {
    LL_deleteFirst(l, val);
  } else {
    int ctr = 0;
    Address loc = LL_FIRST(*l);
    while (ctr < idx - 1) {
      ctr ++;
      loc = NEXT(loc);
    }
    Address p = NEXT(loc);
    *val = INFO(p);
    NEXT(loc) = NEXT(p);
    free(p);
  }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void LL_displayList(List l) {
  // void printInfo(List l);
  /* I.S. List mungkin kosong */
  /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika list kosong : menulis [] */
  /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
  printf("[");
  Address p = LL_FIRST(l);
  while (p != NULL) {
    if (NEXT(p) == NULL) {
      printf("%d", INFO(p));
    } else {
      printf("%d,", INFO(p));
    }
    p = NEXT(p);
  }
  printf("]");
}

int LL_length(List l) {
  /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int ctr = 0;
  Address p = LL_FIRST(l);
  while (p != NULL) {
    ctr ++;
    p = NEXT(p);
  }
  return ctr;
}

/****************** PROSES TERHADAP LIST ******************/
List LL_concat(List l1, List l2)  {
  /* I.S. l1 dan l2 sembarang */
  /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
  /* Konkatenasi dua buah list : l1 dan l2    */
  /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
  /* Tidak ada alokasi/dealokasi pada prosedur ini */
  List l3;
  LL_CreateList(&l3);
  Address p = LL_FIRST(l1);
  while (p != NULL) {
    LL_insertLast(&l3, INFO(p));
    p = NEXT(p);
  }
  p = LL_FIRST(l2);
  while (p != NULL) {
    LL_insertLast(&l3, INFO(p));
    p = NEXT(p);
  }
  return l3;
}
