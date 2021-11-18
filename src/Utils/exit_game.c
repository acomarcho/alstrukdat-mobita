#include "exit_game.h"

void exitgame(boolean *end)
/* Untuk keluar dari game bila di tengah-tengah permainan */
{
    // char isQuit;
    printf("======================================================================\n\n");
    printf("Apakah Anda yakin untuk keluar dari game? (Y/N)\n\n");
    printf("        ENTER COMMAND: ");
    advWord();
    printf("\n");
    printf("======================================================================\n\n");
    while (!(isWordEqual(currentWord, "Y") || isWordEqual(currentWord, "N")))
    {
        printf("Maaf masukan tidak dikenali, silahkan masukkan ulang command anda!\n");
        exitgame(end);
        return;
    }
    if (isWordEqual(currentWord, "Y"))
    {
        
        *end = true;
        printf("[]=====================================[]\n");
        printf("||      Terima kasih sudah bermain     ||\n");
        printf("[]=====================================[]\n");
    }
    else if (isWordEqual(currentWord, "N"))
    {
        *end = false;
    }
}