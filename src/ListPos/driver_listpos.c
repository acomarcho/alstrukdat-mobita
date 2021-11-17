#include <stdio.h>
#include "listpos.h"

int main() {
    ListPos l;
    CreateListPos(&l);
    showInventory(l);
    printf("\n%d\n\n", getEmptySlot(l));
    addToInventory(&l, 1);
    showInventory(l);
    printf("\n");
    useFromInventory(&l, 0);
    printf("\n");
    showInventory(l);
    return 0;
}

// gcc -o main driver_listpos.c listpos.c