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
    struct cliente *proximo;
    struct cliente *anterior;
};

int compara_cliente_ativo(const void *, const void *);
int compara_cliente_inativos(const void *a, const void *b);

void main(void)
{
    FILE *dados;
    dados = fopen("clientes.csv", "r");

    if (dados == NULL)
    {
        printf("Erro ao abrir arquivo!");
        abort();
    }

    char linha[100] = {'\0'};
    int l = 0;

    struct cliente *lista, *ultimo, *new;
    lista = ultimo = NULL;

    lista = malloc(sizeof(struct cliente) * 1000);
    memset(lista, '\0', sizeof(struct cliente) * 1000);

    //Carrega Linha
    fgets(linha, 100, dados);

    while (!feof(dados))
    {
        if (l > 0)
        {
            new = lista + (l - 1);
            //malloc(sizeof(struct cliente));
            if (!ultimo)
            {
                ultimo = new;
            }
            else
            {
                ultimo->proximo = new;
                new->anterior = ultimo;
            }
            ultimo = new;

            // Carrega linha para o ponteiro
            char *pos = NULL;
            char *xPos = &linha[0];
            char *retorno;
            int c = 1;

            retorno = strtok_r(xPos, ";\r\n", &pos);
            while (retorno)
            {
                switch (c)
                {
                case 1:
                    new->id = atoi(retorno);
                    break;

                case 2:
                    new->nome = strdup(retorno);
                    break;

                case 3:
                    new->endereco = strdup(retorno);
                    break;

                case 4:
                    new->saldo = atof(retorno);
                    break;

                case 5:
                    new->situacao = atoi(retorno);
                    break;

                case 6:
                    new->telefone = atol(retorno);
                    break;
                }
                c++;
                retorno = strtok_r(NULL, ";\r\n", &pos);
            }
        }
        l++;
        memset(&linha, '\0', sizeof(linha));
        fgets(linha, 100, dados);
    }

    printf("\nOrdena por clientes nao ativos");
    qsort((void *)lista, l - 1, sizeof(struct cliente), compara_cliente_ativo);
    for (int i = 0; i < (l - 1); i++)
    {
        printf("%i, %s, %i\n", lista[i].id, lista[i].nome, lista[i].situacao);
    }

    printf("\nOrdenando por clientes inativos\n");
    qsort((void *)lista, l - 1, sizeof(struct cliente), compara_cliente_inativos);
    for (int i = 0; i < (l - 1); i++)
    {
        printf("%i, %s, %i\n", lista[i].id, lista[i].nome, lista[i].situacao);
    }

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

int compara_cliente_ativo(const void *a, const void *b)
{
    struct cliente *pri = (struct cliente *)a;
    struct cliente *seg = (struct cliente *)b;

    if (pri->situacao == seg->situacao)
    {
        return 0;
    }
    else if (pri->situacao > seg->situacao)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int compara_cliente_inativos(const void *a, const void *b)
{
    struct cliente *pri = (struct cliente *)a;
    struct cliente *seg = (struct cliente *)b;

    if (pri->situacao == seg->situacao)
    {
        return 0;
    }
    else if (pri->situacao < seg->situacao)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}