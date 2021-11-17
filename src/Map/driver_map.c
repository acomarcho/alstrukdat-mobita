/*
    Driver ADT Map
*/
#include <stdio.h>
#include "map.h"

int main()
{
    int Row, Col;
    ListDin l;
    Matrix adj;
    Map m;
    Bangunan val;
    // Input mobita location
    POINT mobitaLoc;
    BacaPOINT(&mobitaLoc);
    // Create ListLinked
    List toDolist, inProgressList;
    CreateListLinked(&inProgressList);
    CreateListLinked(&toDolist);
    // Create item
    Item i1, i2, i3, p1;
    CreateItem(&i1, 1, 'G', 'N', 'N');
    CreateItem(&i2, 2, 'D', 'M', 'N');
    CreateItem(&i3, 2, 'F', 'H', 'V');
    CreatePerishableItem(&p1, 10, 'P', 'Q', 20);
    // Insert inProgressList and toDolist
    insertLastLL(&inProgressList, p1);
    insertLastLL(&inProgressList, i3);
    insertLastLL(&toDolist, i1);
    insertLastLL(&toDolist, i2);
    // Create Matrix
    char locname;
    int NrowB, NcolB;
    CreateMatrix(Row, Col, &adj);
    readMatrix(&adj, Row, Col);
    if (isIdxValid(2, 4))
    {
        printf("Indes valid\n");
    }
    int capacity;
    scanf("%d", &capacity);
    LD_CreateListDin(&l, capacity);
    scanf("%c %d %d", &locname, &NrowB, &NcolB);
    val = LD_CreateBangunan(locname, NrowB, NcolB);
    LD_insertLast(&l, val);
    scanf("%c %d %d", &locname, &NrowB, &NcolB);
    val = LD_CreateBangunan(locname, NrowB, NcolB);
    LD_insertLast(&l, val);
    CreateMap(Row, Col, l, adj, &m);
    displayMap(m, l, toDolist, inProgressList, mobitaLoc);
    adjacentLocations adjacentLoc;
    POINT P;
    BacaPOINT(&P);
    // Get location Name
    adjacentLoc = getAdjacentLocations(P, l, m);
    printf("%c\n", getLocationName(P, l));
    return 0;
    // gcc -o driver_map driver_map.c map.c
}