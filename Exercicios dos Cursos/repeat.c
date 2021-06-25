#include <stdio.h>

void main()
{
    printf("Lacos de repeticao Wile");
    printf("\n");

    int contador = 1;

    printf("\n WHILE CONTA ATE 10");
    while (contador <= 10)
    {
        printf("\nPosicao : %i", contador);
        contador++;
    }

    printf("\n FOR CONTA ATE 10");
    for (size_t contador = 1; contador <= 10; contador++)
    {
        printf("\nPosicao : %i", contador);
    }
}