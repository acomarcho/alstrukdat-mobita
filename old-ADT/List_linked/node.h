#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "../Item/item.h"

typedef Item ElType;
typedef struct node* Address;
typedef struct node {
    ElType info;
    Address next;
} Node;

#define NODE_INFO(p) (p)->info
#define NODE_NEXT(p) (p)->next

Address newNode(ElType val);


#endif
