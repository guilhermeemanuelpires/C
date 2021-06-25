#include <stdio.h>

void main()
{
    printf("Utilizando vetor na minha struct \n");

    struct horario
    {
        int hora;
        int minutos;
        int segundos;
    };

    struct horario agora[4] =
        {
            {10, 20, 30},
            {5, 10, 20},
            {30, 40, 50}};

    for (int i = 0; i < 3; i++)
    {
        printf("h %i:%i:%i\n", agora[i]);
    }
    
    system("pause");
}