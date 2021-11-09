/* 
    NIM                 : 13520119
    Nama                : Marchotridyo
    Tanggal             : 8 September 2021
    Topik Praktikum     : ADT List
    Deskripsi           : Pra-Praktikum 3
*/

#include <stdio.h>
#include "listpos.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPos(ListPos *l) {
  /* I.S. l sembarang */
  /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
  /* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
  ListPos tmp;
  int i;
  for (i = 0; i < LP_CAPACITY; i ++) {
    LP_ELMT(tmp, i) = LP_VAL_UNDEF;
  }
  *l = tmp;
}


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l) {
  /* Mengirimkan banyaknya elemen efektif List */
  /* Mengirimkan nol jika List kosong */
  int count = 0;
  for (int i = 0; i < LP_CAPACITY; i++) {
    if (LP_ELMT(l, i) != LP_VAL_UNDEF) {
      count += 1;
    }
  }
  return count;
}

/* ********** Test Indeks yang valid ********** */
boolean LP_isIdxValid(ListPos l, int i) {
  /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
  /* yaitu antara indeks yang terdefinisi utk container*/
  return (i >= 0 && i < LP_CAPACITY);
}

boolean LP_isIdxEff(ListPos l, int i) {
  /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
  /* yaitu antara 0..length(l)-1 */
  return (i >= 0 && i < length(l));
}


/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListPos l) {
  /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
  return (length(l) == 0);
}
/* *** Test List penuh *** */
boolean isFull(ListPos l) {
  /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
  return (length(l) == LP_CAPACITY);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListPos *l) {
  /* I.S. l sembarang */
  /* F.S. List l terdefinisi */
  /* Proses: membaca banyaknya elemen l dan mengisi nilainya */
  /* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
  /*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
  /*    Jika n tidak valid, tidak diberikan pesan kesalahan */
  /* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
            Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
  /*    Jika n = 0; hanya terbentuk List kosong */
  int n;
  scanf("%d", &n);
  while(n < 0 || n > LP_CAPACITY) {
    scanf("%d", &n);
  }

  if (n == 0) {
    CreateListPos(l);
  } else {
    CreateListPos(l);
    int i;
    for(i = 0; i < n; i++) {
      int k;
      scanf("%d", &k);
      LP_ELMT(*l, i) = k;
    }
  }
}

void displayList(ListPos l) {
  /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
  /* I.S. l boleh kosong */
  /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika List kosong : menulis [] */
  if (isEmpty(l)) {
    printf("[]");
  } else {
    printf("[");
    int i;
    for(i = 0; i < length(l); i++) {
      printf("%d", LP_ELMT(l, i));
      if (i != length(l) - 1) {
        printf(",");
      }
    }
    printf("]");
  }
}


/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus) {
  /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
  /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
        indeks yang sama dijumlahkan */
  /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
        elemen l2 pada indeks yang sama */
  ListPos result;
  CreateListPos(&result);
  int i;
  for (i = 0; i < length(l1); i ++) {
    if (plus) {
      LP_ELMT(result, i) = LP_ELMT(l1, i) + LP_ELMT(l2, i);
    } else {
      LP_ELMT(result, i) = LP_ELMT(l1, i) - LP_ELMT(l2, i);
    }
  }
  return result;
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListPos l1, ListPos l2) {
  /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
  if (length(l1) != length(l2)) {
    return false;
  } else {
    int i = 0;
    boolean isEqual = true;
    while (i < length(l1) && isEqual) {
      if (LP_ELMT(l1, i) != LP_ELMT(l2, i)) {
        isEqual = false;
      } else {
        i += 1;
      }
    }
    return isEqual;
  }
}


/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListPos l, LP_ElType val) {
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
  /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
  /* Skema Searching yang digunakan bebas */
  if (isEmpty(l)) {
    return LP_IDX_UNDEF;
  } else {
    int i = 0;
    boolean isFound = false;
    while (i < LP_CAPACITY && !isFound) {
      if (LP_ELMT(l, i) == val) {
        isFound = true;
      } else {
        i += 1;
      }
    }
    if (isFound) {
      return i;
    } else {
      return LP_IDX_UNDEF;
    }
  }
}


/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, LP_ElType *max, LP_ElType *min) {
  /* I.S. List l tidak kosong */
  /* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
  LP_ElType minVal = LP_ELMT(l, 0);
  LP_ElType maxVal = LP_ELMT(l, 0);
  int i;
  for (i = 1; i < length(l); i++) {
    if (LP_ELMT(l, i) > maxVal) {
      maxVal = LP_ELMT(l, i);
    }
    if (LP_ELMT(l, i) < minVal) {
      minVal = LP_ELMT(l, i);
    }
  }
  *max = maxVal;
  *min = minVal;
}


/* ********** OPERASI LAIN ********** */
boolean isAllEven(ListPos l) {
  /* Menghasilkan true jika semua elemen l genap */
  int i = 0;
  boolean foundOdd = false;
  while (i < length(l) && !foundOdd) {
    if (LP_ELMT(l, i) % 2 != 0) {
      foundOdd = true;
    } else {
      i += 1;
    }
  }
  return !foundOdd;
}


/* ********** SORTING ********** */
void sort(ListPos *l, boolean asc) {
  /* I.S. l boleh kosong */
  /* F.S. Jika asc = true, l terurut membesar */
  /*      Jika asc = false, l terurut mengecil */
  /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
  int i, j;
  for (i = 0; i < length(*l); i++) {
    for (j = 0; j < length(*l) - i - 1; j++) {
      if (asc) {
        if (LP_ELMT(*l, j) > LP_ELMT(*l, j+1)) {
          LP_ElType tmp = LP_ELMT(*l, j);
          LP_ELMT(*l, j) = LP_ELMT(*l, j+1);
          LP_ELMT(*l, j+1) = tmp;
        }
      } else {
        if (LP_ELMT(*l, j) < LP_ELMT(*l, j+1)) {
          LP_ElType tmp = LP_ELMT(*l, j);
          LP_ELMT(*l, j) = LP_ELMT(*l, j+1);
          LP_ELMT(*l, j+1) = tmp;
        }
      }
    }
  }
}


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, LP_ElType val) {
  /* Proses: Menambahkan val sebagai elemen terakhir List */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */
  LP_ELMT(*l, length(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, LP_ElType *val) {
  /* Proses : Menghapus elemen terakhir List */
  /* I.S. List tidak kosong */
  /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
  /*      Banyaknya elemen List berkurang satu */
  /*      List l mungkin menjadi kosong */
  *val = LP_ELMT(*l, length(*l) - 1);
  LP_ELMT(*l, length(*l) - 1) = LP_VAL_UNDEF;
}

int near_empty(ListPos l) {
  int near = 0;
  while (near < LP_CAPACITY) {
    if (LP_ELMT(l, near) == LP_VAL_UNDEF) {
      break;
    }
    near += 1;
  }
  return near;
}

void send_to_inventory(ListPos *l, LP_ElType val) {
  LP_ELMT(*l, near_empty(*l)) = val;
}

void gadget_now(ListPos *l, LP_ElType val) {
  LP_ELMT(*l, near_empty(*l)) = val;
}