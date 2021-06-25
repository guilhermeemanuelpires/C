#include <stdio.h>
#include <string.h>

/* Defino uma Struct global */
struct pessoa
{
    char nome[30];
    int idade;
};

void main()
{
    printf("Utilizando funcao na minha struct \n");

    /* Declaro a struct*/
    struct pessoa printa(struct pessoa p);

    /* Carrega a struct*/
    struct pessoa guilherme;
    strcpy(guilherme.nome, "Guilherme Pires");
    guilherme.idade = 23;

    struct pessoa retornoGuilherme = printa(guilherme);

    /*retorno da função*/
    printf("Retorno da funcao : %s, %i\n", retornoGuilherme.nome, retornoGuilherme.idade);

    system("pause");
}

struct pessoa printa(struct pessoa p)
{
    printf("Nome  : %s \n", p.nome);
    printf("idade : %i \n", p.idade);
    return p;
}