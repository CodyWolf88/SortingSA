#include <stdio.h>
#include <time.h>

typedef struct
{
    char *name;
    double (*sort_function)(int*, int);
    int active;
} SortingAlgorithm;

double insertion_sort(int x[], int n);

double selection_sort(int x[], int n);

double bubble_sort(int x[], int n);

double quick_sort_wrapper(int x[], int n);

double merge_sort_wrapper(int x[], int n);

double counting_sort(int x[], int n);

double radix_sort(int x[], int n);

double heap_sort(int x[], int n);

double tim_sort(int x[], int n);