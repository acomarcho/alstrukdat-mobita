#include <stdio.h>
#include "list_linked.h"

int main(){
    List l;
    CreateListLinked(&l);
    displayListLinked(l);
    printf("\n");

    Item i1, i2, i3, p1;
    CreateItem(&i1, 1, 'G', 'N', 'N');
    CreateItem(&i2, 2, 'D', 'M', 'N');
    CreateItem(&i3, 2, 'F', 'H', 'V');
    // displayItem(i1);

    CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    // displayItem(p1);

    insertLastLL(&l, p1);
    displayListLinked(l);
    printf("\n");

    insertLastLL(&l, i3);
    displayListLinked(l);
    printf("\n");
    
    insertLastLL(&l, i1);
    displayListLinked(l);
    printf("\n");
    
    insertLastLL(&l, i2);
    displayListLinked(l);
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
