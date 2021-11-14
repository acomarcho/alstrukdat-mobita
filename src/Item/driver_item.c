#include <stdio.h>
#include "item.h"

int main(){
    Item i1, p1;
    CreateItem(&i1, 1, 'G', 'N', 'N');
    displayItem(i1);

    CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    displayItem(p1);
}

// gcc -o item item.c driver_item.c