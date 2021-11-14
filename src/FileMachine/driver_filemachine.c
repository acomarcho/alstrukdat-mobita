#include <stdio.h>
#include "filemachine.h"

int main() {
  /* Mengeluarkan isi file konfigurasi */
  startLine("konfigurasi.txt");
  printf(">> %d\n", fWordToInt(currentLine.contents[0]) + fWordToInt(currentLine.contents[1])); /* Seharusnya keluar 25 */
  while (!endLine) {
    printLine(currentLine); printf("\n");
    advLine();
  }
  return 0;
}

// gcc -o driver driver_filemachine.c filemachine.c