#include <stdio.h>
#include "list_linked.h"

/* Definisi List : */
/* List kosong : LL_FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu NODE_INFO(p), NODE_NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NODE_NEXT(Last)=NULL */

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
ElType LL_getElmt(List l, int idx) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengembalikan nilai elemen l pada indeks idx */
  Address now = LL_FIRST(l);
	int i=0;
  for(i=0;i<idx;i++){
    now = NODE_NEXT(now);
	}
	return (NODE_INFO(now));  
}

void LL_setElmt(List *l, int idx, ElType val) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
  Address now=LL_FIRST(*l);
  int i=0;
  for(i=0;i<idx;i++){
    now = NODE_NEXT(now);
  }NODE_INFO(now)=val;
}

int LL_indexOf(List l, ElType val) {

  /* I.S. l, val terdefinisi */
  /* F.S. Mencari apakah ada elemen list l yang bernilai val */
  /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
  /* Mengembalikan IDX_UNDEF jika tidak ditemukan */
  Address p = LL_FIRST(l);
  int idx = 0;
  boolean found = false;
  while (p != NULL && !found) {
    // if (NODE_INFO(p) == val) {
    if (isItemSame(NODE_INFO(p), val)) {
      found = true;
    }
    else {
      p = NODE_NEXT(p);
      idx ++;
    }
  }
  return found ? idx : LL_IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void LL_insertFirst(List *l, ElType val) {
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
  /* Jika alokasi gagal: I.S.= F.S. */
  Address p = newNode(val);
  if (p != NULL) { // Alokasi berhasil
    NODE_NEXT(p) = *l;
    *l = p;
  }
}

void LL_insertLast(List *l, ElType val) {
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
      while (NODE_NEXT(last) != NULL) {
        last = NODE_NEXT(last);
      }
      NODE_NEXT(last) = p;
    }
  }
}

void LL_insertAt(List *l, ElType val, int idx) {
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
        loc = NODE_NEXT(loc);
      }
      NODE_NEXT(p) = NODE_NEXT(loc);
      NODE_NEXT(loc) = p;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void LL_deleteFirst(List *l, ElType *val) {
  /* I.S. List l tidak kosong  */
  /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen pertama di-dealokasi */
  Address p = LL_FIRST(*l);
  *val = NODE_INFO(p);
  LL_FIRST(*l) = NODE_NEXT(p);
  free(p);
}

void LL_deleteLast(List *l, ElType *val) {
  /* I.S. list tidak kosong */
  /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen terakhir di-dealokasi */
  Address p = LL_FIRST(*l);
  Address loc = NULL;
  while (NODE_NEXT(p) != NULL) {
    loc = p;
    p = NODE_NEXT(p);
  }
  if (loc == NULL) {
    LL_FIRST(*l) = NULL;
  } else {
    NODE_NEXT(loc) = NULL;
  }
  *val = NODE_INFO(p);
  free(p);
}

void LL_deleteAt(List *l, int idx, ElType *val) {
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
      loc = NODE_NEXT(loc);
    }
    Address p = NODE_NEXT(loc);
    *val = NODE_INFO(p);
    NODE_NEXT(loc) = NODE_NEXT(p);
    free(p);
  }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void LL_displayList(List l) {
  // void printNODE_Info(List l);
  /* I.S. List mungkin kosong */
  /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika list kosong : menulis [] */
  /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
  // printf("[");
  // Address p = LL_FIRST(l);
  // while (p != NULL) {
  //   if (NODE_NEXT(p) == NULL) {
  //     printf("%d", NODE_INFO(p));
  //   } else {
  //     printf("%d,", NODE_INFO(p));
  //   }
  //   p = NODE_NEXT(p);
  // }
  // printf("]");

  if (LL_isEmpty(l)) printf("[]");
  else{
    List P = LL_FIRST(l);
    displayItem(NODE_INFO(P));
    while (NODE_NEXT(P) != NULL){
      P = NODE_NEXT(P);
      displayItem(NODE_INFO(P));
    }
  }
}

void displayToDo(List l){
  if (LL_isEmpty(l)) printf("Tidak ada pesanan pada To Do List.\n");
  else{
    List P = LL_FIRST(l);
    int i = 1;
    printf("Pesanan pada To Do List:\n");
    printf("%d. ", i);
    displayToDoItem(NODE_INFO(P));
    while (NODE_NEXT(P) != NULL){
      P = NODE_NEXT(P);
      i++;
      printf("%d. ", i);
      displayToDoItem(NODE_INFO(P));
    }
  }
}
/* Proses : Menampilkan To Do List dengan format "No. Asal -> Tujuan (Jenis Item)" */
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke bawah */
/* Jika list kosong : menulis "Tidak ada pesanan pada To Do List" */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

void displayInProgress(List l){
  if (LL_isEmpty(l)) printf("Tidak ada pesanan yang sedang diantarkan.\n");
  else{
    List P = LL_FIRST(l);
    int i = 1;
    printf("Pesanan yang sedang diantarkan:\n");
    printf("%d. ", i);
    displayInProgItem(NODE_INFO(P));
    while (NODE_NEXT(P) != NULL){
      P = NODE_NEXT(P);
      i++;
      printf("%d. ", i);
      displayInProgItem(NODE_INFO(P));
    }
  }
}
/* Proses : Menampilkan In Progress dengan format "No. Jenis Item (Tujuan: Tujuan)" */
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke bawah */
/* Jika list kosong : menulis "Tidak ada pesanan yang sedang diantarkan" */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int LL_length(List l) {
  /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int ctr = 0;
  Address p = LL_FIRST(l);
  while (p != NULL) {
    ctr ++;
    p = NODE_NEXT(p);
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
    LL_insertLast(&l3, NODE_INFO(p));
    p = NODE_NEXT(p);
  }
  p = LL_FIRST(l2);
  while (p != NULL) {
    LL_insertLast(&l3, NODE_INFO(p));
    p = NODE_NEXT(p);
  }
  return l3;
}
