#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    /* malloc : Solicita ao sistema operacional espaço na memoria, retornando um ponteiro! */
    int x = 0;
    int *p = (int *)malloc(sizeof(x));

    if (p == NULL)
    {
        printf("nao existe espacao disponivel na memoria!");
    }
    else
    {
        *p = 100;
        printf("\nAlocacao em malloc : %i", *p);
    }

    /* free : Limpa o ponteiro e libera memória para o computador, assim administrando o que foi alocado para determinado processo.*/
    free(p);

    /* calloc : Solicita para o sistema operacional espaço na memória, definindo o tamanho e quantas vezes desejar 
                desse tamanho solicitado, o mesmo também retorna o endereço do ponteiro alocado.
    */

    int y = 0;
    int *p2 = (int *)calloc(3, sizeof(y));

    if (p2 == NULL)
    {
        printf("nao existe espacao disponivel na memoria!");
    }
    else
    {
        *(p2) = 1;
        *(p2 + 1) = 2;
        *(p2 + 2) = 3;

        for (int i = 0; i < 3; i++)
        {
            printf("\nAlocacao em calloc p%i: %i", i, p2[i]); /* code */
        }
    }
    free(p2);

    // realloc
}