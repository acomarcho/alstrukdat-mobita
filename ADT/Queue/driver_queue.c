#include <stdio.h>
#include "queue.h"
#include "../Item/item.h"

int main(){
    Item i1, i2, i3, i4, p1;
    I_CreateItem(&i1, 1, 'G', 'N', 'N');
    I_CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    I_CreateItem(&i2, 3, 'G', 'N', 'H');
    I_CreateItem(&i3, 2, 'B', 'M', 'N');
    I_CreateItem(&i4, 1, 'M', 'B', 'H');

    Queue pesanan;
    Q_CreateQueue(&pesanan);

    Q_enqueue(&pesanan, i1);
    Q_displayQueue(pesanan);
    printf("\n");
    
    Q_enqueue(&pesanan, p1);
    Q_displayQueue(pesanan);
    printf("\n");
    
    Q_enqueue(&pesanan, i2);
    Q_displayQueue(pesanan);
    printf("\n");
    
    Q_enqueue(&pesanan, i3);
    Q_displayQueue(pesanan);
    printf("\n");
    
    Q_enqueue(&pesanan, i4);
    Q_displayQueue(pesanan);
    printf("\n");
}

// gcc -o queue driver_queue.c queue.c ../Item/item.c