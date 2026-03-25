#include <stdio.h>
#include <stdlib.h>
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

void save_array_to_txt(char *file_name, int x[], int n)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", x[i]);
    }

    fclose(file);
}

int get_runs(int size)
{
    switch (size)
    {
        case 10:
            return 5000000;
        case 20:
            return 1000000;
        case 50:
            return 100000;
        case 100:
            return 10000;
        case 1000:
            return 1000;
        case 10000:
            return 100;
        case 100000:
            return 10;
        case 1000000:
            return 2;
        default:
            return 1;
    }
}

void run_tests(FILE *file, int n, int runs, void(*generator)(int[], int), char* generator_name) {
    int *original = (int*)malloc(n * sizeof(int));
    int *copy = (int*)malloc(n * sizeof(int));

    // Memory couldn't be allocated
    if (original == NULL || copy == NULL)
    {
        return;
    }

    double insertion_sort_time = 0, selection_sort_time = 0, quick_sort_time = 0, merge_sort_time = 0, counting_sort_time = 0, radix_sort_time = 0;


    for (int i = 0; i < runs; i++)
    {

        generator(original, n);

        // Save the first array
        if (i == 0)
        {
            char filename[100];

            snprintf(filename, sizeof(filename), "date_%d_%s.txt", n, generator_name);
            save_array_to_txt(filename, original, n);
        }

        // Limit O(n^2) algorithms, so we don't wait for hours
        if (n <= 100000)
        {
            memcpy(copy, original, n * sizeof(int));
            insertion_sort_time += insertion_sort(copy, n);

            memcpy(copy, original, n * sizeof(int));
            selection_sort_time += selection_sort(copy, n);
        }
        else
        {
            insertion_sort_time = -1 * runs;
            selection_sort_time = -1 * runs;
        }

        memcpy(copy, original, n * sizeof(int));
        quick_sort_time += quick_sort_wrapper(copy, n);

        memcpy(copy, original, n * sizeof(int));
        merge_sort_time += merge_sort_wrapper(copy, n);

        memcpy(copy, original, n * sizeof(int));
        counting_sort_time += counting_sort(copy, n);

        memcpy(copy, original, n * sizeof(int));
        radix_sort_time += radix_sort(copy, n);
    }

    // Average time
    insertion_sort_time /= runs;
    selection_sort_time /= runs;
    quick_sort_time /= runs;
    merge_sort_time /= runs;
    counting_sort_time /= runs;
    radix_sort_time /= runs;

    fprintf(file, "%d,%d,%s,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf\n", n, runs, generator_name, insertion_sort_time, selection_sort_time, quick_sort_time, merge_sort_time, counting_sort_time, radix_sort_time);

    //printf("For %d lists of %d elements each the results are:\nInsertion sort - %.5lfms\nSelection sort - %.5lfms\nQuick sort - %.5lfms\nMerge sort - %.5lfms\nCounting sort - %.5lfms\n", runs, n, insertion_sort_time, selection_sort_time, quick_sort_time, merge_sort_time, counting_sort_time);
    printf("Tested:\nn = %d\nruns = %d\ntype = %s\n", n, runs, generator_name);

    free(original);
    free(copy);
}

int main(void) {

    srand(time(NULL));


    FILE *file = fopen("results.txt", "w");
    if (file == NULL)
    {
        printf("Couldn't open results.txt\n");
        return 1;
    }

    fprintf(file, "Size,Runs,Generator,InsertionSort,SelectionSort,QuickSort,MergeSort,CountingSort,RadixSort\n");

    int size[] = {10, 20, 50, 100, 1000, 10000, 100000, 1000000, 10000000};
    int num_size = sizeof(size) / sizeof(size[0]);

    void(*generators[])(int[], int) = {generate_random, generate_sorted, generate_reverse_sorted, generate_nearly_sorted, generate_flat};
    char *generators_name[] = {"Random", "Sorted", "ReverseSorted", "NearlySorted", "Flat"};
    int num_generators = sizeof(generators) / sizeof(generators[0]);

    for (int i = 0; i < num_size; i++)
    {
        int n = size[i];
        int runs = get_runs(n);

        for (int j = 0; j < num_generators; j++)
        {
            run_tests(file, n, runs, generators[j], generators_name[j]);
        }
    }

    fclose(file);

    return 0;
}