#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_generators.h"
#include "sorting_algorithms.h"

#define MAX_TIME_MS 10000.0

//int algorithm_active[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

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
            return 10000000;
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
        default:
            return 1;
    }
}

void run_tests(FILE *file, int n, int runs, void(*generator)(int[], int), char* generator_name, SortingAlgorithm alg[], int num_alg) {
    int *original = (int*)malloc(n * sizeof(int));
    int *copy = (int*)malloc(n * sizeof(int));
    double *results = (double*)calloc(num_alg, sizeof(double));

    // Memory couldn't be allocated
    if (original == NULL || copy == NULL || results == NULL)
    {
        return;
    }


    for (int i = 0; i < runs; i++)
    {
        generator(original, n);

        for (int j = 0; j < num_alg; j++)
        {
            if (!alg[j].active)
            {
                if (i == 0)
                {
                    results[j] = -1.0;
                }
                continue;
            }

            memcpy(copy, original, n * sizeof(int));
            double time = alg[j].sort_function(copy, n);

            if (time > MAX_TIME_MS)
            {
                alg[j].active = 0;
                results[j] = -1.0;
            }
            else
            {
                results[j] += time;
            }
        }
    }

    fprintf(file, "%d,%d,%s", n, runs, generator_name);
    for (int i = 0; i < num_alg; i++)
    {
        double avg = (results[i] < 0) ? -1.0 : results[i] / runs;
        fprintf(file, ",%.5lfms", avg);
    }
    fprintf(file, "\n");

    printf("Tested:\nn = %d\nlists = %d\ntype = %s\n", n, runs, generator_name);

    free(original);
    free(copy);
    free(results);
}

int main(void)
{
    srand(time(NULL));

    FILE *file = fopen("results.txt", "w");
    if (file == NULL)
    {
        printf("Couldn't open results.txt\n");
        return 1;
    }

    SortingAlgorithm algorithms[] = {
        {"Insertion Sort", insertion_sort, 1},
        {"Selection Sort", selection_sort, 1},
        {"Bubble Sort", bubble_sort, 1},
        {"Quick Sort", quick_sort_wrapper, 1},
        {"Merge Sort", merge_sort_wrapper, 1},
        {"Counting Sort", counting_sort, 1},
        {"Radix Sort", radix_sort, 1},
        {"Heap Sort", heap_sort, 1},
        {"Tim Sort", tim_sort, 1}
    };

    int num_alg = sizeof(algorithms) / sizeof(algorithms[0]);

    fprintf(file, "Size,Lists,Generator");
    for (int i = 0; i < num_alg; i++)
    {
        fprintf(file, ",%s", algorithms[i].name);
    }
    fprintf(file, "\n");

    int size[] = {10, 20, 50, 100, 1000, 10000, 100000, 1000000};
    int num_size = sizeof(size) / sizeof(size[0]);


    void(*generators[])(int[], int) = {generate_random, generate_sorted, generate_reverse_sorted, generate_nearly_sorted, generate_flat};
    char *generators_name[] = {"Random", "Sorted", "ReverseSorted", "NearlySorted", "Flat"};
    int num_generators = sizeof(generators) / sizeof(generators[0]);

    for (int i = 0; i < num_generators; i++)
    {
        for (int j = 0; j < num_alg; j++)
        {
            algorithms[j].active = 1;
        }

        for (int j = 0; j < num_size; j++)
        {
            int n = size[j];
            int runs = get_runs(n);

            run_tests(file, n, runs, generators[i], generators_name[i], algorithms, num_alg);
        }
    }

    fclose(file);
    return 0;
}