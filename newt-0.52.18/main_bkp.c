#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "newt.h"
    struct cliente {
        char codigo;
        char *nome[30];
        long *cartao;
        int ativo;
    };

    const char* FILE_NAME = "clientes.xml";
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    xmlNodePtr cur2 = NULL;

    //* FORMS *//
    newtComponent frm, frmCadastro;
    newtGrid grid;

    //* BUTTONS *//
    newtComponent btnSair,  btnCadastrar, btnSalvar, btnCancelar;

    //* LABELS *//`
    newtComponent lCod, lNome, lCartao, lAtivo;

    //* EDIT *//
    newtComponent edtCod, edtNome, edtcartao;

    //* CHECKBOX *//
    newtComponent ckbAtivo;

    //** LIST BOX **//
    newtComponent lbPessoa;

    const char *id, *nome, *cartao, *ativo;
    char result;

    void createFrmPrincpial();
    void createFrmCadastro();
    void AddCliente();
    void LoadToClienteXml();
    void CreateFileClienteXml();


int main(void){

     CreateFileClienteXml(); 

    struct newtExitStruct es;

    newtInit();
    newtCls();

    createFrmPrincpial();

    do {
        newtFormRun(frm , &es);
        
        newtRefresh();
    
        if(es.u.co == btnCadastrar){            
            createFrmCadastro();
            newtFormRun(frmCadastro, &es);
        }else if (es.u.co == btnSalvar){
            AddCliente();
        }

        if( es.u.key == NEWT_KEY_DELETE){
            newtListboxAppendEntry(lbPessoa, "TESTE ", (void *) 10);
        }

    } while (es.reason != NEWT_EXIT_COMPONENT || es.u.co != btnSair);

    newtPopWindow();
    newtFinished();

    newtFormDestroy(frm);
    newtFormDestroy(frmCadastro);

    return 0;
}

void createFrmPrincpial(){
    
    newtOpenWindow(10, 5, 50, 16, "Formulario de Pessoa...");

    frm = newtForm(NULL, "Formulario de Cadastro", 0);

    btnCadastrar = newtButton(1, 2, "Cadastrar");
    btnSair = newtButton(1, 8, "Sair");

    lbPessoa = newtListbox(20,  1, 15, NEWT_FLAG_BORDER | NEWT_FLAG_SCROLL | NEWT_FLAG_SHOWCURSOR);

    // newtListboxAppendEntry(lbPessoa, "1 - Guilherme", (void *) 1);
    // newtListboxAppendEntry(lbPessoa, "2 - Eduardo ", (void *) 2);
    // newtListboxAppendEntry(lbPessoa, "3 - Douglas ", (void *) 3);

    newtFormAddComponents(frm,
                          btnCadastrar,
                          btnSair,
                          lbPessoa,
                          NULL);

    newtFormAddHotKey(frm,NEWT_KEY_DELETE);

    LoadToClienteXml();

}

void createFrmCadastro(){
    newtOpenWindow(10, 5, 50, 16, "Cadastro de Usuario");
    frmCadastro = newtForm(NULL, "Formulario de Usuario", 0);

    lCod = newtLabel(6, 1, "Cod...:");
    lNome = newtLabel(6, 2, "Nome..:");
    lCartao = newtLabel(6, 3, "Cartao:");
    lAtivo = newtLabel(6, 4, "Ativo.:");

    edtCod = newtEntry(14, 1, "1", 20, &id, NEWT_FLAG_DISABLED);
    edtNome = newtEntry(14, 2, "", 20, &nome, 0);
    edtcartao = newtEntry(14, 3, "", 20, &cartao, 0);
    ckbAtivo = newtCheckbox(14, 4, "", ' ', NULL, NULL);

    btnSalvar = newtButton(15, 10, "Salvar");
    btnCancelar = newtButton(30, 10, "Cancelar");

    newtFormAddComponents(frmCadastro,
                            lCod,
                            lNome,
                            lCartao,
                            lAtivo,
                            edtNome,
                            edtCod,
                            edtcartao,
                            ckbAtivo,
                            btnSalvar,
                            btnCancelar,
                            NULL);
}

void AddCliente(){  
    printf("ADICIONOU!");
}

void CreateFileClienteXml(){
    FILE *File;
    File = fopen(FILE_NAME,"r");

    if(!File){
        File = fopen(FILE_NAME,"w");
        fprintf(File,"<?xml version=\"%s\" encoding=\"%s\"?>","1.0","ISO-8859-1");
    }

    fclose(File);
}   

void LoadToClienteXml(){
 
    doc = xmlParseFile(FILE_NAME);
    xmlChar *ret = NULL;

    if(doc){
        cur = xmlDocGetRootElement(doc);
        cur = cur->children;

        while(cur != NULL){

            if(cur->type == XML_ELEMENT_NODE){
                cur2 = cur->xmlChildrenNode;

                while(cur2 !=NULL){
           
                    if (!xmlStrcmp(cur->name, (const xmlChar * ) "codigo")){
                        ret = xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
                        id = strdup(ret);
                    }
                    if (!xmlStrcmp(cur2->name, (const xmlChar * ) "nome")){
                        ret = xmlNodeListGetString(doc, cur2->xmlChildrenNode,1);
                        nome = strdup(ret);
                    }
                    if (!xmlStrcmp(cur->name, (const xmlChar * ) "cartao")){
                        ret = xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
                        cartao =  strdup(ret);
                    }
                    if (!xmlStrcmp(cur->name, (const xmlChar * ) "ativo")){
                        ret = xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
                        ativo = strdup(ativo);
                    }

                    cur2 = cur2->next;
                }
                newtListboxAppendEntry(lbPessoa, nome, (void *) 1);
            }
            cur = cur->next;
        }   
    }
}