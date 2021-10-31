#include <stdio.h>
#include <stdlib.h>
#include "mesinfile.h"

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