#include "time.h"
#include <stdlib.h>

/* KONSTRUKTOR ADT_TIME dari GAME */
void Start_Time(TIME *time)
/* Memulai waktu permainan, yaitu dengan mengeset time = 0 */
{
    time = Initial_TIME;
}
void increaseTime(TIME *time, int K)
/* Menambah waktu permainan sebesar K satuan (tergantung dengan ability yang dimiliki oleh Mobita */
{
    time = time + K;
}