#include "listpos.h"
#include <stdio.h>

int main() {
  ListPos l1;
  ListPos l2;
  LP_readList(&l1);

  printf("L1: ");
  LP_displayList(l1);
  LP_readList(&l2);
  printf("L2: ");
  LP_displayList(l2);
  printf("L1: ");
  LP_displayList(l1);

  printf("Length: %d\n", LP_length(l1));
  printf("Index of 3: %d\n", LP_indexOf(l1, 3));
  printf("isIDXVALID1: %d\n", LP_isIdxValid(l1, 1));
  printf("isIDXVALID101: %d\n", LP_isIdxValid(l1, 101));
  printf("isIDXEff2: %d\n", LP_isIdxEff(l1, 2));
  printf("Sama l1 l2: %d\n", LP_isListEqual(l1, l2));
  printf("Kosong: %d\n", LP_isEmpty(l1));
  ListPos l3;
  CreateListPos(&l3);
  l3 = LP_plusMinusTab(l1, l2, true);
  printf("L3: ");
  LP_displayList(l3);
  int max;
  int min;
  LP_extremes(l3, &max, &min);
  printf("L3 Max: %d \nL3 MIN: %d\n", max, min);
  printf("IsAllEven L3: %d\n", LP_isAllEven(l3));
  LP_sort(&l3, true);
  printf("L3 ascending: ");
  LP_displayList(l3);
  printf("L3 descending: ");
  LP_sort(&l3, false);
  LP_displayList(l3);
  LP_insertLast(&l3, 69);
  printf("L3: ");
  LP_displayList(l3);
  int pop;
  LP_deleteLast(&l3, &pop);
  printf("Pop: %d\n", pop);
  LP_deleteLast(&l3, &pop);
  printf("Pop: %d\n", pop);
  printf("L3: ");
  LP_displayList(l3);
  return 0;
}

// gcc -o driver driver_listpos.c listpos.c