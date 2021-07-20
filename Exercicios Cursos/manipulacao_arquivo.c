#include <stdio.h>
#include <stdlib.h>

void main()
{
    //Declara ponteiro do tipo FILE arquivo
    FILE *arq;

    //Carrega arquivo para o ponteiro
    arq = fopen("teste.txt", "w");

    // Escreve em um arquivo.
    fprintf(arq, "10 20 30");

    // Fecha arquivo
    fclose(arq);

    // Ler e eescrever em um arquisvo!
    arq = fopen("teste2.txt", "r");
    if (arq == NULL)
    {
        printf("Este arquivo nao existe!\n");
        exit(0);
    }
    else
    {
        int x, y, z;
        fscanf(arq, "%i %i %i", &x, &y, &z);

        printf("%i %i %i", x, y, z);
        fclose(arq);
    }
}