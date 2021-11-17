#include <stdio.h>
#include "stack.h"

// Driver ADT Stack

int main()
{
    Stack S;
    Item item;
    int masuk;
    char start, dest, jenis;
    ST_CreateStack(&S);
    if (ST_isEmpty(S) == true)
    {
        printf("Stack kosong\n");
    }
    for (int i = 0; i < 100; i++)
    {
        scanf("%d", &masuk);
        scanf("%c", &start);
        scanf("%c", &dest);
        scanf("%c", &jenis);
        CreateItem(&S, masuk, start, dest, jenis);
        ST_push(&S, item); // Menambahkan elemen k ke stack S, yaitu pada bagian stack
    }
    if (ST_isFull(S) == true)
    {
        printf("Stack penuh\n");
    }
    return 0;
    // gcc -o driver_stack driver_stack.c stack
}
