#include "sorting_algorithms.h"
#include <stdlib.h>
#include <string.h>

double insertion_sort(int x[], int n)
{
    clock_t start = clock();

    for (int i = 1; i < n; i++) {
        int aux = x[i];
        int j = i - 1;
        while (j >= 0 && aux < x[j]) {
            x[j + 1] = x[j];
            j--;
        }
        x[j+1] = aux;
    }

    clock_t stop = clock();

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}


double selection_sort(int x[], int n)
{
    clock_t start = clock();

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

    clock_t stop = clock();

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}


void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

int partition(int x[], int low, int high)
{
    int random_index = low + rand() % (high - low + 1);
    swap(&x[random_index], &x[high]);

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
        int pivot = partition(x, low, high);
        quick_sort(x, low, pivot - 1);
        quick_sort(x, pivot + 1, high);
    }
}

double quick_sort_wrapper(int x[], int n)
{
    clock_t start = clock();

    quick_sort(x, 0, n - 1);

    clock_t stop = clock();

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}


void merge(int x[], int temp[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (x[i] <= x[j])
        {
            temp[k++] = x[i++];
        }
        else
        {
            temp[k++] = x[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = x[i++];
    }

    while (j <= high)
    {
        temp[k++] = x[j++];
    }

    for (int p = low; p <= high; p++)
    {
        x[p] = temp[p];
    }

}

void merge_sort(int x[], int temp[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        merge_sort(x, temp, low, mid);
        merge_sort(x, temp, mid + 1, high);
        merge(x, temp, low, mid, high);
    }
}

double merge_sort_wrapper(int x[], int n)
{
    int *temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL)
    {
        return 0;
    }

    clock_t start = clock();

    merge_sort(x, temp, 0, n - 1);

    clock_t stop = clock();

    free(temp);

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}


double counting_sort(int x[], int n)
{
    clock_t start = clock();

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

    memcpy(x, output, n * sizeof(int));

    free(count);
    free(output);

    clock_t stop = clock();

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}


void counting_sort_radix(int x[], int n, int exp)
{
    int *output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++)
    {
        count[(x[i]/ exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(x[i] / exp) % 10] - 1] = x[i];
        count[(x[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
    {
        x[i] = output[i];
    }

    free(output);
}

double radix_sort(int x[], int n)
{
    clock_t start = clock();

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

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort_radix(x, n, exp);
    }

    clock_t stop = clock();

    return ((double)(stop - start) / CLOCKS_PER_SEC) * 1000.0;
}