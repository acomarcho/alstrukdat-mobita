#include "wordmachine.h"

Word currentWord;

void startWord() {
  // Mulai pita karakter
  start();
  copyWord();
}

void advWord() {
  // Apabila currentChar == '\n', majukan penunjuk.
  while (currentChar == '\n') {
    adv();
  }
  copyWord();
}

void copyWord() {
  // Salin karakter-karakter pada kata, dimulai dari penunjuk awal.
  int i;
  i = 0;
  while (currentChar != '\n' && i < W_CAPACITY) {
    currentWord.contents[i] = currentChar;
    i ++;
    adv();
  }
  currentWord.length = i;
}

boolean isWordEqual(Word word, char cmp[]) {
  // Membandingkan isi word dengan cmp.
  // Cari panjang dari cmp.
  int i = 0;
  while (cmp[i] != 0) {
    i ++;
  }
  // i adalah panjang dari cmp.
  if (i != word.length) {
    return false;
  } else {
    // Compare tiap hurufnya.
    boolean diff = false;
    int j = 0;
    while (j < i && !diff) {
      if (word.contents[j] != cmp[j]) {
        diff = true;
      } else {
        j ++;
      }
    }
    return !diff;
  }
}
