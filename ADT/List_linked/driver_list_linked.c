#include <stdio.h>
#include "list_linked.h"

int main(){
    List l;
    LL_CreateList(&l);
    LL_displayList(l);
    printf("\n");

    Item i1, i2, i3, p1;
    I_CreateItem(&i1, 1, 'G', 'N', 'N');
    I_CreateItem(&i2, 2, 'D', 'M', 'N');
    I_CreateItem(&i3, 2, 'F', 'H', 'V');
    // displayItem(i1);

    I_CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    // displayItem(p1);

    LL_insertLast(&l, p1);
    LL_displayList(l);
    printf("\n");

    LL_insertLast(&l, i3);
    LL_displayList(l);
    printf("\n");
    
    LL_insertLast(&l, i1);
    LL_displayList(l);
    printf("\n");
    
    LL_insertLast(&l, i2);
    LL_displayList(l);
    printf("\n");

    // Catatan : Belum ada queue di sini, jadi belum diurutkan berdasarkan waktu
    // To Do        => insertLast
    displayToDo(l);
    printf("\n");
    // In Progress  => insertFirst
    displayInProgress(l);
    printf("\n");
}

// gcc -o main driver_list_linked.c list_linked.c node.c ../Item/item.c