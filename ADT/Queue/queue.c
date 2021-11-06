/*
  NIM: 13520119
  Nama: Marchotridyo
  Tanggal: 5 Oktober
  Topik Praktikum: ADT Queue
  Deskripsi: Pra-praktikum
*/

#include <stdio.h>
#include "queue.h"

/* *** Kreator *** */
void Q_CreateQueue(Queue *q) {
  /* I.S. sembarang */
  /* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
  /* - Index head bernilai Q_IDX_UNDEF */
  /* - Index tail bernilai Q_IDX_UNDEF */
  /* Proses : Melakukan alokasi, membuat sebuah q kosong */
  Q_IDX_HEAD(*q) = Q_IDX_UNDEF;
  Q_IDX_TAIL(*q) = Q_IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean Q_isEmpty(Queue q) {
  /* Mengirim true jika q kosong: lihat definisi di atas */
  return (Q_IDX_HEAD(q) == Q_IDX_UNDEF && Q_IDX_TAIL(q) == Q_IDX_UNDEF);
}
boolean Q_isFull(Queue q) {
  /* Mengirim true jika tabel penampung elemen q sudah penuh */
  /* yaitu jika index head bernilai 0 dan index tail bernilai Q_CAPACITY-1 */
  return (Q_IDX_HEAD(q) == 0 && Q_IDX_TAIL(q) == Q_CAPACITY-1);
}

int Q_length(Queue q) {
  /* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
  if (Q_isEmpty(q)) {
    return 0;
  } else {
    return Q_IDX_TAIL(q) - Q_IDX_HEAD(q) + 1;
  }
}

/* *** Primitif Add/Delete *** */
void Q_enqueue(Queue *q, Item val) {
/* Proses: Menambahkan val pada q sesuai waktu yang dimiliki */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, Q_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
  if (Q_IDX_HEAD(*q) == Q_IDX_UNDEF){
      Q_IDX_HEAD(*q) = 0;
      Q_HEAD(*q) = val;
      Q_IDX_TAIL(*q) = 0;
  } else {
      // menyimpan index head dan tail
      int n = Q_IDX_TAIL(*q), firstHead = Q_IDX_HEAD(*q);
      // Mencari posisi yang pas untuk val
      while ((Q_IDX_TAIL(*q) >= 0) && MASUK(Q_TAIL(*q)) > MASUK(val) ){
          Q_IDX_TAIL(*q)--;
      }
      // udah ketemu posisi yang pas, sekarang geser dari Q_idx_tail+1 sampai n, 1 tempat ke belakang
      int posisi = Q_IDX_TAIL(*q) + 1;
      // posisikan head di 2 urutan paling belakang untuk menggeser
      Q_IDX_HEAD(*q)=n;
      // posisikan tail di paling belakang
      Q_IDX_TAIL(*q) = n+1;
      while (Q_IDX_HEAD(*q) >= posisi){
          Q_TAIL(*q) = Q_HEAD(*q);
          Q_IDX_HEAD(*q)--;
          Q_IDX_TAIL(*q)--;
      }
      // Sudah digeser
      // Lakukan penyisipan
      Q_TAIL(*q) = val;
      // kembalikan posisi head dan atur posisi tail ke n+1
      Q_IDX_HEAD(*q) = firstHead;
      Q_IDX_TAIL(*q) = n+1;
  }
}

void Q_dequeue(Queue *q, Item *val) {
  /* Proses: Menghapus val pada q dengan aturan FIFO */
  /* I.S. q tidak mungkin kosong */
  /* F.S. val = nilai elemen HEAD pd I.S., HEAD dan Q_IDX_HEAD "mundur"; 
          q mungkin kosong */
  *val = Q_HEAD(*q);
  if (Q_IDX_HEAD(*q) == Q_IDX_TAIL(*q)) {
    Q_IDX_HEAD(*q) = Q_IDX_UNDEF;
    Q_IDX_TAIL(*q) = Q_IDX_UNDEF;
  } else {
    Q_IDX_HEAD(*q) ++;
  }
}

/* *** Display Queue *** */
void Q_displayQueue(Queue q) {
  /* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara kurung 
    siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
    karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
  /* I.S. q boleh kosong */
  /* F.S. Jika q tidak kosong: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika Queue kosong : menulis [] */
  if (Q_isEmpty(q)) {
    printf("[]");
  } else {
    while (Q_IDX_HEAD(q) <= Q_IDX_TAIL(q)){
          printf("%d. %c -> %c ", Q_IDX_HEAD(q)+1, START(Q_HEAD(q)), DESTINATION(Q_HEAD(q)));
          switch (JENIS(Q_HEAD(q))){
          case 'N':
              printf("(Normal Item)\n");
              break;
          case 'H':
              printf("(Heavy Item)\n");
              break;
          case 'P':
              printf("(Perishable Item)\n");
              break;
          case 'V':
              printf("(VVIP Item)\n");
              break;
          default:
              break;
          }
          Q_IDX_HEAD(q)++;
      }
  }
}