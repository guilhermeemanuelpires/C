#include <stdio.h>

void main()
{
    printf("Exemplos de como inicializar uma struct\n");
    /* Define a estrutura do strucut */
    struct horario
    {
        int horas;
        int minutos;
        int segundos;
    };

    // Exemplo 1
    struct horario agora1;
    agora1.horas = 10;
    agora1.minutos = 20;
    agora1.segundos = 20;

    // Exemplo 2
    struct horario agora2 = {10, 20, 30};

    // Exemplo 3
    struct horario agora3 = {.segundos = 30, .horas = 10, .minutos = 20};

    printf("Exemplo 1 h %i:%i:%i \n", agora1);
    printf("Exemplo 2 h %i:%i:%i \n", agora2);
    printf("Exemplo 3 h %i:%i:%i \n", agora3);

    system("pause");
}