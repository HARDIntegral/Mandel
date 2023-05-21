#include <stdlib.h>

#include "queue.h"

queue_t* init_queue() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->head_node = NULL;
    q->tail_node = NULL;
    q->size = 0;
    return q;
}

void enqueue(queue_t* q, row_t* r) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->r = r;
    new_node->next = NULL;
    if (q->tail_node == NULL) 
        q->head_node = new_node;
    else 
        q->tail_node->next = new_node;
    q->tail_node = new_node;
    q->size++;
}

node_r* dequeue(queue_t* q) {
    node_r* result = (node_r*)malloc(sizeof(node_r));

    if (q->head_node == NULL)
        return NULL;
    result->r = q->head_node->r;
    result->num_left = q->size - 1;
    q->size--;

    node_t* tmp = q->head_node;
    q->head_node = q->head_node->next;
    if (q->head_node == NULL)
        q->tail_node = NULL;
    free(tmp);

    return result;
}