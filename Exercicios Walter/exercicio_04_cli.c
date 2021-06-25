#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int envia_servidor();
void conf_dll_windows();
struct sockaddr_in conf_sockt_in();
int conf_socket();
int inet_pton(int af, const char *src, void *dst);
int envia_cliente(char *line);

int main()
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

    envia_cliente("#INICIO");

    fgets(linha, 100, dados);
    while (!feof(dados))
    {
        if (l > 0)
        {
            envia_cliente(linha);
        }

        l++;
        memset(&linha, '\0', sizeof(linha));
        fgets(linha, 100, dados);
    }

    envia_cliente("#FIM");

    fclose(dados);

    return 0;
}

int envia_cliente(char *line)
{

    // Configura Dll para Windows
    conf_dll_windows();

    // Cria conexão com socket
    int server = conf_socket();
    if (server == -1)
    {
        puts("ERRO: conexao com servidor falhou...");
        return 1;
    }
    puts("SUCESSO: conectado ao servidor...");

    // Define Parametros de Socket
    struct sockaddr_in saddr = conf_sockt_in();

    //Converte Endereço IPv4 e IPv6 de texto para formato binário
    if (inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr) <= 0)
    {
        puts("ERRO: Endereco invalido ou endereco nao suportado...");
        return 1;
    }

    if (connect(server, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
    {
        puts("ERRO: a conexao com o servidor falhou...");
        return -1;
    }
    printf("SUCESSO : conectado ao servidor..\n");

    // envia para Cliente
    int valread;
    send(server, line, strlen(line), 0);
    valread = read(server, line, strlen(line));

    closesocket(server);

    return valread;
}

void conf_dll_windows()
{
    // inicia o uso da DLL Winsock para WINDOWS
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
}

struct sockaddr_in conf_sockt_in()
{
    struct sockaddr_in saddr =
        {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(4000)};

    return saddr;
}

int conf_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
};

int inet_pton(int af, const char *src, void *dst)
{
    struct sockaddr_storage ss;
    int size = sizeof(ss);
    char src_copy[INET6_ADDRSTRLEN + 1];

    ZeroMemory(&ss, sizeof(ss));

    strncpy(src_copy, src, INET6_ADDRSTRLEN + 1);
    src_copy[INET6_ADDRSTRLEN] = 0;

    if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0)
    {
        switch (af)
        {
        case AF_INET:
            *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
            return 1;
        case AF_INET6:
            *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
            return 1;
        }
    }
    return 0;
}