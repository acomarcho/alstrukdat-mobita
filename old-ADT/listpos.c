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
  for (i = 0; i < CAPACITY; i ++) {
    ELMT(tmp, i) = VAL_UNDEF;
  }
  *l = tmp;
}


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l) {
  /* Mengirimkan banyaknya elemen efektif List */
  /* Mengirimkan nol jika List kosong */
  int i;
  i = 0;
  while (i < CAPACITY && ELMT(l, i) != VAL_UNDEF) {
    i ++;
  }
  return i;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListPos l, int i) {
  /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
  /* yaitu antara indeks yang terdefinisi utk container*/
  return (i >= 0 && i < CAPACITY);
}

boolean isIdxEff(ListPos l, int i) {
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
  return (length(l) == CAPACITY);
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
  while(n < 0 || n > CAPACITY) {
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
      ELMT(*l, i) = k;
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
      printf("%d", ELMT(l, i));
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
      ELMT(result, i) = ELMT(l1, i) + ELMT(l2, i);
    } else {
      ELMT(result, i) = ELMT(l1, i) - ELMT(l2, i);
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
      if (ELMT(l1, i) != ELMT(l2, i)) {
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
int indexOf(ListPos l, ElType val) {
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
  /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
  /* Skema Searching yang digunakan bebas */
  if (isEmpty(l)) {
    return IDX_UNDEF;
  } else {
    int i = 0;
    boolean isFound = false;
    while (i < length(l) && !isFound) {
      if (ELMT(l, i) == val) {
        isFound = true;
      } else {
        i += 1;
      }
    }
    if (isFound) {
      return i;
    } else {
      return IDX_UNDEF;
    }
  }
}


/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, ElType *max, ElType *min) {
  /* I.S. List l tidak kosong */
  /* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
  ElType minVal = ELMT(l, 0);
  ElType maxVal = ELMT(l, 0);
  int i;
  for (i = 1; i < length(l); i++) {
    if (ELMT(l, i) > maxVal) {
      maxVal = ELMT(l, i);
    }
    if (ELMT(l, i) < minVal) {
      minVal = ELMT(l, i);
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
    if (ELMT(l, i) % 2 != 0) {
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
        if (ELMT(*l, j) > ELMT(*l, j+1)) {
          ElType tmp = ELMT(*l, j);
          ELMT(*l, j) = ELMT(*l, j+1);
          ELMT(*l, j+1) = tmp;
        }
      } else {
        if (ELMT(*l, j) < ELMT(*l, j+1)) {
          ElType tmp = ELMT(*l, j);
          ELMT(*l, j) = ELMT(*l, j+1);
          ELMT(*l, j+1) = tmp;
        }
      }
    }
  }
}


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, ElType val) {
  /* Proses: Menambahkan val sebagai elemen terakhir List */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */
  ELMT(*l, length(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, ElType *val) {
  /* Proses : Menghapus elemen terakhir List */
  /* I.S. List tidak kosong */
  /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
  /*      Banyaknya elemen List berkurang satu */
  /*      List l mungkin menjadi kosong */
  *val = ELMT(*l, length(*l) - 1);
  ELMT(*l, length(*l) - 1) = VAL_UNDEF;
}