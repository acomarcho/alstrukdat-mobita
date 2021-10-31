#ifndef ABILITY_H
#define ABILITY_H

#include "boolean.h"
#include "move.h"
#include "time.h"
#include "bag.h"
#include "item.h"

boolean IsSpeedBoost_Actived(BAG B, char Dest);
/* Mengirimkan true jika speed boost ability aktif */

boolean IsIncreaseCapacity_Actived(BAG B, char Dest);
/* Mengirimkan true jika ability Increase Capacity aktif */

boolean IsReturnToSender_Actived(char COMMAND);
/* Mengirimkan true jika ability Return To sender Aktif */

/* void SpeedBoost(TIME *time); */
/* Menambahkan efek Speed Boost pada time apabila Mobita Berhasil Mengantarkan barang berat (Heavy Item) */
/* Efeknya : Waktu akan bertambah 1 unit setiap Mobita berpindah 2 lokasi. Efek ini berlangsung hingga Mobita telah melewati 10 lokasi ( berlaku selama 5 unit waktu) */
/* Ability ini akan segera hilang bila terdapat Heavy Item pada Bag Mobita */

/* void IncreaseCapacity(BAG bag, int *CAPACITY); */
/* Menambah kapasitas tas sebanyak 1 satuan */

/* BONUS */
/* void ReturnToSender(TIME *time, TO_DO_LIST list); */
/* Jika ability ini digunakan dengan command "RETURN", maka item di atas tas dikembalikan ke lokasi pick up. */
/* Efeknya : 1. Pesanan akan dikembalikan ke TO DO List di urutan terakhir, 2. Time Limit yang terdapat pada pesanan dengan perishable item akan direset sebelum dikembalikan */
/* Ability ini tidak dapat diaktifkan untuk pesanan VIP Item */

#endif