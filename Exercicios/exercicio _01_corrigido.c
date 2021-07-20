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
    /* lista dinamica encadeada */
    struct cliente *proximo;
    struct cliente *anterior;
};

void main(void)
{
    FILE *dados;
    dados = fopen("clientes.csv", "r");

    if (dados == NULL)
    {
        printf("Erro ao abrir arquivo!");
        abort();
    }

    char linha[100] = {'\0'}; /* ------ sempre liberar a memoria da variavel */
    int l = 0;

    /* ----- alocacao dinamica */
    struct cliente *lista, *ultimo, *new;
    lista = ultimo = NULL; /* ----- sempre liberar a memoria */

    //Carrega Linha
    fgets(linha, 100, dados);

    while (!feof(dados))
    {
        // Valida se � a primeira coluna
        if (l > 0)
        {
            /* lista dinamica com apontamento para o proximo e ultimo */
            new = malloc(sizeof(struct cliente));
            if (!lista)
            {
                lista = new;
            }
            else
            {
                ultimo->proximo = new;
                new->anterior = ultimo;
            }
            ultimo = new;
            /**/

            // Carrega linha para o ponteiro
            char *pos = NULL;       /* -----esse cara nao pode ter valor no inicio */
            char *xPos = &linha[0]; /* ------quem vai ser usado como dado e o xPos ou poderia ser a propria variavel no strtok_r */
            char *retorno;
            int c = 1;

            // percore colunas qaubrando por separador ";"
            retorno = strtok_r(xPos, ";\r\n", &pos); /* se voce deixr ele no loop while entao toda vez que ele subir vai reiniciar e ficar em loop eterno */
            while (retorno)
            {
                //classifica��o da posi��o do dado
                switch (c)
                {
                case 1:
                    //clientes[l-1].id = atoi(retorno);
                    new->id = atoi(retorno);
                    break;

                case 2:
                    //Aloca dinamicamente a variavel vereficando o tamanho
                    //clientes[l-1].nome = malloc(strlen(retorno)+1);
                    //strcpy(clientes[l-1].nome,retorno);

                    // Aloca e aramzena o dado em um comando s� strdup()
                    //clientes[l-1].nome = strdup(retorno);
                    new->nome = strdup(retorno);
                    break;

                case 3:
                    //clientes[l-1].endereco = strdup(retorno);
                    new->endereco = strdup(retorno);
                    break;

                case 4:
                    //clientes[l-1].saldo = atof(retorno);
                    new->saldo = atof(retorno);
                    break;

                case 5:
                    //clientes[l-1].situacao = atoi(retorno);
                    new->situacao = atoi(retorno);
                    break;

                case 6:
                    //clientes[l-1].telefone = atol(retorno);
                    new->telefone = atol(retorno);
                    break;
                }
                c++;
                retorno = strtok_r(NULL, ";\r\n", &pos); /* pega o proximo token */
            }
            /* vc nao faz liberacao de memoria aqui, pois nao foi alocado dinamicamente, sao ponteiros sendo utilizados apenas em uma funcao que usa uma variavel */
            //free(pos);
            //free(xPos);
            //free(retorno);
        }
        l++;
        memset(&linha, '\0', sizeof(linha)); /////// ------- sempre bom deixar limpa a variavel
        fgets(linha, 100, dados);
    }

    // Lista Clientes usando o ponteiro de alocacao dinamica
    printf("Lista em ordem crescente\n");
    for (new = lista; new; new = new->proximo)
    {
        printf("%i, %s \n", new->id, new->nome);
    }
    printf("\n\n\nLista em ordem decrescente\n");
    for (new = ultimo; new; new = new->anterior)
    {
        printf("%i, %s \n", new->id, new->nome);
    }
    /* limmpando a lista */
    struct cliente *aux;
    new = lista;
    while (new)
    {
        aux = new->proximo;
        free(new->nome);
        free(new->endereco);
        free(new);
        new = aux;
    }

    fclose(dados);
}