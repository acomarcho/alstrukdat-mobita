#ifndef TIME_H
#define TIME_H

#include "../Boolean/boolean.h"

/* DEFINISI ABSTRACT DATA TYPE TIME */
typedef struct
{
    int time;
} TIME;
#define Time(P) (P).time

/* Initial Time */
#define INITIAL_TIME 1

/* KONSTRUKTOR ADT_TIME dari GAME */
void CreateTime(TIME *t);
/* Memulai waktu permainan, yaitu dengan mengeset time ke INITIAL_TIME*/

void increaseTime(TIME *t, int K);
/* Menambah waktu permainan sebesar K satuan (tergantung dengan ability yang dimiliki oleh Mobita */

#endif