#include <stdio.h>
#include "item.h"

void I_CreateItem(Item *i, int masuk, char start, char dest, char jenis){
    MASUK(*i) = masuk;
    START(*i) = start;
    DESTINATION(*i) = dest;
    JENIS(*i) = jenis;
    switch (jenis){
    case 'N':
        NILAI(*i) = 200;
        break;
    case 'H':
        NILAI(*i) = 400;
        break;
    case 'V':
        NILAI(*i) = 600;
        break;
    default:
        break;
    }
}
/* Proses: Mendeklarasikan Item */
/* I.S. sembarang */
/* F.S. terbentuk sebuah item */

void I_CreatePerishableItem(Item *i, int masuk, char start, char dest, int hangus){
    MASUK(*i) = masuk;
    START(*i) = start;
    DESTINATION(*i) = dest;
    JENIS(*i) = 'P';
    NILAI(*i) = 400;
    HANGUS(*i) = hangus;
    SISA_WAKTU(*i) = hangus;
}
/* Proses: Mendeklarasikan Perishable Item */
/* I.S. sembarang */
/* F.S. terbentuk sebuah perishable item */


void I_displayItem(Item i){
    printf("%d : %c -> %c ", MASUK(i), START(i), DESTINATION(i));

    switch (JENIS(i)){
    case 'N':
        printf("(Normal Item)\n");
        break;
    case 'H':
        printf("(Heavy Item)\n");
        break;
    case 'P':
        printf("(Perishable Item, sisa waktu %d)\n", SISA_WAKTU(i));
        break;
    case 'V':
        printf("(VVIP Item)\n");
        break;
    default:
        break;
    }
}
/* Proses: Menampilkan sebuah item dengan format "Waktu : Asal -> Tujuan (Jenis Item)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

void displayToDoItem(Item i){
    printf("%c -> %c ", START(i), DESTINATION(i));

    switch (JENIS(i)){
    case 'N':
        printf("(Normal Item)\n");
        break;
    case 'H':
        printf("(Heavy Item)\n");
        break;
    case 'P':
        printf("(Perishable Item, sisa waktu %d)\n", SISA_WAKTU(i));
        break;
    case 'V':
        printf("(VVIP Item)\n");
        break;
    default:
        break;
    }
}
/* Proses: Menampilkan sebuah item dengan format "No. Asal -> Tujuan (Jenis Item)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

void displayInProgItem(Item i){
    switch (JENIS(i)){
    case 'N':
        printf("Normal Item ");
        break;
    case 'H':
        printf("Heavy Item ");
        break;
    case 'P':
        printf("Perishable Item ");
        break;
    case 'V':
        printf("VVIP Item ");
        break;
    default:
        break;
    }

    printf("(Tujuan: %c)\n", DESTINATION(i));
}
/* Proses: Menampilkan sebuah item dengan format "No. Jenis Item (Tujuan: Tujuan)" */
/* I.S. i terdefinisi */
/* F.S. detail item sudah ditampilkan */

boolean I_isItemSame(Item i1, Item i2){
    if (MASUK(i1) != MASUK(i2)) return false;
    if (JENIS(i1) != JENIS(i2)) return false;
    if (START(i1) != START(i2)) return false;
    if (DESTINATION(i1) != DESTINATION(i2)) return false;
    if (SISA_WAKTU(i1) != SISA_WAKTU(i2)) return false;

    return true;
}
/* Proses: Membandingkan kedua kesamaan antara 2 item */
/* I.S. i1 dan i2 terdefinisi */
/* F.S. Mengeluarkan true jika i1 == i2. False jika sebaliknya */