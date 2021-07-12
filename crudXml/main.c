#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "newt.h"

    struct cliente {
        int codigo;
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
    newtComponent frm, frmCadastro, frmMsg;
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

    char bfId[32], bfNome[100], bfCartao[32];

    char *id, *nome, *cartao;
    char ativo;

    int l = 0;
    struct cliente *list, *last, *new;

    void createFrmPrincpial();
    void createFrmCadastro();
    void AddCliente();
    void EditaCliente();
    void SaveEditCliente();
    void DeleteCliente();
    int LoadToClienteXml();
    void SaveToXml();
    void LaodListbox();
    int CreateOrOpenFileClienteXml();
    void setElementContent(xmlNodePtr element, char* value);
    int GetSeqCodigo();
    int CheckFinal();
    xmlNodePtr createRoot(xmlDocPtr doc, char* name);
    xmlNodePtr addChild(xmlNodePtr parent, char* name, char* value);


int main(void){
    
    struct newtExitStruct es;
    struct newtExitStruct es2;  

    LoadToClienteXml();

    newtInit();
    newtCls();

    createFrmPrincpial();

    LaodListbox();
    
    do {
        newtRefresh();
        newtFormRun(frm , &es);

        if(es.u.co == btnCadastrar){

            int  SeqID = GetSeqCodigo();
            sprintf(&bfId[0], "%i", SeqID);
            sprintf(&bfNome[0], "%s", "");
            sprintf(&bfCartao[0], "%s", "");
            
            createFrmCadastro();

            int controll = 1;
            do{
                newtRefresh();    
                newtFormRun(frmCadastro, &es2);
                if (es2.u.co == btnSalvar){
                    if (strlen(nome) <= 0 ){
                        newtWinMessage("Atencao", "Ok", "Campo Nome eh obrigatorio!");
                        controll = 1;
                    }else if(strlen(cartao) <= 0){
                        newtWinMessage("Atencao", "Ok", "Campo Cartao eh obrigatorio!");
                        controll = 1;
                    }else{
                        AddCliente();
                        controll = 0;
                    }

                }else if (es2.u.co == btnCancelar){
                    controll = 0;
                }

            }while(controll);
        }

        if( es.u.key == NEWT_KEY_DELETE){
            DeleteCliente();
        }else if(es.u.key == NEWT_KEY_RIGHT){
            EditaCliente();
            createFrmCadastro();
            int controll = 1;
            do{
                newtRefresh();    
                newtFormRun(frmCadastro, &es2);
                if (es2.u.co == btnSalvar){
                    if (strlen(nome) <= 0 ){
                        newtWinMessage("Atencao", "Ok", "Campo Nome eh obrigatorio!");
                        controll = 1;
                    }else if(strlen(cartao) <= 0){
                        newtWinMessage("Atencao", "Ok", "Campo Cartao eh obrigatorio!");
                        controll = 1;
                    }else{
                        SaveEditCliente();
                        controll = 0;
                    }
                }else if (es2.u.co == btnCancelar){
                    controll = 0;
                }

            }while(controll);

        }

    } while (es.u.co != btnSair);
    
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
    newtFormAddHotKey(frm,NEWT_KEY_RIGHT);
    
}

void createFrmCadastro(){
    newtOpenWindow(10, 5, 50, 16, "Cadastro de Usuario");   
    frmCadastro = newtForm(NULL, "Formulario de Usuario", 0);

    lCod = newtLabel(6, 1, "Cod...:");
    lNome = newtLabel(6, 2, "Nome..:");
    lCartao = newtLabel(6, 3, "Cartao:");
    lAtivo = newtLabel(6, 4, "Ativo.:");

    edtCod = newtEntry(14, 1, &bfId[0], 20, (const char **) &id, NEWT_FLAG_DISABLED);
    edtNome = newtEntry(14, 2, &bfNome[0], 20, (const char **) &nome, 0);
    edtcartao = newtEntry(14, 3, &bfCartao[0], 20, (const char **) &cartao, 0);
    ckbAtivo = newtCheckbox(14, 4, "", ' ', NULL, &ativo);

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
        doc = xmlNewDoc(BAD_CAST "1.0");
        return 1;
    }else{
        doc = xmlParseFile(FILE_NAME);
        return 0;
    }

    fclose(File);   
}   

