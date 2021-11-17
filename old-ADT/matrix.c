#include "matrix.h"
#include "boolean.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void CreateMatrix(int nRow, int nCol, Matrix *m) {
  /* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
  /* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
  /* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
  ROWS(*m) = nRow;
  COLS(*m) = nCol;
}

/* *** Selektor "DUNIA Matrix" *** */
boolean isIdxValid(int i, int j) {
  /* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
  return (0 <= i && 0 <= j && i < ROW_CAP && j < COL_CAP);
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
Index getLastIdxRow(Matrix m) {
  /* Mengirimkan Index baris terbesar m */
  return ROWS(m) - 1;
}

Index getLastIdxCol(Matrix m) {
  /* Mengirimkan Index kolom terbesar m */
  return COLS(m) - 1;
}

boolean isIdxEff(Matrix m, Index i, Index j) {
  /* Mengirimkan true jika i, j adalah Index efektif bagi m */
  return (0 <= i && 0 <= j && i <= getLastIdxRow(m) && j <= getLastIdxCol(m));
}

ElType getElmtDiagonal(Matrix m, Index i) {
  /* Mengirimkan elemen m(i,i) */
  return ELMT(m, i, i);
}


/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mRes){
  /* Melakukan assignment MRes = MIn */
  CreateMatrix(ROWS(mIn), COLS(mIn), mRes);
  int i, j;
  for (i = 0; i <= getLastIdxRow(mIn); i ++) {
    for (j = 0; j <= getLastIdxCol(mIn); j ++) {
      ELMT(*mRes, i, j) = ELMT(mIn, i, j);
    }
  }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol){
  /* I.S. isIdxValid(nRow,nCol) */
  /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
  /* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
  /* Selanjutnya membaca nilai elemen per baris dan kolom */
  /* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
  1 2 3
  4 5 6
  8 9 10 
  */
  CreateMatrix(nRow, nCol, m);
  int i, j;
  for (i = 0; i < nRow; i ++) {
    for (j = 0; j < nCol; j ++) {
      scanf("%d", &ELMT(*m, i, j));
    }
  }
}

void displayMatrix(Matrix m) {
  /* I.S. m terdefinisi */
  /* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
    dipisahkan sebuah spasi */
  /* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
  /* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
  1 2 3
  4 5 6
  8 9 10
  */
  int i, j;
  for (i = 0; i <= getLastIdxRow(m); i ++) {
    for (j = 0; j <= getLastIdxCol(m); j ++) {
      printf("%d", ELMT(m, i, j));
      if (j != getLastIdxCol(m)) {
        printf(" ");
      }
    }
    if (i != getLastIdxRow(m)) {
      printf("\n");
    }
  }
}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2) {
  /* Prekondisi : m1 berukuran sama dengan m2 */
  /* Mengirim hasil penjumlahan matriks: m1 + m2 */
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m1), &m3);
  int i, j;
  for (i = 0; i <= getLastIdxRow(m1); i ++) {
    for (j = 0; j <= getLastIdxCol(m1); j ++) {
      ELMT(m3, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
    }
  }
  return m3;
}

Matrix subtractMatrix(Matrix m1, Matrix m2) {
  /* Prekondisi : m1 berukuran sama dengan m2 */
  /* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m1), &m3);
  int i, j;
  for (i = 0; i <= getLastIdxRow(m1); i ++) {
    for (j = 0; j <= getLastIdxCol(m1); j ++) {
      ELMT(m3, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
    }
  }
  return m3;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2) {
  /* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
  /* Mengirim hasil perkalian matriks: salinan m1 * m2 */
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m2), &m3);
  int i, j, k;
  for (i = 0; i <= getLastIdxRow(m3); i ++) {
    for (j = 0; j <= getLastIdxCol(m3); j ++) {
      ELMT(m3, i, j) = 0;
      for (k = 0; k <= getLastIdxCol(m1); k ++) {
        ELMT(m3, i, j) += (ELMT(m1, i, k) * ELMT(m2, k, j));
      }
    }
  }
  return m3;
}

Matrix multiplyConst(Matrix m, ElType x) {
  /* Mengirim hasil perkalian setiap elemen m dengan x */
  Matrix retM;
  CreateMatrix(ROWS(m), COLS(m), &retM);
  int i, j;
  for (i = 0; i <= getLastIdxRow(m); i ++) {
    for (j = 0; j <= getLastIdxCol(m); j ++) {
      ELMT(retM, i, j) = x * ELMT(m, i, j);
    }
  }
  return retM;
}

