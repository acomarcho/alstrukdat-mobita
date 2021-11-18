#include <stdio.h>
#include "point.h"
#include "math.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y) {
  /* Membentuk sebuah POINT dari komponen-komponennya */
  // ALGORITMA
  POINT p;
  Absis(p) = X;
  Ordinat(p) = Y;
  return p;
}
              
/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2) {
  /* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
  // ALGORITMA
  return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ (POINT P1, POINT P2) {
  /* Mengirimkan true jika P1 tidak sama dengan P2 */
  // ALGORITMA
  return ((Absis(P1) != Absis(P2)) || (Ordinat(P1) != Ordinat(P2)));
}