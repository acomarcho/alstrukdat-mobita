/*
    Driver ADT queue
*/
#include <stdio.h>
#include "queue.h"

int main()
{
    Queue q;
    Item item;
    int masuk;
    char start, dest, jenis;
    Q_CreateQueue(&q);
    if (Q_isEmpty(q) == true)
    {
        printf("Queue Kosong\n");
    }
    for (int i = 0; i < 100; i++)
    {
        scanf("%d", &masuk);
        scanf("%c", &start);
        scanf("%c", &dest);
        scanf("%c", &jenis);
        CreateItem(&q, masuk, start, dest, jenis);
        Q_enqueue(&q, item); // Menambahkan elemen k ke stack S, yaitu pada bagian stack
    }
    Q_displayQueue(q);
    Q_dequeue(&q, &item);
    Q_displayQueue(q);
    return 0;
}
// gcc -o driver_queue driver_queue.c queue.c