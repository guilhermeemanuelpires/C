#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

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

void parseStory(xmlDocPtr doc, xmlNodePtr cur, struct cliente *new);

int main()
{
    xmlDocPtr doc = NULL;
    doc = xmlParseFile("clientes.xml");

    if (!doc)
    {
        printf("Arqueivo não encontrado!\n");
        return 1;
    }
    else
    {
        xmlNodePtr cur = NULL;
        cur = xmlDocGetRootElement(doc);

        cur = cur->children;

        struct cliente *lista, *ultimo, *new;
        lista = ultimo = NULL;

        while (cur != NULL)
        {
            if (cur->type == XML_ELEMENT_NODE)
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
                parseStory(doc, cur, new);
            }
            cur = cur->next;
        }

        printf("Lista de forma crescente\n");
        for (new = lista; new; new = new->proximo)
        {
            printf("%i, %s \n", new->id, new->nome);
        }

        printf("\nLista de forma decrescente\n");
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

    xmlFree(doc);
}

void parseStory(xmlDocPtr doc, xmlNodePtr cur, struct cliente *new)
{
    xmlChar *ret = NULL;
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"ID")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->id = atoi(ret);
        }

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Nome")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->nome = strdup(ret);
        }

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Endereco")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->endereco = strdup(ret);
        }

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Saldo")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->saldo = atof(ret);
        }

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Situacao")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->situacao = atoi(ret);
        }

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Telefone")))
        {
            ret = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            new->telefone = atol(ret);
        }

        cur = cur->next;
    }

    xmlFree(ret);
}
