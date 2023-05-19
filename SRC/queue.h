#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "mandel.h"

typedef struct node {
    struct node *next;
    row_t* r;
} node_t;

void enqueue(row_t* r);
row_t* dequeue();

#endif /* __QUEUE_H__ */