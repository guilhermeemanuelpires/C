#include <stdio.h>

void main()
{
    printf("Exemplo de structs C\n");

    /* Define a estrutura do strucut */
    struct horario
    {
        int horas;
        int minutos;
        int segundos;
    };

    /* carrega valores para estrutura*/
    struct horario agora = {15, 17, 30};

    /* Lista valores na forma */
    printf("h %i:%i:%i \n", agora);

    /* Ou desta forma */
    printf("h %i:%i:%i \n", agora.horas, agora.minutos, agora.segundos);

    system("pause");
}