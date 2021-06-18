#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "newt.h"

    struct cliente {
        char *codigo;
        char *nome;
        long cartao;
        int ativo;
        struct cliente *next;
        struct cliente *back;
    };

    const char* FILE_NAME = "clientes.xml";
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;

    //** FORMS **//
    newtComponent frm, frmCadastro;
    newtGrid grid;

    //** BUTTONS **//
    newtComponent btnSair,  btnCadastrar, btnSalvar, btnCancelar;

    //** LABELS **//
    newtComponent lCod, lNome, lCartao, lAtivo;

    //** EDIT **//
    newtComponent edtCod, edtNome, edtcartao;

    //** CHECKBOX **//
    newtComponent ckbAtivo;

    //** LIST BOX **//
    newtComponent lbPessoa;

    const char *id, *nome, *cartao, *ativo;
    char result;

    int l = 0;
    struct cliente *list, *last, *new;

    void createFrmPrincpial();
    void createFrmCadastro();
    void AddCliente();
    int LoadToClienteXml();
    void LaodListbox();
    int CreateOrOpenFileClienteXml();
    xmlNodePtr createRoot(xmlDocPtr doc, char* name);
    xmlNodePtr addChild(xmlNodePtr parent, char* name, char* value);
    void setElementContent(xmlNodePtr element, char* value);


int main(void){
    
    struct newtExitStruct es;
    struct newtExitStruct es2;

    LoadToClienteXml();

    newtInit();
    newtCls();

    createFrmPrincpial();

    LaodListbox();
    
    do {
        newtFormRun(frm , &es);

        newtRefresh();

        if(es.u.co == btnCadastrar){
            createFrmCadastro();
            newtFormRun(frmCadastro, &es2);
            AddCliente();
            newtFormDestroy(frmCadastro);
        }else if (es.u.co == btnSalvar){

            // xmlNodePtr clientes = NULL;
            // clientes = createRoot(doc, "clientes");

            AddCliente();
            newtFinished();
        }

        if( es.u.key == NEWT_KEY_DELETE){
            AddCliente();
            LaodListbox();
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

    newtFormAddComponents(frm,
                          btnCadastrar,
                          btnSair,
                          lbPessoa,
                          NULL);

    newtFormAddHotKey(frm,NEWT_KEY_DELETE); 
    
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

int CreateOrOpenFileClienteXml(){
    FILE *File;
    File = fopen(FILE_NAME,"r");

    if(!File){
        printf("\n PAssou aqui!");
        doc = xmlNewDoc(BAD_CAST "1.0");
        return 1;
    }else{
        doc = xmlParseFile(FILE_NAME);
        return 0;
    }

    fclose(File);   
}   

void AddCliente(){
    
    // xmlNodePtr cliente= NULL;

    // cliente  = addChild(clientes, "cliente", NULL);

    // xmlSetProp(cliente, "codigo", id);
    // xmlSetProp(cliente, "nome", nome);
    // xmlSetProp(cliente, "cartao", cartao);
    // xmlSetProp(cliente, "ativo", "1");

    new = list + l;

    if(!last){
        last = new;
    }else{
        last->next = new;
        new->back  = last; 
    }

    last = new;

    new->codigo = strdup(id);
    new->nome   = strdup(nome);
    new->cartao = atol(cartao);
    new->ativo  = atoi("1");
    

    // new->codigo = strdup("TESTE");
    // new->nome   = strdup("TEST WALTER");
    // new->cartao = atol("123456");
    // new->ativo  = atoi("1");


    l++;

    // newtListboxClear(lbPessoa);

    LaodListbox();

}

int LoadToClienteXml(){

    CreateOrOpenFileClienteXml();

    // xmlNodePtr clientes= NULL;

    // clientes = createRoot(doc, "clientes");

    // AddCliente(clientes);

    // Aloca Memoria para estrutura
    
    list = last = NULL;
    list = malloc(sizeof(struct cliente) *1000);
    memset(list, '\0', sizeof(struct cliente) * 100);

    if(doc){

        cur = xmlDocGetRootElement(doc);
        cur = cur->children;

        while(cur != NULL){

            if(cur->type == XML_ELEMENT_NODE){    

                new = list + l;

                if(!last){
                    last = new;
                }else{
                    last->next = new;
                    new->back  = last; 
                }

                last = new;

                new->codigo = strdup(xmlGetProp(cur,"codigo"));
                new->nome   = strdup(xmlGetProp(cur,"nome"));
                new->cartao = atol(xmlGetProp(cur,"cartao"));
                new->ativo  = atoi( xmlGetProp(cur,"ativo"));

                l++;
            }
            cur = cur->next;
        }

        // AddCliente();
        // for(int i = 0; i < l; i++){
        //     char caption[500];
        //     sprintf(caption, "%s - %s",list[i].codigo, list[i].nome);
        //     printf("\n %s", caption);
        // }

        return 0;

    }else{

        return 1;
    }
    
    // xmlSaveFileEnc(FILE_NAME,doc,"ISO-8859-1");
    // xmlFreeDoc(doc);
}

void LaodListbox(){

    newtListboxClear(lbPessoa);

    for(int i = 0; i < l; i++){
        char caption[500];
        sprintf(caption, "%s - %s",list[i].codigo, list[i].nome);
        newtListboxAppendEntry(lbPessoa, caption, (void * ) list[i].codigo);
    }
}

xmlNodePtr createRoot(xmlDocPtr doc, char* name)
{
    xmlNodePtr root;
    root = xmlNewNode(NULL, BAD_CAST name);
    xmlDocSetRootElement(doc, root);
    return root;
}

xmlNodePtr addChild(xmlNodePtr parent, char* name, char* value)
{
    return xmlNewChild(parent, NULL, BAD_CAST name, BAD_CAST value);
}