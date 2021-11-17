#include <stdio.h>
#include "listdin.h"

int main(){
    ListDin l;
    int x;
    scanf("%d", &x);
    LD_CreateListDin(&l, x);
    printf("Length: %d\n", LD_length(l));
    Bangunan b;
    b = LD_CreateBangunan('8', 1, 2);
    LD_insertLast(&l, b);
    printf("Length: %d\n", LD_length(l));
    printf("isIDXVALID: %d\n", LD_isIdxEff(l, 0)); // cek apakah idx 0 efektif
    LD_dealocate(&l);
    return 0;
}

// gcc -o driver driver_listdin.c listdin.c ../Point/point.c