#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <mysql.h>

#include "newt.h"

    MYSQL conn;
    struct cliente *list, *last, *new;
    
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

    struct cliente {
        int codigo;
        char *nome;
        long cartao;
        int ativo;
        struct cliente *next;
        struct cliente *back;
    };

    int create_conn();
    int LoadToCliente();
    void createFrmPrincpial();
    void createFrmCadastro();
    void LaodListbox();
    int GetSeqCodigo();
    void AddCliente();
    void DeleteCliente();
    void EditaCliente();
    void SaveEditCliente();

int main(void){

    struct newtExitStruct es;
    struct newtExitStruct es2;
    
    if (create_conn()){
        LoadToCliente();

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
    }
    
    return(0);
}

int create_conn(){
    mysql_init(&conn);

    if ( mysql_real_connect(&conn, "localhost", "root", "root", "teste", 0, NULL, 0) )
    {
        mysql_query(&conn,"CREATE TABLE IF NOT EXISTS usuario (codigo INTEGER NOT NULL AUTO_INCREMENT, nome VARCHAR(30), cartao SMALLINT, ativo VARCHAR(1), PRIMARY KEY (codigo))");
        return 1;
    }else{
        printf("\nErro na conexao com bando de dados teste no MYSQL...\n");
        return 0;
    }
}

int LoadToCliente(){

    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(&conn,"SELECT * FROM usuario");
    res = mysql_store_result(&conn);

    list = NULL;
    last = NULL;
    new  = NULL;
    
    while(row = mysql_fetch_row(res)){
        new = malloc(sizeof(struct cliente));
        memset(new, '\0', sizeof(struct cliente));

        if(!list){
            list = new;
        }else{
            last->next = new;
            new->back  = last; 
        }

        last = new;

        new->codigo = atoi(row[0]);
        new->nome   = strdup(row[1]);
        new->cartao = atol(row[2]);
        new->ativo  = atoi(row[3]); 
    }
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

void LaodListbox(){

    newtListboxClear(lbPessoa);

    for(new = list; new; new = new->next){
        char caption[500];
        sprintf(caption, "%i - %s",new->codigo, new->nome);
        newtListboxAppendEntry(lbPessoa, caption, (void * ) (long) new->codigo);
    }
}

int GetSeqCodigo(){
    // Retorna sempre o maior codigo do banco de dados.
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(&conn,"SELECT COALESCE(MAX(CODIGO),0) + 1 AS CODIGO FROM usuario");
    res = mysql_store_result(&conn);
    row = mysql_fetch_row(res);

    return atoi(row[0]);
}

void AddCliente(){
    char query[1000];
    char locAtivo = '1';
    int SeqID = GetSeqCodigo();

    if (ativo == '*'){
        locAtivo = 'S';
    }else{
        locAtivo = 'N';
    }

    sprintf(&query[0],"INSERT INTO usuario VALUES (%i,'%s',%s,'%c')",SeqID,nome,cartao,locAtivo);

    mysql_query(&conn,query);

    LoadToCliente();
    LaodListbox();
}

void DeleteCliente(){
    const int idDell = (int)(long) newtListboxGetCurrent(lbPessoa);
    if (idDell > 0){
        char query[500];
        sprintf(&query[0],"DELETE FROM usuario WHERE codigo = %i",idDell);

        mysql_query(&conn,query);
    }

    LoadToCliente();
    LaodListbox();
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
        }
    }
}

void SaveEditCliente(){
    
    char query[1000];
    char locAtivo;
    
    if (ativo == '*'){
        locAtivo = 'S';
    }else{
        locAtivo = 'N';
    }

    sprintf(&query[0],"UPDATE usuario SET NOME = '%s', CARTAO = %s, ATIVO = '%c' WHERE CODIGO = %s",nome,cartao,locAtivo,id);
    mysql_query(&conn,query);

    LoadToCliente();
    LaodListbox();
}

// gcc -ggdb -o main main.c -I/usr/include/libxml2 -lxml2 -I/usr/include/newt -lnewt `mysql_config --cflags --libs`