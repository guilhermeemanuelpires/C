#include <stdio.h>

void main()
{
    // Declaro matriz de 5 por 5 e atribuo valores
    int matriz[5][5] = {{1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};

    // percorro coluna no for "int C" e percorro linha no for "int  l"
    for (int c = 0; c < 5; c++)
    {  
        for (size_t l = 0; l <5; l++)
        {   
            printf("%i ", matriz[c][l]);
        }
        printf("\n");
    }
}