void AddCliente(){

    int SeqID = GetSeqCodigo();
    sprintf(&bfId[0], "%i", SeqID);

    new = malloc(sizeof(struct cliente));
    memset(new, '\0', sizeof(struct cliente));

    if(!list){
        list = new;
    }else{
        last->next = new;
        new->back  = last; 
    }

    last = new;

    new->codigo = SeqID;
    new->nome   = strdup(nome);
    new->cartao = atol(cartao);

    if (ativo == '*'){
        new->ativo  = atoi("1");
    }else{
        new->ativo  = atoi("0");
    }

    LaodListbox();

    SaveToXml();
}

void EditaCliente(){
    
    const int idDell = (int)(long) newtListboxGetCurrent(lbPessoa);
    
    for(new = list; new; new = new->next){
        if(new->codigo == idDell){
            sprintf(&bfId[0], "%i", new->codigo);
            sprintf(&bfNome[0], "%s", new->nome);
            sprintf(&bfCartao[0], "%lu", new->cartao);

            if (new->cartao == 1){
                ativo = ativo;
            }

            // break;
        }
    }
}

void SaveEditCliente(){
    for(new = list; new; new = new->next){
        if(new->codigo == atoi(id)){
            new->nome   = strdup(nome);
            new->cartao = atol(cartao);

            if (ativo == '*'){
                new->ativo  = atoi("1");
            }else{
                new->ativo  = atoi("0");
            }

        }
    }

    LaodListbox();
    
    SaveToXml();
}

int GetSeqCodigo(){
    // Retorna sempre o maior sequencial da estrutura para gerar codigo
    int iReturn = 0;
    
    for(new = list; new; new = new->next){
        if (new->codigo >= iReturn){
            iReturn = new->codigo;   
        }
    }

    return iReturn + 1;
}

void DeleteCliente(){

    const int idDell = (int)(long) newtListboxGetCurrent(lbPessoa);
    
    for(new = list; new; new = new->next){

        if(new->codigo == idDell){
            
            if(new->back){
                new->back->next = new->next;
            }else if(new->next){
                new->next->back = NULL;
                list = new->next;
            }
            
            if(new->next){
                new->next->back = new->back;
            }else if (new->back){
                new->back->next = NULL;
                last = new->back;   
            }else{
                list = NULL;
            }

            free(new);
            break;

        }
    }   
    
    SaveToXml();

    LaodListbox();
}

int LoadToClienteXml(){

    CreateOrOpenFileClienteXml();
    
    list = last = NULL;
    
    if(doc){

        cur = xmlDocGetRootElement(doc);
        cur = cur->children;

        while(cur != NULL){

            if(cur->type == XML_ELEMENT_NODE){    
                new = malloc(sizeof(struct cliente));
                memset(new, '\0', sizeof(struct cliente));

                if(!list){
                    list = new;
                }else{
                    last->next = new;
                    new->back  = last; 
                }

                last = new;

                new->codigo = atoi((char *)xmlGetProp(cur, (const xmlChar *)"codigo"));
                new->nome   = strdup(xmlGetProp(cur,"nome"));
                new->cartao = atol(xmlGetProp(cur,"cartao"));
                new->ativo  = atoi( xmlGetProp(cur,"ativo"));
                
            }
            cur = cur->next;
        }

        return 0;

    }else{

        return 1;
    }
}

void LaodListbox(){

    newtListboxClear(lbPessoa);

    for(new = list; new; new = new->next){
        char caption[500];
        sprintf(caption, "%i - %s",new->codigo, new->nome);
        newtListboxAppendEntry(lbPessoa, caption, (void * ) (long) new->codigo);
    }
}

void SaveToXml(){

    xmlNodePtr clientes = NULL;

    clientes = createRoot(doc, "clientes");

    for(new = list; new; new = new->next){


        xmlNodePtr cliente= NULL;

        cliente  = addChild(clientes, "cliente", NULL);
        
        char cod[2048];
        sprintf(cod, "%i",new->codigo);
        xmlSetProp(cliente, "codigo", cod);
        xmlSetProp(cliente, "nome", new->nome);

        char card[64]; 
        char active[12];
        sprintf(card, "%lu", new->cartao);
        sprintf(active, "%i",new->ativo);

        xmlSetProp(cliente, "cartao", card);
        xmlSetProp(cliente, "ativo", active);   
    }

    xmlSaveFileEnc(FILE_NAME,doc,"ISO-8859-1");
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

// gcc -ggdb -o main main.c -I/usr/include/libxml2 -lxml2 -I/usr/include/newt -lnewt