#include "time.h"

/* KONSTRUKTOR ADT_TIME dari GAME */
void CreateTime(TIME *t)
{
  /* Memulai waktu permainan, yaitu dengan mengeset time = 0 */
  Time(*t) = INITIAL_TIME;
}

void increaseTime(TIME *t, int K)
/* Menambah waktu permainan sebesar K satuan (tergantung dengan ability yang dimiliki oleh Mobita */
{
  Time(*t) += K;
}