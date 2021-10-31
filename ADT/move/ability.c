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
/* Mengirimkan true jika ability Return To sender Aktif */
{
    return (COMMAND == 'RETURN');
}
