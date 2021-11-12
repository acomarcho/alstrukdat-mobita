#include <stdio.h>
#include "List_linked/list_linked.h"
#include "listdin.h"
#include "point.h"
#include "Item/item.h"
#include "move/bag.h"

// Buat digabung sama fungsi main nanti 
void drop_off(List inProgressList, ListDin listBangunan, POINT mobitaLoc, BAG tas){
    int money;

    if(isEmptyLL(inProgressList)){
        printf("Tidak ada pesanan yang dapat diantarkan!\n");
    }

    else{
        Item item;
        item = NODE_INFO(LL_FIRST(inProgressList)); // Type info di node.h disini masih ElType, butuh penyesuain nanti
        if(DESTINATION(item) == getLocationName(mobitaLoc, listBangunan) && item == INFO(tas, IDX_TOP(tas))){ // getLocationName dari ADT MAP acho 
            int prize;                                                                                        // Cek Lokasi mobita serta item berada di top stack bag atau tidak
            switch (JENIS(item)){
            case 'N':
                printf("Pesanan Normal Item berhasil diantarkan.\n");
                prize = 200;
                break;
            case 'H':
                printf("Pesanan Heavy Item berhasil diantarkan.\n");
                prize = 400;
                // Ability Speed Boost aktif (belum direalisasi liat integrasinya gimana)
                break;
            case 'P':
                printf("Pesanan Perishable Item berhasil diantarkan.\n");
                prize = 400;
                IncreaseCapacity(&tas);
                break;                         
            }
            money += prize;
            printf("Uang yang didapatkan: %d Yen\n", prize);
            // Hapus dari inProgressList dan bag.
            Item tmp;
            deleteFirstLL(&inProgressList, &tmp);
            Drop_Off(&tas, &tmp);
        }

        else{
            printf("Tidak ada pesanan yang dapat diantarkan!\n");
        }
    }
}