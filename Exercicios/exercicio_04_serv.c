#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

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

int main()
{
    printf("\nconfigurando servidor...\n");

    char buff[100] = {'\0'};

    WSADATA wsa;

    WSAStartup(MAKEWORD(2, 0), &wsa);

    struct sockaddr_in caddr;

    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(4000)};

    int server = socket(AF_INET, SOCK_STREAM, 0);

    if (server == -1)
    {
        puts("ERRO: conexao ao servidro falhou...");
        return 1;
    }
    puts("SUCESSO: servidor conecatdo...");

    if (bind(server, (struct sockaddr *)&saddr, sizeof saddr) < 0)
    {
        puts("ERRO: bind conexao porta(4000)...");
        return 1;
    }
    puts("SUCESSO: bind realizado com sucesso na porta(4000)...");

    // Define o numero de conexao no socket
    if (listen(server, 5) != 0)
    {
        puts("ERRO: erro ao configurar o LISTEN \n");
        return 1;
    }
    puts("SUCESSO: listen configurado... \n");

    int client, x;
    int csize = sizeof caddr;

    struct cliente *lista, *ultimo, *new;
    lista = ultimo = NULL;

    client = accept(server, (struct sockaddr *)&caddr, &csize);
    x = recv(client, buff, sizeof buff, 0);
    send(client, buff, x, 0);
    int start = !strcmp(buff, "#INICIO");

    // Aguarda estruçoes do cliente
    while (start)
    {
        client = accept(server, (struct sockaddr *)&caddr, &csize);
        x = recv(client, buff, sizeof buff, 0);
        send(client, buff, x, 0);

        int finished = !strcmp(buff, "#FIM");

        start = !finished;

        if (start)
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

            char *pos = NULL;
            char *xPos = &buff[0];
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
        fflush(stdout);
        memset(&buff, '\0', sizeof(buff));
    }
    printf("\nACABOU MLK MLK \n");
    if (!start)
    {
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
    }

    closesocket(client);
    return 0;
}