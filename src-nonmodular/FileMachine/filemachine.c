#include <stdio.h>
#include <stdlib.h>
#include "filemachine.h"

FILE *in_file;
boolean endLine;
Line currentLine;

void startLine(char namaFile[]) {
  /*  Memulai membaca line dari namaFile.
      Meletakkan penunjuk baca ke awal file. */
  in_file = fopen(namaFile, "r");
  if (in_file == NULL) {
    endLine = true;
  } else {
    endLine = false;
    copyLine();
  }
}

void advLine() {
  /*  Meletakkan penunjuk baca ke line berikutnya. */
  if (feof(in_file)) {
    endLine = true;
  } else {
    copyLine();
  }
}

void copyLine() {
  /*  Mengakuisisi konten satu line ke dalam currentLine.
      Berhenti ketika membaca karakter \n atau sudah feof. */
  char readChar;
  int wordIdx = 0;
  int lineIdx = 0;
  fWord readWord;
  readWord.length = 0;
  fscanf(in_file, "%c", &readChar);
  while(readChar == ' ' || readChar == '\n') {
    fscanf(in_file, "%c", &readChar);
  }
  while (readChar != '\n' && !feof(in_file)) {
    if (readChar != ' ') {
      readWord.contents[wordIdx] = readChar;
      readWord.length ++;
      wordIdx ++;
    } else {
      currentLine.contents[lineIdx] = readWord;
      lineIdx ++;
      readWord.length = 0;
      wordIdx = 0;
    }
    fscanf(in_file, "%c", &readChar);
  }
  currentLine.contents[lineIdx] = readWord;
  lineIdx ++;
  currentLine.length = lineIdx;
}

void printFWord(fWord fw) {
  /*  Mencetak fWord fw */
  int i;
  for (i = 0; i < fw.length; i ++) {
    printf("%c", fw.contents[i]);
  }
}

void printLine(Line l) {
  /*  Mencetak line l */
  int i;
  for (i = 0; i < l.length; i ++) {
    printFWord(l.contents[i]); printf(" ");
  }
}

int fWordToInt(fWord fw) {
  /*  Mengonversi fWord ke integer */
  int num = 0;
  if (fw.contents[0] == '-') {
    for (int i = 1; i < fw.length; i ++) {
      num = num * 10 + fw.contents[i] - 48;
    }
    return -1 * num;
  } else {
    for (int i = 0; i < fw.length; i ++) {
      num = num * 10 + fw.contents[i] - 48;
    }
    return num;
  }
}

boolean fExists(const char *fname) {
  /*  Mengecek apakah file ada atau tidak */
  FILE *file;
  if ((file = fopen(fname, "r"))) {
    fclose(file);
    return true;
  }
  return false;
}