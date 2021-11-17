#include <stdlib.h>
#include "move.h"
#include "ability.h"

boolean IsSpeedBoost_Actived(BAG B, char Dest, int count_actived)
/* Mengirimkan true jika speed boost ability aktif */
{
    if (count_actived < 10 && (isTheItemDone(B, 'H', Dest) == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}
boolean IsIncreaseCapacity_Actived(BAG B, char Dest)
/* Mengirimkan true jika ability Increase Capacity aktif */
{
    if (isTheItemDone(B, 'P', Dest) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
boolean IsReturnToSender_Actived(char COMMAND[6])
/* Mengirimkan true jika ability Return To sender Aktif */
{
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
        {
            if (COMMAND[i] != 'R')
            {
                return false;
            }
        }
        else if (i == 1)
        {
            if (COMMAND[i] != 'E')
            {
                return false;
            }
        }
        else if (i == 2)
        {
            if (COMMAND[i] != 'T')
            {
                return false;
            }
        }
        else if (i == 3)
        {
            if (COMMAND[i] != 'U')
            {
                return false;
            }
        }
        else if (i == 4)
        {
            if (COMMAND[i] != 'R')
            {
                return false;
            }
        }
        else if (i == 5)
        {
            if (COMMAND[i] != 'N')
            {
                return false;
            }
        }
    }
    return true;
}
