#include <stdio.h>
#include "charmachine.h"

int main()
{
    // Menerima input dari user kemudian ditampilkan di layar
    start();
    printf("Anda memasukkan : ");
    printWord(currentChar);
    printf("\n");
    return 0;
}
// gcc -o driver driver_charmachine.c charmachine.c