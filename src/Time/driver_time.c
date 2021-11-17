#include <stdio.h>
#include "time.h"

// Driver Time, membuat time t kemudian menambahkannya sebesar k yang kemudian hasilnya akan ditampilkan ke layar

int main()
{
    TIME t;
    CreateTime(&t);
    int k;
    scanf("%d", &k);
    increaseTime(&t, k);
    printf("%d", t);
    return 0;
}
// gcc -o driver_time driver_time.c time.c