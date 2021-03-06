#include "matrix.h"
#include "../Boolean/boolean.h"
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

MatrixEl getElmtDiagonal(Matrix m, Index i) {
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

