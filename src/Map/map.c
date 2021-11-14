#include <stdio.h>
#include "map.h"

void CreateMap(int rows, int cols, ListDin l, Matrix adj, Map* m) {
  // Isi adjacencyMatrix
  (*m).adjacencyMatrix = adj;
  // Isi locationMatrix
  Matrix locMatrix;
  CreateMatrix(rows, cols, &locMatrix);
  // Isi dulu dengan -1 (artinya tidak ada lokasi)
  for (int i = 0; i <= getLastIdxRow(locMatrix); i ++) {
    for (int j = 0; j <= getLastIdxCol(locMatrix); j ++) {
      ELMT(locMatrix, i, j) = -1;
    }
  }
  // Untuk lokasi yang sesuai dengan bangunan, simpan indexnya.
  for (int i = 0; LD_isIdxEff(l, i); i ++) {
    Bangunan b = LD_ELMT(l, i);
    int row = Absis(b.locCoords) - 1;
    int col = Ordinat(b.locCoords) - 1;
    ELMT(locMatrix, row, col) = i;
  }
  // Set locationMatrix menjadi locMatrix.
  (*m).locationMatrix = locMatrix;
}

void displayMap(Map m, ListDin l, List toDoList, List inProgressList, POINT mobitaLoc) {
  for (int i = 0; i < ROWS(m.locationMatrix) + 2; i ++) {
    for (int j = 0; j < COLS(m.locationMatrix) + 2; j ++) {
      if (i == 0 || i == ROWS(m.locationMatrix) + 1) { // Baris pertama atau baris terakhir, cetak *
        printf("*");
      } else {
        if (j == 0 || j == COLS(m.locationMatrix) + 1) { // Kolom pertama atau kolom terakhir, cetak *
          printf("*");
        } else {
          // Cek apakah lokasi valid
          if (ELMT(m.locationMatrix, i-1, j-1) != -1) {
            // Lokasi valid, cetak nama lokasi.
            Bangunan lokasi = LD_ELMT(l, ELMT(m.locationMatrix, i-1, j-1));
            boolean isLokasiMobita = false;
            boolean isLokasiDropOff = false;
            boolean isLokasiPickUp = false;
            boolean isLokasiDest = false;
            isLokasiMobita = lokasi.locName == getLocationName(mobitaLoc, l);
            // Cek apakah lokasi drop off.
            if (!LL_isEmpty(inProgressList)) {
              isLokasiDropOff = NODE_INFO(LL_FIRST(inProgressList)).dest == lokasi.locName;
            }
            // Cek apakah lokasi pick up.
            Address p = LL_FIRST(toDoList);
            while (p != NULL && !isLokasiPickUp) {
              if (NODE_INFO(p).start == lokasi.locName) {
                isLokasiPickUp = true;
              } else {
                p = NODE_NEXT(p);
              }
            }
            // Cek apakah lokasi destination.
            adjacentLocations dest = getAdjacentLocations(mobitaLoc, l, m);
            int ptr = 0;
            while (ptr < dest.length && !isLokasiDest) {
              if (LD_ELMT(l, dest.buffer[ptr]).locName == lokasi.locName) {
                isLokasiDest = true;
              } else {
                ptr ++;
              }
            }
            if (isLokasiMobita) {
              print_yellow(lokasi.locName);
            } else if (isLokasiDropOff) {
              print_blue(lokasi.locName);
            } else if (isLokasiPickUp) {
              print_red(lokasi.locName);
            } else if (isLokasiDest) {
              print_green(lokasi.locName);
            } else {
              printf("%c", lokasi.locName);
            }
          } else {
            printf(" ");
          }
        }
      }
    }
    printf("\n");
  }
}

adjacentLocations getAdjacentLocations(POINT p, ListDin l, Map m) {
  // Mendapatkan list index-index lokasi yang bisa dicapai dari titik p.
  // Cari index pada l yang mengandung POINT p.
  int LD_idx = 0;
  while(LD_idx < LD_length(l) && !EQ(p, LD_ELMT(l, LD_idx).locCoords)) {
    LD_idx ++;
  }
  // Inisialisasi hasil return.
  adjacentLocations retVal;
  // LD_idx ditemukan.
  int bufferIdx = 0;
  // Loop di adjacencyMatrix pada baris ke-LD_idx, proses adjacentLocations.
  Matrix adjMat = m.adjacencyMatrix;
  for (int j = 0; j < COLS(adjMat); j ++) {
    if (ELMT(adjMat, LD_idx, j) == 1) {
      retVal.buffer[bufferIdx] = j;
      bufferIdx ++;
    }
  }
  retVal.length = bufferIdx;
  return retVal;
}

char getLocationName(POINT p, ListDin l) {
  // Mendapatkan nama lokasi dari POINT p.
    // Cari index pada l yang mengandung POINT p.
  int LD_idx = 0;
  while(LD_idx < LD_length(l) && !EQ(p, LD_ELMT(l, LD_idx).locCoords)) {
    LD_idx ++;
  }
  // LD_idx ditemukan.
  return LD_ELMT(l, LD_idx).locName;
}