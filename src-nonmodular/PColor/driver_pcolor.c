/*
    Driver ADT pcolor
*/
#include <stdio.h>
#include "pcolor.h"

int main()
{
    char cred, cgreen, cyellow, cblue, cmagenta, ccyan;
    scanf("%c", &cred);
    printf("%c\n", cred); // Menampilkan char dengan warna merah
    scanf("%c", &cgreen);
    printf("%c\n", cgreen); // Menampilkan char dengan warna hijau
    scanf("%c", &cyellow);
    printf("%c\n", cyellow); // Menampilkan char dengan warna kuning
    scanf("%c", &cblue);
    printf("%c\n", cblue); // Menampilkan char dengan warna biru
    scanf("%c", &cmagenta);
    printf("%c\n", cmagenta); // Menampilkan char dengan warna magenta
    scanf("%c", &ccyan);
    printf("%c\n", ccyan); // Menampilkan char dengan warna cyan
    return 0;
    // gcc -o driver_pcolor driver_pcolor.c pcolor.c
}