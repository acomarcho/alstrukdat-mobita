#ifndef __MAP_H__
#define __MAP_H__

#include "../Matrix/matrix.h"
#include "../Listdin/listdin.h"
#include "../LinkedList/list_linked.h"
#include "../PColor/pcolor.h"

typedef struct {
  Matrix locationMatrix;
  Matrix adjacencyMatrix;
} Map;

typedef struct {
  int buffer[30];
  int length;
} adjacentLocations;

void CreateMap(int rows, int cols, ListDin l, Matrix adj, Map* m);
// Membuat map, dalam artian mengisi locationMatrix dan adjacencyMatrix pada map tersebut.

void displayMap(Map m, ListDin l, List toDoList, List inProgressList, POINT mobitaLoc);
// Menunjukkan map.

adjacentLocations getAdjacentLocations(POINT p, ListDin l, Map m);
// Mendapatkan list index-index lokasi yang bisa dicapai dari titik p.

char getLocationName(POINT p, ListDin l);
// Mendapatkan nama lokasi dari POINT p.

#endif