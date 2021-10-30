#include "listdin.h"
#include <stdlib.h>

/* Konstruktor : create list kosong  */
void LD_CreateListDin(ListDin *l, int capacity) {
    /* I.S. l sembarang, capacity > 0 */
    /* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
    LD_BUFFER(*l) = (Bangunan*) malloc (sizeof(Bangunan) * capacity);
    LD_NEFF(*l) = 0;
    LD_CAPACITY(*l) = capacity;
}

Bangunan LD_CreateBangunan(char locName, int row, int col) {
    // Membentuk bangunan dengan locName dan posisi (row, col)
    // Inisialisasi titik.
    POINT point = MakePOINT(row, col);
    // Inisialisasi return value.
    Bangunan retVal;
    retVal.locName = locName;
    retVal.locCoords = point;
    return retVal;
}

void LD_dealocate(ListDin *l) {
    /* I.S. l terdefinisi; */
    /* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
    free(LD_BUFFER(*l));
    LD_NEFF(*l) = 0;
    LD_CAPACITY(*l) = 0;
}

boolean LD_isIdxEff(ListDin l, IdxType idx) {
    // Mengembalikan apakah idx merupakan index efektif.
    return (idx >= 0 && idx <= LD_NEFF(l) - 1);
}

int LD_length(ListDin l) {
    // Mengembalikan panjang dari ListDin.
    return LD_NEFF(l);
}

void LD_insertLast(ListDin *l, Bangunan val) {
    // Memasukkan val ke akhir ListDin.
    LD_ELMT(*l, LD_NEFF(*l)) = val;
    LD_NEFF(*l) ++;
}
