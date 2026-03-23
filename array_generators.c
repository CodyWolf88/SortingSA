//
// Created by minec on 3/13/2026.
//

#include "array_generators.h"

void generate_sorted(int x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = i;
    }
}

void generate_reverse_sorted(int x[], int n) {
    for (int i = 0; i < n; i++)
    {
        x[i] = n - i;
    }
}

void generate_nearly_sorted(int x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = i;
    }

    int swaps = n / 20;
    for (int i = 0; i < swaps; i++)
    {
        int i1 = rand() % n;
        int i2 = rand() % n;
        int aux = x[i1];
        x[i1] = x[i2];
        x[i2] = aux;
    }
}

void generate_random(int x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % (n * 10);
    }
}

void generate_flat(int x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 100;
    }
}
