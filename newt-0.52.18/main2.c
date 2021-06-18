#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "newt.h"


int main(void){

    //* FORMS *//
    newtComponent frm;

    //* LABELS *//
    newtComponent lCod, lNome, lCartao, lAtivo;

    //* EDIT *//
    newtComponent edtCod, edtNome, edtcartao;

    //* CHECKBOX *//
    newtComponent ckbAtivo;

    //* BUTTONS *//
    newtComponent btnSair,  btnSalvar;

    //** LIST BOX **//
    newtComponent lbPessoa;

    struct newtExitStruct es;

    //ESTRUTURA DE DADOS
    const char *id, *nome, *cartao, *ativo;
    char result;

    newtInit();
    newtCls();

    newtOpenWindow(10, 5, 80, 16, "Formulario de Cadastro...");

    frm = newtForm(NULL, "This is some help text", 0);

    lCod = newtLabel(3, 1, "Cod...:");
    lNome = newtLabel(3, 2, "Nome..:");
    lCartao = newtLabel(3, 3, "Cartao:");
    lAtivo = newtLabel(3, 4, "Ativo.:");

    edtCod = newtEntry(12, 1, "1", 40, &id, NEWT_FLAG_DISABLED);
    edtNome = newtEntry(12, 2, "", 40, &nome, 0);
    edtcartao = newtEntry(12, 3, "", 40, &cartao, 0);
    ckbAtivo = newtCheckbox(12, 4, ativo, ' ', NULL, &result);

    // lbPessoa = newtListbox(3, 5, 1, NEWT_FLAG_BORDER | NEWT_FLAG_SCROLL | NEWT_FLAG_SHOWCURSOR);
    // NEWT_FLAG_MULTIPLE | NEWT_FLAG_BORDER | NEWT_FLAG_SCROLL | NEWT_FLAG_SHOWCURSOR
    lbPessoa = newtListbox(45, 1, 6, NEWT_FLAG_MULTIPLE | NEWT_FLAG_BORDER | NEWT_FLAG_SCROLL | NEWT_FLAG_SHOWCURSOR);

    newtListboxAppendEntry(lbPessoa, "TESTE 01 sasasas sasasas sasasas", (void *) 1);
    newtListboxAppendEntry(lbPessoa, "TESTE 02 sasasas sasasas sasasas", (void *) 2);
    newtListboxAppendEntry(lbPessoa, "TESTE 03 sasasas sasasas sasasas", (void *) 3);
    newtListboxAppendEntry(lbPessoa, "TESTE 04 sasasas sasasas sasasas", (void *) 4);
    newtListboxAppendEntry(lbPessoa, "TESTE 05 sasasas sasasas sasasas", (void *) 5);
    newtListboxAppendEntry(lbPessoa, "TESTE 06 sasasas sasasas sasasas", (void *) 6);
    newtListboxAppendEntry(lbPessoa, "TESTE 07 sasasas sasasas sasasas", (void *) 7);
    newtListboxAppendEntry(lbPessoa, "TESTE 08 sasasas sasasas sasasas", (void *) 8);
    
    btnSair = newtButton(3, 10, "Sair");
    btnSalvar = newtButton(18, 10, "Salvar");


    newtFormAddComponents(frm,
                          lCod, 
                          lNome, 
                          lCartao,
                          lAtivo,
                          edtCod,
                          edtNome,
                          edtcartao,
                          ckbAtivo,
                          lbPessoa,
                          btnSair, 
                          btnSalvar, 
                          NULL);

    newtRefresh();

    do {
        newtFormRun(frm , &es);

        if (es.reason == NEWT_EXIT_COMPONENT && es.u.co == btnSalvar) {
            newtRefresh();

        }

    } while (es.reason != NEWT_EXIT_COMPONENT || es.u.co == btnSalvar);


    newtPopWindow();
    newtPopWindow();
    newtFinished();
    
    printf("\nCOD : %s \nNOME : %s \nCARTAO : %s \nATIVO : %c \n", id,nome,cartao, result);

    newtFormDestroy(frm);

    return 0;
}