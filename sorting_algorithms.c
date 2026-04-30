#include "sorting_algorithms.h"
#include <stdlib.h>
#include <string.h>

#ifndef TIMER_H
#define TIMER_H

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <time.h>
    #include <unistd.h>
#endif

// Returns the time in ms, adaptated to the OS
double get_time_ms()
{
#if defined(_WIN32) || defined(_WIN64)
    LARGE_INTEGER count, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart * 1000.0 / frequency.QuadPart;
#else
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (t.tv_sec * 1000.0) + (t.tv_nsec / 1000000.0);
#endif
}
#endif

#define RUN 32

double insertion_sort(int x[], int n)
{
    double start = get_time_ms();

    for (int i = 1; i < n; i++) {
        int aux = x[i];
        int j = i - 1;
        // Move elem. > aux to the right
        while (j >= 0 && aux < x[j]) {
            x[j + 1] = x[j];
            j--;
        }
        // Insert aux
        x[j+1] = aux;
    }

    double stop = get_time_ms();

    return stop - start;
}


double selection_sort(int x[], int n)
{
    double start = get_time_ms();

    for (int i = 0; i < n; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            // Found a smaller elem.
            if (x[k] > x[j]) {
                k = j;
            }
        }
        // Found a new min
        if (k!=i) {
            int aux = x[i];
            x[i] = x[k];
            x[k] = aux;
        }
    }

    double stop = get_time_ms();

    return stop - start;
}


void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}


double bubble_sort(int x[], int n)
{
    double start = get_time_ms();

    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (x[j] > x[j + 1])
            {
                swap(&x[j], &x[j + 1]);
                swapped = 1; // Change occurred
            }
        }
        // No change <=> sorted
        if (swapped == 0)
        {
            break;
        }
    }

    double stop = get_time_ms();

    return stop - start;
}


int partition(int x[], int low, int high)
{

    // Pick a random pivot
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
    while (low < high)
    {
        int pivot = partition(x, low, high);

        // Recursively sort the smaller part
        if (pivot - low < high - pivot)
        {
            quick_sort(x, low, pivot - 1);
            low = pivot + 1;
        }
        else
        {
            quick_sort(x, pivot + 1, high);
            high = pivot - 1;
        }

    }
}

double quick_sort_wrapper(int x[], int n)
{
    double start = get_time_ms();

    quick_sort(x, 0, n - 1);

    double stop = get_time_ms();

    return stop - start;
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

    // Copy remaining elements if they exist
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
        merge_sort(x, temp, low, mid); // Left sort
        merge_sort(x, temp, mid + 1, high); // Right sort
        merge(x, temp, low, mid, high); // Combine results
    }
}

double merge_sort_wrapper(int x[], int n)
{
    int *temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL)
    {
        return 0;
    }

    double start = get_time_ms();

    merge_sort(x, temp, 0, n - 1);

    double stop = get_time_ms();

    free(temp);

    return stop - start;
}


double counting_sort(int x[], int n)
{
    double start = get_time_ms();

    if (n <= 0)
    {
        return 0;
    }

    // Find max number
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

    // Find occurrences
    for (int i = 0; i < n; i++)
    {
        count[x[i]]++;
    }

    // Calculate sum
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the sorted list
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[x[i]] - 1] = x[i];
        count[x[i]]--;
    }

    memcpy(x, output, n * sizeof(int));

    free(count);
    free(output);

    double stop = get_time_ms();

    return stop - start;
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
    double start = get_time_ms();

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

    double stop = get_time_ms();

    return stop - start;
}


void heapify(int x[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && x[left] > x[largest])
    {
        largest = left;
    }
    if (right < n && x[right] > x[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        int temp = x[i];
        x[i] = x[largest];
        x[largest] = temp;
        heapify(x, n, largest);
    }
}

double heap_sort(int x[], int n)
{
    double start = get_time_ms();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(x, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(&x[0], &x[i]);
        heapify(x, i, 0);
    }

    double stop = get_time_ms();
    return stop - start;
}


void insertion_sort_range(int x[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = x[i];
        int j = i - 1;
        while (j >= left && x[j] > temp)
        {
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = temp;
    }
}

void merge_timsort(int x[], int left, int mid, int right)
{
    int len1 = mid - left + 1, len2 = right - mid;

    int *left_arr = (int*)malloc(len1 * sizeof(int));
    int *right_arr = (int*)malloc(len2 * sizeof(int));

    if (!left_arr || !right_arr)
    {
        free(left_arr);
        free(right_arr);
        return;
    }

    for (int i = 0; i < len1; i++)
    {
        left_arr[i] = x[left + i];
    }
    for (int i = 0; i < len2; i++)
    {
        right_arr[i] = x[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < len1 && j < len2)
    {
        if (left_arr[i] <= right_arr[j])
        {
            x[k++] = left_arr[i++];
        }
        else
        {
            x[k++] = right_arr[j++];
        }
    }

    while (i < len1)
    {
        x[k++] = left_arr[i++];
    }
    while (j < len2)
    {
        x[k++] = right_arr[j++];
    }

    free(left_arr);
    free(right_arr);
}

double tim_sort(int x[], int n)
{
    double start = get_time_ms();

    for (int i = 0; i < n; i += RUN)
    {
        int end = (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1);
        insertion_sort_range(x, i, end);
    }

    for (int size = RUN; size <= n; size *= 2)
    {
        for (int left = 0; left < n; left += size * 2)
        {
            int mid = left + size - 1;
            int right = (left + size * 2 - 1 < n - 1) ? (left + size * 2 - 1) : (n - 1);

            if (mid < right)
            {
                merge_timsort(x, left, mid, right);
            }
        }
    }

    double stop = get_time_ms();
    return stop - start;
}