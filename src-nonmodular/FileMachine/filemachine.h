#ifndef __MESINFILE_H_
#define __MESINFILE_H_

#include "../Boolean/boolean.h"

#define WORD_CAP 50
#define BARIS_CAP 620

typedef struct {
  char contents[WORD_CAP];
  int length;
} fWord;

typedef struct {
  fWord contents[BARIS_CAP];
  int length;
} Line;

extern boolean endLine;
extern Line currentLine;

void startLine(char namaFile[]);
/*  Inisialisasi pembacaan file. Apabila file ada, baca line pertama. */

void advLine();
/*  Meletakkan penunjuk baca ke line berikutnya. */

void copyLine();
/*  Mengakuisisi konten satu line ke dalam currentLine.
    Berhenti ketika membaca karakter \n atau sudah feof. */

void printFWord(fWord fw);
/*  Mencetak fWord fw */

void printLine(Line l);
/*  Mencetak line l */

int fWordToInt(fWord fw);
/*  Mengonversi fWord ke integer */

boolean fExists(const char *fname);
/*  Mengecek apakah file ada atau tidak */

#endif