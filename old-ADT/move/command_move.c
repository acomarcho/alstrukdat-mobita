#include <stdio.h>
#include "time.h"
#include "ability.h"
#include "move.h"
#include "bacafile.h"

int main()
{
    TIME time;
    char POS, POS_Head, POS_Moved;
    POINT Coor, Coor_Head, Coor_Moved;
    BAG B;
    char Dest;
    int i = 0;
    int pilih_pos = 0;
    int count_actived = 0;
    boolean is_command = true;
    StartPos(&POS, POS_Head);         /* Mengeset posisi awal (Nama Koordinat) dengan headquarter dimana Pos_Head diambil dari konfigurasi file */
    StartKoordinat(&Coor, Coor_Head); /* Mengeset Koordinat awal dengan koordinat headquarter, dimana Coor_Head diambil dari Konfigurasi File */
    Start_Time(&time);
    printf("Waktu: ", time);
    char Command[20];
    while (pilih_pos == 0)
    {
        scanf("ENTER COMMAND: %s", &Command);
        while (i < 4 && is_command == true)
        {
            if (i == 0)
            {
                if (Command[i] != 'M')
                {
                    is_command = false;
                }
            }
            else if (i == 1)
            {
                if (Command[i] != 'O')
                {
                    is_command = false;
                }
            }
            else if (i == 2)
            {
                if (Command[i] != 'V')
                {
                    is_command = false;
                }
            }
            else if (i == 3)
            {
                if (Command[i] != 'E')
                {
                    is_command = false;
                }
            }
            i++;
        }
        if (is_command == true)
        {
            printf("Posisi yang dapat dicapai: \n");
            bacaFile();
            scanf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
            scanf("ENTER COMMAND: %d", &pilih_pos);
            if (pilih_pos != 0)
            {
                MOVEPos(&POS, POS_Moved);
                MOVEKoordinat(&Coor, Coor_Moved);
                if (iSthereDone(B, POS) == true)
                {
                    if (IsSpeedBoost_Actived(B, POS, count_actived) == true)
                    {
                        if (count_actived % 2 == 1)
                        {
                            increaseTime(&time, 1);
                        }
                    }
                    if (IsIncreaseCapacity_Actived(B, POS) == true)
                    {
                        IncreaseCapacity(&B);
                    }
                }
                if (count_actived == 10)
                { /* Kalo dia sudah pindah lebih dari 10 lokasi */
                    count_actived = 0;
                }
                else
                { /* Kalo dia pindah lokasi kurang dari 10 kali */
                    count_actived++;
                }
            }
            printf("Mobita sekarang berada di titik ");
            bacaLine(pilih_pos);
            printf("!\n");
            printf("Waktu: %d\n", time);
        }
        if (pilih_pos != 0 && Command != "RETURN")
        {
            scanf("ENTER COMMAND: %s", &Command);
        }
    }
    if (IsReturnToSender_Actived(Command) == true)
    {
        /* Item tas kembali ke lokasi pick up */
        /* Nunggu yang buat pick up dulu */
    }
    return 0;
}
