#include "exit_game.h"

void exitgame(boolean *end)
/* Untuk keluar dari game bila di tengah-tengah permainan */
{
    char isQuit;
    printf("Apakah Anda yakin untuk keluar dari game? (Y/N)\n");
    scanf("ENTER COMMAND : %c", &isQuit);
    while (isQuit != 'Y' || isQuit != 'N')
    {
        printf("Maaf masukan tidak dikenali, silahkan masukkan ulang command anda !\n");
        scanf("ENTER COMMAND : %c", &isQuit);
    }
    if (isQuit == 'Y')
    {
        end = true;
        printf("Terima kasih sudah bermain\n");
    }
    else if (isQuit == 'N')
    {
        end = false;
    }
}