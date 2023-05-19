#include <stdlib.h>

#include "queue.h"

node_t* head_node = NULL;
node_t* tail_node = NULL;

void enqueue(row_t* r) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->r = r;
    new_node->next = NULL;
    if (tail_node == NULL) 
        head_node = new_node;
    else 
        tail_node->next = new_node;
    tail_node = new_node;
}

row_t* dequeue() {
    if (head_node == NULL)
        return NULL;
    row_t* result = head_node->r;
    node_t* tmp = head_node;
    head_node = head_node->next;
    if (head_node == NULL)
        tail_node = NULL;
    free(tmp);
    return result;
}