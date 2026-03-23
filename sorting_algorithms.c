#include "sorting_algorithms.h"

#include <stdlib.h>

double insertion_sort(int x[], int n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 1; i < n; i++) {
        int aux = x[i];
        int j = i - 1;
        while (j >= 0 && aux < x[j]) {
            x[j + 1] = x[j];
            j--;
        }
        x[j+1] = aux;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) * 1000.0;
    time += (end.tv_nsec - start.tv_nsec) / 1000000.0;

    return time;
}


double selection_sort(int x[], int n) {

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (x[k] > x[j]) {
                k = j;
            }
        }
        if (k!=i) {
            int aux = x[i];
            x[i] = x[k];
            x[k] = aux;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) * 1000.0;
    time += (end.tv_nsec - start.tv_nsec) / 1000000.0;

    return time;
}


void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

int partition(int x[], int low, int high)
{
    int pivot = x[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (x[j] <= pivot)
        {
            i++;
            swap(&x[i], &x[j]);
        }
    }
    swap(&x[i + 1], &x[high]);
    return i + 1;
}

void quick_sort(int x[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(x, low, high);
        quick_sort(x, low, pi - 1);
        quick_sort(x, pi + 1, high);
    }
}

double quick_sort_wrapper(int x[], int n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    quick_sort(x, 0, n - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) * 1000.0;
    time += (end.tv_nsec - start.tv_nsec) / 1000000.0;

    return time;
}


void merge(int x[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = (int *) malloc((n1 * sizeof(int)));
    int *H = (int *) malloc((n2 * sizeof(int)));

    for (int i = 0; i < n1; i++)
    {
        L[i] = x[low + i];
    }

    for (int i = 0; i < n2; i++)
    {
        H[i] = x[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] <= H[j])
        {
            x[k] = L[i];
            i++;
        }
        else
        {
            x[k] = H[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        x[k] = L[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        x[k] = H[j];
        k++;
        j++;
    }

    free(L);
    free(H);
}

void merge_sort(int x[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        merge_sort(x, low, mid);
        merge_sort(x, mid + 1, high);
        merge(x, low, mid, high);
    }
}

double merge_sort_wrapper(int x[], int n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    merge_sort(x, 0, n - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = (end.tv_sec - start.tv_sec) * 1000.0;
    time += (end.tv_nsec - start.tv_nsec) / 1000000.0;

    return time;
}

double counting_sort(int x[], int n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (n <= 0)
    {
        return 0;
    }

    int max = x[0];
    for (int i = 1; i < n; i++)
    {
        if (x[i] > max)
        {
            max = x[i];
        }
    }

    int *count = (int*)calloc(max + 1, sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        count[x[i]]++;
    }

    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[x[i]] - 1] = x[i];
        count[x[i]]--;
    }

    free(count);
    free(output);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = (end.tv_sec - start.tv_sec) * 1000.0;
    time += (end.tv_nsec - start.tv_nsec) / 1000000.0;

    return time;
}