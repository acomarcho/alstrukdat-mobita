/* File: node.c */
/* Implementasi Node */

#include "node.h"
#include <stdlib.h>

Address newNode(ElType val) {
    Address p = (Address) malloc(sizeof(Node));
    if (p!=NULL) {
        NODE_INFO(p) = val;
        NODE_NEXT(p) = NULL;
    }
    return p;
}