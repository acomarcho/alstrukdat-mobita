#ifndef ABILITY_H
#define ABILITY_H

#include "boolean.h"
#include "move.h"
#include "time.h"
#include "bag.h"
#include "item.h"

boolean IsSpeedBoost_Actived(BAG B, char Dest, int count_actived);
/* Mengirimkan true jika speed boost ability aktif */

boolean IsIncreaseCapacity_Actived(BAG B, char Dest);
/* Mengirimkan true jika ability Increase Capacity aktif */

boolean IsReturnToSender_Actived(char COMMAND[6]);
/* Mengirimkan true jika ability Return To sender Aktif */

#endif
