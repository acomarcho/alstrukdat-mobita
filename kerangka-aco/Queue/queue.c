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
  /* - Index Q_HEAD bernilai Q_IDX_UNDEF */
  /* - Index Q_TAIL bernilai Q_IDX_UNDEF */
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
  /* yaitu jika index Q_HEAD bernilai 0 dan index Q_TAIL bernilai Q_CAPACITY-1 */
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
void Q_enqueue(Queue *pq, Item val) {
	/* Proses: Menambahkan val pada pq dengan aturan FIFO */
	/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
	/* F.S. val menjadi Q_TAIL yang baru, Q_IDX_TAIL "mundur".
					Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
					menjadi rata kiri untuk membuat ruang kosong bagi Q_TAIL baru  */
	if (Q_isEmpty(*pq)) {
		Q_IDX_HEAD(*pq) = 0;
		Q_IDX_TAIL(*pq) = 0;
		Q_TAIL(*pq) = val;
	} else {
		if (Q_IDX_TAIL(*pq) == Q_CAPACITY-1) {
			// Geser ke kiri!
			int i;
			for (int i = Q_IDX_HEAD(*pq); i <= Q_IDX_TAIL(*pq); i ++) {
				(*pq).buffer[i - Q_IDX_HEAD(*pq)] = (*pq).buffer[i];
			}
			Q_IDX_TAIL(*pq) -= Q_IDX_HEAD(*pq);
			Q_IDX_HEAD(*pq) = 0;
		}
		// Sudah geser. Masukkan val di tempat yang tepat.
		int idx = Q_IDX_HEAD(*pq);
		boolean found = false;
		while (idx <= Q_IDX_TAIL(*pq) && !found) {
			if (val.entryTime < (*pq).buffer[idx].entryTime) {
				found = true;
			} else {
				idx ++;
			}
		}
		if (idx == Q_IDX_TAIL(*pq) + 1) {
			// Tidak perlu penggeseran.
			(*pq).buffer[idx] = val;
		} else {
			// Perlu penggeseran dari idx sampai Q_IDX_TAIL.
			int i;
			for (int i = Q_IDX_TAIL(*pq); i >= idx; i --) {
				(*pq).buffer[i + 1] = (*pq).buffer[i];
			}
			// Penggeseran selesai.
			(*pq).buffer[idx] = val;
		}
		Q_IDX_TAIL(*pq) ++;
	}
}

void Q_dequeue(Queue *q, Item *val) {
  /* Proses: Menghapus val pada q dengan aturan FIFO */
  /* I.S. q tidak mungkin kosong */
  /* F.S. val = nilai elemen Q_HEAD pd I.S., Q_HEAD dan Q_IDX_HEAD "mundur"; 
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
    printf("[");
    for (int i = Q_IDX_HEAD(q); i <= Q_IDX_TAIL(q); i++) {
      printf("(%c -> %c)", (q).buffer[i].startLoc, (q).buffer[i].destLoc); 
      if (i < Q_IDX_TAIL(q)) {
        printf(",");
      }
    }
    printf("]");
  }
}