#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "mandel.h"

typedef struct node {
    struct node *next;
    row_t* r;
} node_t;

typedef struct queue {
    node_t* head_node;
    node_t* tail_node;
    int size;    
} queue_t;

typedef struct node_return {
    row_t* r;
    int num_left;
} node_r;

queue_t* init_queue();
void kill_queue(queue_t* q);
void enqueue(queue_t* q, row_t* r);
node_r* dequeue(queue_t* q);

#endif /* __QUEUE_H__ */