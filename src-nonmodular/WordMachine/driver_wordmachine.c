#include <stdio.h>
#include "wordmachine.h"

int main() {
  // Menerima input sampai user mengirimkan "END".
  startWord();
  while (!isWordEqual(currentWord, "END")) {
    printf("Anda memasukkan: "); printWord(currentWord); printf("\n");
    advWord();
  }
  return 0;
}

// gcc -o driver driver_wordmachine.c wordmachine.c charmachine.c