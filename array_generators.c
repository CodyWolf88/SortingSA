//
// Created by minec on 3/13/2026.
//

#include "array_generators.h"

int* generate_unsorted_array(int n) {
    int *y = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        y[i] = n-i;
    }
    return y;
}
