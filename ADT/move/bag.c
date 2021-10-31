#include <stdio.h>
#include "bag.h"

void CreateBag(BAG *B)
/* Membuat Bag kosong dengan CAPACITY = 3 */
{
    CAPACITY(*B) = MinCAPACITY;
    IDX_TOP(*B) = -1;
}
boolean IsEmptyBag(BAG B)
{
    return IDX_TOP(B) == -1;
}

boolean IsFullBag(BAG B)
{
    return IDX_TOP(B) == CAPACITY(B) - 1;
}

void GetItem(BAG *B, Item item)
/* Melakukan Get Elemen dengan mengikuti Aturan LIFO (Last In First Out) */
{
    if (!IsFullBag(*B))
    {
        IDX_TOP(*B)
        ++;
        INFO(*B, IDX_TOP(*B)) = item;
    }
}
void Drop_Off(BAG *B, Item *item)
/* Prekondisi : Elemen Val pasti ada di BAG */
/* Melakukan penghapusan pada item yang ada di tas dengan mengikuti prinsip LIFO dimana item yang didrop out adalah item di tumpukan teratas */
{
    if (!IsEmptyBag(*B))
    {
        *item = INFO(*B, IDX_TOP(*B));
        IDX_TOP(*B)
        --;
    }
}
boolean IsThere_Item(char jenis_Item, BAG bag)
/* Mengecek apakah ada item tertentu di bag. Jika ya maka akan mengirimkan true, jika tidak maka akan mengirimkan false */
{
    for (int i = 0; i < CAPACITY(bag); i++)
    {
        if (JENIS(INFO(bag, i)) == jenis_Item)
        {
            return true;
        }
    }
    return false;
}
boolean iSthereDone(BAG B, char Dest)
/* Mengecek apakah terdapat item yang berhasil diantarkan ke destinationnya */
{
    for (int i = IDX_TOP(B); i >= 0; i--)
    {
        if (DESTINATION(INFO(B, i)) == Dest)
        {
            return true;
        }
    }
    return false;
}
boolean isTheItemDone(BAG B, char Jenis_Item, char Dest)
{
    for (int i = IDX_TOP(B); i >= 0; i--)
    {
        if ((DESTINATION(INFO(B, i)) == Dest) && (JENIS(INFO(B, i)) == Jenis_Item))
        {
            return true;
        }
    }
    return false;
}
int NumberOfItemDone(BAG B, char Jenis_Item, char Dest)
/* Menghitung banyaknya item berjenis tertentu berhasil diantarkan ke destination */
{
    int count = 0;
    for (int i = IDX_TOP(B); i >= 0; i--)
    {
        if ((DESTINATION(INFO(B, i)) == Dest) && (JENIS(INFO(B, i)) == Jenis_Item))
        {
            count++;
        }
    }
    return count;
}