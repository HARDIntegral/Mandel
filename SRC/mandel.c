#include <malloc.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "mandel.h"
#include "queue.h"

#define THREAD_POOL_SIZE 16
pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

queue_t* w_q;

void* thread_function(void* arg);

void init_thread_pool() {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }
}

void kill_thread_pool() {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_kill(thread_pool[i], NULL);
    }
}

uint4_t** __plot_mandel(int width, int height, int granularity) {
    uint4_t** pixels = (uint4_t**)malloc(width * height * sizeof(uint4_t*));
    w_q = init_queue();
    init_thread_pool();

    for (int i = 0; i < height; i++) {
        row_t* r = (row_t*)malloc(sizeof(row_t));
        r->row_ID = i;
        r->granularity = granularity;
        r->height = height;
        r->width = width;
        r->pixels = pixels;
        pthread_mutex_lock(&mutex);
        enqueue(w_q, r);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    while (w_q->size > 0) {
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    
    kill_queue(w_q);
    kill_thread_pool();

    return pixels;
}

void __calc_row(row_t* r) {
    double complex comp;
    __imag__ comp = -1 + (r->row_ID / (double)r->height) * 2;
    for (int x = 0; x < r->width; x++) {
		int val = 0;
		__real__ comp = -2 + (x / (double)r->width)*3;
		for(double complex z = 0 + 0 * I; cabs(z) < 2 && val < r->granularity; val++)
			z = z*z + comp;
        pthread_mutex_lock(&mutex);
        uint4_t* val4 = (uint4_t*)malloc(sizeof(uint4_t));
        val4->value = r->granularity * val % 16;
        r->pixels[r->row_ID * r->width + x] = *val4;
        pthread_mutex_unlock(&mutex);
	}
}

void* thread_function(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        node_r* n_r = dequeue(w_q);
        pthread_mutex_unlock(&mutex);
        if (n_r->num_left >= 0) {
            __calc_row(n_r->r);
            free(n_r->r);
            free(n_r);
        }
        else
            break;
    }
}