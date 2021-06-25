#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cliente
{
    int id;
    char *nome;
    char *endereco;
    double saldo;
    int situacao;
    long telefone;
};

void main()
{
    FILE *dados;
    dados = fopen("clientes.csv", "r");

    if (dados == NULL)
    {
        printf("Erro ao abrir arquivo!");
        abort();
    }

    char linha[100];
    int l = 0;

    struct cliente clientes[43];

    //Carrega Linha
    fgets(linha, 100, dados);

    while (!feof(dados))
    {
        // Valida se � a primeira coluna
        if (l > 0)
        {
            // Carrega linha para o ponteiro
            char *pos = linha;
            char *xPos = NULL;
            char *retorno;
            int c = 1;

            // percore colunas qaubrando por separador ";"
            while ((retorno = strtok_r(xPos, ";\r\n", &pos)))
            {
                //classifica��o da posi��o do dado
                switch (c)
                {
                case 1:
                    clientes[l - 1].id = atoi(retorno);
                    break;

                case 2:
                    //Aloca dinamicamente a variavel vereficando o tamanho
                    //clientes[l-1].nome = malloc(strlen(retorno)+1);
                    //strcpy(clientes[l-1].nome,retorno);

                    // Aloca e aramzena o dado em um comando s� strdup()
                    clientes[l - 1].nome = strdup(retorno);
                    break;

                case 3:
                    clientes[l - 1].endereco = strdup(retorno);
                    break;

                case 4:
                    clientes[l - 1].saldo = atof(retorno);
                    break;

                case 5:
                    clientes[l - 1].situacao = atoi(retorno);
                    break;

                case 6:
                    clientes[l - 1].telefone = atol(retorno);
                    break;
                }
                c++;
            }
            free(pos);
            free(xPos);
            free(retorno);
        }
        l++;

        fgets(linha, 100, dados);
    }

    // Lista Clientes
    for (int i = 0; i < 43; i++)
    {
        printf("%i, %s \n", clientes[i].id, clientes[i].nome);
    }

    fclose(dados);
}
