#ifndef __MANDELBROT_H_
#define __MANDELBROT_H_

#include <stdint.h>

typedef struct row {
    int row_ID;
    int granularity;
    int height;
    int width;
    uint8_t* pixels;
} row_t;

uint8_t* __plot_mandel(int width, int height, int granularity);

#endif /* __MANDELBROT_H_ */