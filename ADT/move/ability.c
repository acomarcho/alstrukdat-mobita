#include <stdlib.h>
#include "move.h"
#include "ability.h"

boolean IsSpeedBoost_Actived(BAG B, char Dest)
/* Mengirimkan true jika speed boost ability aktif */
{
    return (isTheItemDone(B, 'H', Dest) == true);
}
boolean IsIncreaseCapacity_Actived(BAG B, char Dest)
/* Mengirimkan true jika ability Increase Capacity aktif */
{
    return (isTheItemDone(B, 'P', Dest) == true);
}
boolean IsReturnToSender_Actived(char COMMAND)
{
    return (COMMAND == 'RETURN');
}
/* void SpeedBoost(TIME *time) */
/* Menambahkan efek Speed Boost pada time apabila Mobita Berhasil Mengantarkan barang berat (Heavy Item) */
/* Efeknya : Waktu akan bertambah 1 unit setiap Mobita berpindah 2 lokasi. Efek ini berlangsung hingga Mobita telah melewati 10 lokasi ( berlaku selama 5 unit waktu) */
/* Ability ini akan segera hilang bila terdapat Heavy Item pada Bag Mobita */
/* {
    while ()
        *time = increaseTime(time, 0.5);
} */

/* void IncreaseCapacity(BAG bag, int *CAPACITY) */
/* Menambah kapasitas tas sebanyak 1 satuan */
/* {
    *CAPACITY()
} */

/* void ReturnToSender(TIME *time, TO_DO_LIST list)
{
} */