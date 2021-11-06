#include <stdio.h>
#include "item.h"

int main(){
    Item i1, p1;
    I_CreateItem(&i1, 1, 'G', 'N', 'N');
    I_displayItem(i1);

    I_CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    I_displayItem(p1);
}

// gcc -o item item.c driver_item.c