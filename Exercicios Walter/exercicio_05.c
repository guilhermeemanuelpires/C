#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

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

void add_cliente(struct cliente *new, char linha[100]);

int main()
{
    printf("Utilizando thread...\n");

    FILE *dados;
    dados = fopen("clientes.csv", "r");

    if (dados == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    char linha[100] = {'\0'};
    int l = 0;

    struct cliente *lista, *ultimo, *new;
    lista = ultimo = NULL;

    //Carrega Linha
    fgets(linha, 100, dados);

    while (!feof(dados))
    {
        if (l > 0)
        {
            pthread_t thread;
            int flag = 0, i = 0;

            printf("Criando thread:  %i\n", l);
            flag = pthread_create(&thread, NULL, add_cliente, NULL);
            if (flag != 0)
                printf("Erro na criação duma nova thread\n");
            else
            {
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
                add_cliente(new, linha);
            }
        }
        l++;
        memset(&linha, '\0', sizeof(linha));
        fgets(linha, 100, dados);
    }

    // Derruba thread
    pthread_exit(NULL);

    printf("Lista em ordem crescente\n");
    for (new = lista; new; new = new->proximo)
    {
        printf("%i, %s \n", new->id, new->nome);
    }
    printf("\nLista em ordem decrescente\n");
    for (new = ultimo; new; new = new->anterior)
    {
        printf("%i, %s \n", new->id, new->nome);
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

void add_cliente(struct cliente *new, char linha[100])
{
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