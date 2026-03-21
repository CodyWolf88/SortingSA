#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "array_generators.h"

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

void insertion_sort(int x[], int n)
{
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    for (int i = 1; i < n; i++) {
        int aux = x[i];
        int j = i - 1;
        while (j >= 0 && aux < x[j]) {
            x[j + 1] = x[j];
            j--;
        }
        x[j+1] = aux;
    }

    gettimeofday(&end, 0);
    printf("%ldms - insertion sort\n", end.tv_usec - begin.tv_usec);
}

void selection_sort(int x[], int n) {

    struct timeval begin, end;
    gettimeofday(&begin, 0);

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

    gettimeofday(&end, 0);
    printf("%ldms - selection sort\n", end.tv_usec - begin.tv_usec);
}

int main(void) {

    int *a = generate_unsorted_array(10000);
    int *b = copy_array(a, 10000);

    insertion_sort(a, 10000);

    selection_sort(b, 10000);

    free(a);
    free(b);
    return 0;
}