#include <stdio.h>

int comparador(const void *a, const void *b);

int main()
{
    printf("\nfuncao qsort!");

    int i, val[] = {15, 3, 10, 14, 25};

    //ordena o array
    qsort(val, 5, sizeof(int), comparador);

    // mostra os valores do array
    for (i = 0; i < 5; i++)
    {
        printf("\n%i ", val[i]);
    }

    return (0);
}

int comparador(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}