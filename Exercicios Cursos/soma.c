#include <stdio.h>

main()
{
    int n, n2=0;
    printf("Soma valores!\n");

    printf("Digite dois numeros separados por espaco : ");
    scanf("%d %d", &n, &n2);

    printf("Resultado da soma:  %d\n", (n + n2) );

    printf("valor %d, endereco da memoria %i \n",n,&n);
}