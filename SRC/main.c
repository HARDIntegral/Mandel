#include <stdio.h>
#include "BMPHandler.h"
#include "mandel.h"

int main(int argc, char **argv) {
    printf("Hello, world!\n");
    int dims[2] = {64, 36};
    createImage(
        "test.bmp", dims[0], dims[1],
        __plot_mandel(dims[0], dims[1], 100)
    );

    return 0;
}
