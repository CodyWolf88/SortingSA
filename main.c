#include <stdio.h>

#include <string.h>
#include "array_generators.h"
#include "sorting_algorithms.h"

int* copy_array(int *x, int n) {
    int *y = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        y[i] = x[i];
    }
    return y;
}

void print_array(int x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void run_tests(int n, int runs, void(*generator)(int[], int)) {
    int *original = (int*)malloc(n * sizeof(int));
    int *copy = (int*)malloc(n * sizeof(int));

    // Memory couldn't be allocated
    if (original == NULL || copy == NULL)
    {
        return;
    }

    double insertion_sort_time = 0, selection_sort_time = 0, quick_sort_time = 0, merge_sort_time = 0, counting_sort_time = 0;

    for (int i = 0; i < runs; i++)
    {
        generator(original, n);

        memcpy(copy, original, n * sizeof(int));
        insertion_sort_time += insertion_sort(copy, n);

        memcpy(copy, original, n * sizeof(int));
        selection_sort_time += selection_sort(copy, n);

        memcpy(copy, original, n * sizeof(int));
        quick_sort_time += quick_sort_wrapper(copy, n);

        memcpy(copy, original, n * sizeof(int));
        merge_sort_time += merge_sort_wrapper(copy, n);

        memcpy(copy, original, n * sizeof(int));
        counting_sort_time += counting_sort(copy, n);
    }

    // Average time
    insertion_sort_time /= runs;
    selection_sort_time /= runs;
    quick_sort_time /= runs;
    merge_sort_time /= runs;
    counting_sort_time /= runs;

    printf("For %d lists of %d elements each the results are:\nInsertion sort - %.5lfms\nSelection sort - %.5lfms\nQuick sort - %.5lfms\nMerge sort - %.5lfms\nCounting sort - %.5lfms\n", runs, n, insertion_sort_time, selection_sort_time, quick_sort_time, merge_sort_time, counting_sort_time);

    free(original);
    free(copy);
}

int main(void) {

    run_tests(10000, 100, generate_random);

    return 0;
}