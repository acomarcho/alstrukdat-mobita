#include <stdio.h>
#include "list_linked.h"

int main(){
    List l;
    LL_CreateList(&l);
    LL_displayList(l);
    printf("\n");

    Item i1, i2, i3, i4, p1;
    I_CreateItem(&i1, 1, 'G', 'N', 'N');
    I_CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    I_CreateItem(&i2, 3, 'G', 'N', 'H');
    I_CreateItem(&i3, 2, 'B', 'M', 'N');
    I_CreateItem(&i4, 1, 'M', 'B', 'H');

    // LL_insertLast(&l, p1);
    // LL_insertLast(&l, i3);
    // LL_insertLast(&l, i1);
    // LL_insertLast(&l, i2);
    // LL_displayList(l);
    // printf("\n");

    Queue pesanan;
    Q_CreateQueue(&pesanan);
    Q_enqueue(&pesanan, i1);
    Q_enqueue(&pesanan, p1);
    Q_enqueue(&pesanan, i2);
    Q_enqueue(&pesanan, i3);
    Q_enqueue(&pesanan, i4);
    Q_displayQueue(pesanan);
    printf("\n");

    printf("Waktu 1:\n");
    updatePesanan(1, &pesanan, &l);
    Q_displayQueue(pesanan);
    printf("\n");
    LL_displayList(l);
    printf("\n");
    
    printf("Waktu 2:\n");
    updatePesanan(2, &pesanan, &l);
    Q_displayQueue(pesanan);
    printf("\n");
    LL_displayList(l);
    printf("\n");
    
    printf("Waktu 3:\n");
    updatePesanan(3, &pesanan, &l);
    Q_displayQueue(pesanan);
    printf("\n");
    LL_displayList(l);
    printf("\n");

    // To Do        => insertLast
    displayToDo(l);
    printf("\n");
    // In Progress  => insertFirst
    displayInProgress(l);
    printf("\n");
}

// gcc -o main driver_list_linked.c list_linked.c node.c ../Item/item.c ../Queue/queue.c