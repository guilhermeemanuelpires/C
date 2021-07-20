#include <stdio.h>

int main()
{
    /* Exemplo de ponteiro!*/
    printf("\nExemplo Ponteiro!");

    int    a = 10;
    char   b = 'X';
    double c = 3.5;
    float  d = 1.5; 

    int    *pa = &a;
    char   *pb = &b;
    double *pc = &c;
    float  *pd = &d;


    printf("\nEndereco do ponteiro a = %i - valor do ponteiro a = %i", pa, *pa);
    printf("\nEndereco do ponteiro b = %i - valor do ponteiro b = %c", pb, *pb);
    printf("\nEndereco do ponteiro c = %i - valor do ponteiro c = %f", pc, *pc);
    printf("\nEndereco do ponteiro d = %i - valor do ponteiro d = %f ", pd, *pd);

    return 0;
}