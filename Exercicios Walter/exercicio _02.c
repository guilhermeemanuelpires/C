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

void main()
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

    //Carrega Linha
    fgets(linha, 100, dados);

    while (!feof(dados))
    {
        // Valida se � a primeira coluna
        if (l > 0)
        {
            //define endereçamento de memoria para o novo registro de cleinte.
            new = malloc(sizeof(struct cliente));

            // Verifica a existência da lista de registro.
            if (!lista)
            {
                //Caso não exista carrega o novo registro.
                lista = new;
            }
            else
            {
                //Se existir o “ultimo” assume o “proximo” e o “proximo” assume o novo registro.
                ultimo->proximo = new;
                // A Partir de agora o  “new” assume o “anterior” e o “anterior” assume o "ultimo" registro.
                new->anterior = ultimo;
            }
            //Recarrega o novo registro para o "último" ponteiro .
            ultimo = new;

            char *pos = NULL;
            char *xPos = &linha[0];
            char *retorno;
            int c = 1;

            // percore colunas qaubrando por separador ";"
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
                    new->saldo = atoi(retorno);
                    break;

                case 5:
                    new->situacao = atof(retorno);
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
        memset(&linha, '\0', sizeof(linha)); /////// ------- sempre bom deixar limpa a variavel
        fgets(linha, 100, dados);
    }

    GeraXml(lista, new, ultimo);

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

void GeraXml(struct cliente *lista, struct cliente *new, struct cliente *ultimo)
{
    FILE *XML;
    XML = fopen("clientes.xml", "w");

    if (!XML)
    {
        printf("Erro ao gerar o arquivo clientes.xml");
        abort();
    }

    fprintf(XML, "<?xml version=\"%s\" encoding=\"%s\"?>", "1.0", "ISO-8859-1");

    fprintf(XML, "<clientes>");

    for (new = lista; new; new = new->proximo)
    {
        fprintf(XML, "<cliente>");
        fprintf(XML, "<ID>%i</ID>", new->id);
        fprintf(XML, "<Nome>%s</Nome>", new->nome);
        fprintf(XML, "<Endereco>%s</Endereco>", new->endereco);
        fprintf(XML, "<Saldo>%f</Saldo>", new->saldo);
        fprintf(XML, "<Situacao>%i</Situacao>", new->situacao);
        fprintf(XML, "<Telefone>%d</Telefone>", new->telefone);
        fprintf(XML, "</cliente>");
    }
    fprintf(XML, "</clientes>");

    fclose(XML);
    printf("Arquivo gerado com sucesso!");
}
