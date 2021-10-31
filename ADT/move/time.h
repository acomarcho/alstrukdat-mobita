#ifndef TIME_H
#define TIME_H

#include "boolean.h"
#include <stdlib.h>

/* DEFINISI ABSTRACT DATA TYPE TIME */
typedef int ElType;
typedef struct
{
    ElType Time;
} TIME;

/* Initial Time */
#define Initial_TIME 0

/* KONSTRUKTOR ADT_TIME dari GAME */
void Start_Time(TIME *time);
/* Memulai waktu permainan, yaitu dengan mengeset time = 0 */

void increaseTime(TIME *time, int K);
/* Menambah waktu permainan sebesar K satuan (tergantung dengan ability yang dimiliki oleh Mobita */

#endif