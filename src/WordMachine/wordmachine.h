/* File: wordmachine.h */
/* Definisi Word Engine */

#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include "../Boolean/boolean.h"
#include "charmachine.h"

#define W_CAPACITY 50
#define BLANK '\n'

typedef struct {
   char contents[W_CAPACITY]; /* container penyimpan kata, indeks yang dipakai [0..CAPACITY-1] */
   int length;
} Word;

/* Word Engine State */
extern Word currentWord;

void startWord();
/* I.S. : currentChar sembarang 
   F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void advWord();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi 
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
   Proses : Akuisisi kata menggunakan procedure copyWord */

void copyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi; 
          currentChar = BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */

boolean isWordEqual(Word word, char cmp[]);
/* Membandingkan isi word dengan cmp. */

void printWord(Word word);
/* Mencetak isi word */

int wordToInt(Word word);
/* Mengembalikan konversi word ke integer. */

#endif
