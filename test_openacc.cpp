#include <openacc.h>
#include <stdio.h>

int main() {
    int NUM = 1000;
    int buf[NUM] = {};    // initialize the buffer to 0s

    #pragma acc parallel loop create(buf[NUM])
    for (int i = 0; i < NUM; ++i) {
        buf[i] = 1;
    }

    if (buf[0] == 1) {
        printf("Running on CPU\n");
    } else {
        printf("Running on GPU\n");
    }
}