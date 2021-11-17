#include <stdio.h>
#include "time.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S) {
  /* Mengirim true jika H,M,S dapat membentuk T yang valid */
  /* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
  return ((H >= 0 && H <= 23) && (M >= 0 && M <= 59) && (S >= 0 && S <= 59));
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
TIME MakeTIME (int HH, int MM, int SS) {
  /* Membentuk sebuah TIME dari komponen-komponennya yang valid */
  /* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
  TIME time;
  Hour(time) = HH;
  Minute(time) = MM;
  Second(time) = SS;
  return time;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T) {
  /* I.S. : T tidak terdefinisi */
  /* F.S. : T terdefinisi dan merupakan jam yang valid */
  /* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
  /* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
  /* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
  /* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
    diulangi hingga didapatkan jam yang valid. */
  /* Contoh: 
    60 3 4
    Jam tidak valid
    1 3 4
    --> akan terbentuk TIME <1,3,4> */
  for(;;) {
    int jam, menit, detik;
    scanf("%d %d %d", &jam, &menit, &detik);
    if (IsTIMEValid(jam, menit, detik)) {
      *T = MakeTIME(jam, menit, detik);
      break;
    } else {
      printf("Jam tidak valid\n");
    }
  }
}
   
void TulisTIME (TIME T) {
  /* I.S. : T sembarang */
  /* F.S. : Nilai T ditulis dg format HH:MM:SS */
  /* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
  int hour, minute, second;
  hour = Hour(T); minute = Minute(T); second = Second(T);
  printf("%d:%d:%d", hour, minute, second);
  // if (hour < 10) {
  //   printf("0%d:", hour);
  // } else {
  //   printf("%d:", hour);
  // }

  // if (minute < 10) {
  //   printf("0%d:", minute);
  // } else {
  //   printf("%d:", minute);
  // }

  // if (second < 10) {
  //   printf("0%d", second);
  // } else {
  //   printf("%d", second);
  // }
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (TIME T) {
  /* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
  /* Rumus : detik = 3600*HH + 60*MM + SS */
  /* Nilai maksimum = 3600*23+59*60+59 */
  return 3600 * Hour(T) + 60 * Minute(T) + Second(T);
}

TIME DetikToTIME (long N) {
  /* Mengirim  konversi detik ke TIME */
  /* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
    mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
    N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
  int N1 = N % 86400;
  int jam, menit, detik;
  jam = N1 / 3600;
  // sisanya N1 % 3600
  menit = (N1 % 3600) / 60;
  // sisanya (N1 % 3600) % 60
  detik = N1 % 3600 % 60;
  return MakeTIME(jam, menit, detik);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2) {
  /* Mengirimkan true jika T1=T2, false jika tidak */
  return (TIMEToDetik(T1) == TIMEToDetik(T2));
}

boolean TNEQ (TIME T1, TIME T2) {
  /* Mengirimkan true jika T1 tidak sama dengan T2 */
  return (TIMEToDetik(T1) != TIMEToDetik(T2));
}

boolean TLT (TIME T1, TIME T2) {
  /* Mengirimkan true jika T1<T2, false jika tidak */
  return (TIMEToDetik(T1) < TIMEToDetik(T2));
}

boolean TGT (TIME T1, TIME T2) {
  /* Mengirimkan true jika T1>T2, false jika tidak */
  return (TIMEToDetik(T1) > TIMEToDetik(T2));
}

/* *** Operator aritmatika TIME *** */
TIME NextDetik (TIME T) {
  /* Mengirim 1 detik setelah T dalam bentuk TIME */
  return DetikToTIME((TIMEToDetik(T) + 1));
}

TIME NextNDetik (TIME T, int N) {
  /* Mengirim N detik setelah T dalam bentuk TIME */
  return DetikToTIME((TIMEToDetik(T) + N));
}

TIME PrevDetik (TIME T) {
  /* Mengirim 1 detik sebelum T dalam bentuk TIME */
  return DetikToTIME((TIMEToDetik(T) - 1 + 86400));
}

TIME PrevNDetik (TIME T, int N) {
  /* Mengirim N detik sebelum T dalam bentuk TIME */
  return DetikToTIME((TIMEToDetik(T) - N + 86400));
}

/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh) {
  /* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
  /* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
  if (TGT(TAw, TAkh)) {
    return (86400 - TIMEToDetik(TAw) + TIMEToDetik(TAkh));
  } else {
    return (TIMEToDetik(TAkh) - TIMEToDetik(TAw));
  }
}
