#include <stdio.h>

void main()
{
    printf("Casting na Linguagem C \n");
    /*
        Nesse Exemplo nosso resultado ira retornar um 
        valor inteiro, pois a divisão se trata de um 
        variaveis INT, não levando em consideração 
        os valores quebrados como Ex: 5,333333333333333
        */

    int x = 16;
    int y = 3;

    float result = x / y;

    printf("Resultado sem casting : %f \n", result);

    /*
    Agora nesse Exemplo eu utilizo casting para definir o 
    tipo do resultado da divisão, antes se tratava de um 
    resultado inteiro agora eu defino com (FLOAT);
    */

    float resultCasting = (float) x / y;

    printf("Resultado aplicando casting : %f \n", resultCasting);

    system("pause");
}