void pMultiplyConst(Matrix *m, ElType k) {
  /* I.S. m terdefinisi, k terdefinisi */
  /* F.S. Mengalikan setiap elemen m dengan k */
  int i, j;
  for (i = 0; i <= getLastIdxRow(*m); i ++) {
    for (j = 0; j <= getLastIdxCol(*m); j ++) {
      ELMT(*m, i, j) = k * ELMT(*m, i, j);
    }
  }
}


/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isEqual(Matrix m1, Matrix m2) {
  /* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
  /* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
  /* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
  if (ROWS(m1) != ROWS(m2) || COLS(m1) != COLS(m2)) {
    return false;
  } else {
    boolean equal = true;
    int i = 0;
    while (i <= getLastIdxRow(m1) && equal) {
      int j = 0;
      while (j <= getLastIdxCol(m1) && equal) {
        if (ELMT(m1, i, j) != ELMT(m2, i, j)) {
          equal = false;
        } else {
          j ++;
        }
      }
      i ++;
    }
    return equal;
  }
}

boolean isNotEqual(Matrix m1, Matrix m2) {
  /* Mengirimkan true jika m1 tidak sama dengan m2 */
  return !isEqual(m1, m2);
}

boolean isSizeEqual(Matrix m1, Matrix m2) {
  /* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
  return (ROWS(m1) == ROWS(m2) && COLS(m1) == COLS(m2));
}


/* ********** Operasi lain ********** */
int count(Matrix m) {
  /* Mengirimkan banyaknya elemen m */
  return ROWS(m) * COLS(m);
}


/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m) {
  /* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
  return (ROWS(m) == COLS(m));
}

boolean isSymmetric(Matrix m) {
  /* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
   if (!isSquare(m)) {
     return false;
   } else {
     boolean symmetric = true;
     int i = 0;
     while (i <= getLastIdxRow(m) && symmetric) {
       int j = 0;
       while (j <= getLastIdxCol(m) && symmetric) {
         if (ELMT(m, i, j) != ELMT(m, j, i)) {
           symmetric = false;
         } else {
           j ++;
         }
       }
       i ++;
     }
     return symmetric;
   }
}

boolean isIdentity(Matrix m) {
  /* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
   if (!isSquare(m)) {
     return false;
   } else {
     boolean identity = true;
     int i = 0;
     while (i <= getLastIdxRow(m) && identity) {
       int j = 0;
       while (j <= getLastIdxRow(m) && identity) {
         if (i != j && ELMT(m, i, j) != 0) {
           identity = false;
         } else if (i == j && ELMT(m, i, j) != 1) {
           identity = false;
         } else {
           j ++;
         }
       }
       i ++;
     }
     return identity;
   }
}

boolean isSparse(Matrix m){
  /* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
  int notZero = 0;
  int i, j;
  for (i = 0; i <= getLastIdxRow(m); i ++) {
    for (j = 0; j <= getLastIdxCol(m); j ++) {
      if (ELMT(m, i, j) != 0) {
        notZero ++;
      }
    }
  }
  return ((double) notZero <= 0.05 * (double) count(m));
}

Matrix inverse1(Matrix m) {
  /* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
  return multiplyConst(m, -1);
}

void pInverse1(Matrix *m) {
  /* I.S. m terdefinisi */
  /* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
  pMultiplyConst(m, -1);
}

float determinant(Matrix m) {
  /* Prekondisi: isSquare(m) */
  /* Menghitung nilai determinan m */
  if (count(m) == 1) {
    return ELMT(m, 0, 0);
  } else if (count(m) == 4) {
    return (ELMT(m, 0, 0) * ELMT(m, 1, 1)) - (ELMT(m, 0, 1) * ELMT(m, 1, 0));
  } else {
    int i;
    float det = 0.0;
    int sign = 1;
    for (i = 0; i <= getLastIdxRow(m); i ++) {
      Matrix minor;
      CreateMatrix(ROWS(m) - 1, COLS(m) - 1, &minor);
      int row, col;
      int j;
      for (row = 1; row <= getLastIdxRow(m); row ++) {
        j = 0;
        for (col = 0; col <= getLastIdxCol(m); col ++) {
          if (col != i) {
            ELMT(minor, row - 1, j) = ELMT(m, row, col);
            j ++;
          }
        }
      }
      det += ELMT(m, 0, i) * determinant(minor) * sign;
      sign *= -1;
    }
    return det;
  }
}


void transpose(Matrix *m) {
  /* I.S. m terdefinisi dan isSquare(m) */
  /* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
  Matrix tMat;
  CreateMatrix(ROWS(*m), COLS(*m), &tMat);
  int i, j;
  for (i = 0; i <= getLastIdxRow(*m); i ++) {
    for (j = 0; j <= getLastIdxCol(*m); j ++) {
      ELMT(tMat, i, j) = ELMT(*m, j, i);
    }
  }
  copyMatrix(tMat, m);
}
