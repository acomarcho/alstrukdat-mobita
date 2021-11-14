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
int LP_length(ListPos l) {
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
  return (i >= 0 && i < LP_length(l));
}


/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean LP_isEmpty(ListPos l) {
  /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
  return (LP_length(l) == 0);
}
/* *** Test List penuh *** */
boolean LP_isFull(ListPos l) {
  /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
  return (LP_length(l) == LP_CAPACITY);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void LP_readList(ListPos *l) {
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

void LP_displayList(ListPos l) {
  /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
  /* I.S. l boleh kosong */
  /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika List kosong : menulis [] */
  if (LP_isEmpty(l)) {
    printf("[]");
  } else {
    printf("[");
    int i;
    for(i = 0; i < LP_length(l); i++) {
      printf("%d", LP_ELMT(l, i));
      if (i != LP_length(l) - 1) {
        printf(",");
      }
    }
    printf("]");
  }
}


/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos LP_plusMinusTab(ListPos l1, ListPos l2, boolean plus) {
  /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
  /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
        indeks yang sama dijumlahkan */
  /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
        elemen l2 pada indeks yang sama */
  ListPos result;
  CreateListPos(&result);
  int i;
  for (i = 0; i < LP_length(l1); i ++) {
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
boolean LP_isListEqual(ListPos l1, ListPos l2) {
  /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
  if (LP_length(l1) != LP_length(l2)) {
    return false;
  } else {
    int i = 0;
    boolean isEqual = true;
    while (i < LP_length(l1) && isEqual) {
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
int LP_indexOf(ListPos l, LP_ElType val) {
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
  /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
  /* Skema Searching yang digunakan bebas */
  if (LP_isEmpty(l)) {
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
void LP_extremes(ListPos l, LP_ElType *max, LP_ElType *min) {
  /* I.S. List l tidak kosong */
  /* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
  LP_ElType minVal = LP_ELMT(l, 0);
  LP_ElType maxVal = LP_ELMT(l, 0);
  int i;
  for (i = 1; i < LP_length(l); i++) {
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
boolean LP_isAllEven(ListPos l) {
  /* Menghasilkan true jika semua elemen l genap */
  int i = 0;
  boolean foundOdd = false;
  while (i < LP_length(l) && !foundOdd) {
    if (LP_ELMT(l, i) % 2 != 0) {
      foundOdd = true;
    } else {
      i += 1;
    }
  }
  return !foundOdd;
}


/* ********** SORTING ********** */
void LP_sort(ListPos *l, boolean asc) {
  /* I.S. l boleh kosong */
  /* F.S. Jika asc = true, l terurut membesar */
  /*      Jika asc = false, l terurut mengecil */
  /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
  int i, j;
  for (i = 0; i < LP_length(*l); i++) {
    for (j = 0; j < LP_length(*l) - i - 1; j++) {
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
void LP_insertLast(ListPos *l, LP_ElType val) {
  /* Proses: Menambahkan val sebagai elemen terakhir List */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */
  LP_ELMT(*l, LP_length(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void LP_deleteLast(ListPos *l, LP_ElType *val) {
  /* Proses : Menghapus elemen terakhir List */
  /* I.S. List tidak kosong */
  /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
  /*      Banyaknya elemen List berkurang satu */
  /*      List l mungkin menjadi kosong */
  *val = LP_ELMT(*l, LP_length(*l) - 1);
  LP_ELMT(*l, LP_length(*l) - 1) = LP_VAL_UNDEF;
}

int getEmptySlot(ListPos l) {
  /* Mendapatkan index slot terkecil yang masih kosong */
  int near = 0;
  while (near < LP_CAPACITY) {
    if (LP_ELMT(l, near) == LP_VAL_UNDEF) {
      break;
    }
    near += 1;
  }
  return near;
}

void addToInventory(ListPos *l, LP_ElType val) {
  /* Menambahkan ke inventory */
  LP_ELMT(*l, getEmptySlot(*l)) = val;
}

void useFromInventory(ListPos *l, int idx) {
  /* Menghilangkan dari inventory */
  // 1 = Kain Pembungkus Waktu
  // 2 = Senter Pembesar
  // 3 = Pintu Kemana Saja
  // 4 = Mesin Waktu
  // 5 = Senter Pengecil
  if (LP_ELMT(*l, idx) == 1) {
    printf("Kain Pembungkus Waktu berhasil digunakan!\n");
  } else if (LP_ELMT(*l, idx) == 2) {
    printf("Senter Pembesar berhasil digunakan!\n");
  } else if (LP_ELMT(*l, idx) == 3) {
    printf("Pintu Kemana Saja berhasil digunakan!\n");
  } else if (LP_ELMT(*l, idx) == 4) {
    printf("Meisn Waktu berhasil digunakan!\n");
  } else if (LP_ELMT(*l, idx) == 5) {
    printf("Senter Pengecil berhasil digunakan!\n");
  }
  LP_ELMT(*l, idx) = LP_VAL_UNDEF;
}

void showInventory(ListPos l) {
  /* Menunjukkan isi inventory */
  // 1 = Kain Pembungkus Waktu
  // 2 = Senter Pembesar
  // 3 = Pintu Kemana Saja
  // 4 = Mesin Waktu
  // 5 = Senter Pengecil
  for (int i = 1; i <= LP_CAPACITY; i ++) {
    if (LP_ELMT(l, i-1) == 1) {
      printf("%d. Kain Pembungkus Waktu\n", i);
    } else if (LP_ELMT(l, i-1) == 2) {
      printf("%d. Senter Pembesar\n", i);
    } else if (LP_ELMT(l, i-1) == 3) {
      printf("%d. Pintu Kemana Saja\n", i);
    } else if (LP_ELMT(l, i-1) == 4) {
      printf("%d. Mesin Waktu\n", i);
    } else if (LP_ELMT(l, i-1) == 5) {
      printf("%d. Senter Pengecil\n", i);
    } else {
      printf("%d. -\n", i);
    }
  }
}