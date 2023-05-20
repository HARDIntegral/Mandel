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

void* thread_function(void* arg);

void init_thread_pool() {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }
}

uint8_t* __plot_mandel(int width, int height, int granularity) {
    uint8_t* pixels = (uint8_t*)malloc(3* width * height * sizeof(uint8_t));
    init_thread_pool();

    for (int i = 0; i < height; i++) {
        row_t* r = (row_t*)malloc(sizeof(row_t));
        r->row_ID = i;
        r->granularity = granularity;
        r->height = height;
        r->width = width;
        r->pixels = pixels;
        pthread_mutex_lock(&mutex);
        enqueue(r);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

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
        r->pixels[3 * (r->row_ID * r->width + x) + 0] = r->granularity * val % 256;
        r->pixels[3 * (r->row_ID * r->width + x) + 1] = r->granularity * val % 256;
        r->pixels[3 * (r->row_ID * r->width + x) + 2] = r->granularity * val % 256;
        pthread_mutex_unlock(&mutex);
	}
}

void* thread_function(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        row_t* r = dequeue();
        pthread_mutex_unlock(&mutex);
        if (r) 
            __calc_row(r);
    }
}