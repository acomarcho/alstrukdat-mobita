/* Realisasi ADT bacafile */

#include <stdio.h>
#include <string.h>
#include "bacafile.h"

void bacaLine(int Line)
/* Buat baca isi line */
{
    char pattern[] = "of"; // string to search for
    int count = 0;
    boolean isFound = false;
    static const char filename[] = "testing.txt";
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        char line[MAX];

        while ((fgets(line, sizeof line, file) != NULL) && (isFound == false)) /* read a line */
        {
            ++count;
            if (count == Line)
            {
                fputs(line, stdout); /* write the line */
                isFound = true;
            }
        }
        fclose(file);
        if (isFound == false)
        {
            printf("Posisi tidak ditemukan\n");
        }
    }
    else
    {
        perror(filename);
    }
}
void bacaFile()
/* Buat Baca file konfigurasi */
{
    char pattern[] = "of"; // string to search for
    int count = 0;
    static const char filename[] = "testing.txt"; /* Nama FILE Bisa disesuaikan saja */
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        char line[MAX];

        while (fgets(line, sizeof line, file) != NULL) /* read a line */
        {
            ++count;
            printf("%d. ", count);
            fputs(line, stdout); /* write the line */
        }
        printf("\n");
        fclose(file);
    }
    else
    {
        perror(filename);
    }
}
