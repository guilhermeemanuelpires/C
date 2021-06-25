#include <stdio.h>
#include <stdlib.h>

void main()
{
    FILE *arq;

    arq = fopen("arquivao.txt", "w");

    fprintf(arq, "TESTE\nTESTE2\nTESTE3\n");

    fclose(arq);

    arq = fopen("arquivao.txt", "r");

    if (arq == NULL)
    {
        printf("Este arquivo nao existe!\n");
        exit(0);
    };

    char all_arquivao[100];

    while (fgets(all_arquivao, 100, arq) != NULL)
    {
        printf("%s", all_arquivao);
    };

    fclose(arq);
}