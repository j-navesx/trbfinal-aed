#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

#include "boleia.h"
#include "user.h"
#include "session.h"

#define MAXL 50
#define MAXC 10

#define MINPASS 4
#define MAXPASS 6

#define MAXUSERS 10000

struct _sess{
    //Users dicionario
    dicionario users;
    //Deslocacoes por data
    dicionario datalist;
};

//*INITIALIZER
session initialize(int capUsers){
    session s;
    s = (session) malloc(sizeof(struct _sess));
    s->users = criaDicionario(capUsers,1);
    if(s->users == NULL){
        return NULL;
    }
    s->datalist = criaDicionario(capUsers,1);
    if(s->datalist == NULL){
        return NULL;
    }
    return s;
}

//*USER RELATED ACTIONS
void registUser(char * usr, char * name, char * pass, session s){
    user us = fillUser(usr,name,pass);
    adicionaElemDicionario(s->users,usr,us);
}

int userCheck(char * mail, session s){
    return existeElemDicionario(s->users,mail);
}

int userLogin(char * mail, char * pass, session s){
    user us;
    us = elementoDicionario(s->users,mail);
    return (checkpass(us,pass));
}

char * userName(char * mail, session s){
    user us;
    us = elementoDicionario(s->users,mail);
    return getName(us);
}

char * userMail(user us){
    return getMail(us);
}

int userCheckBol(char * mail, char * date, session s){
    int existe = 0;
    user us = elementoDicionario(s->users,mail);
    boleia bol = getBoleia(us,date);
    if(bol != NULL){
        if(getPosUser(bol,mail)!=0){
            existe = 1;
        } 
    }
    return existe;
}

//*DESLOCACOES RELATED ACTIONS

int checkDeslocacao(char *usr, char * date, session s){
    int exist = 0;
    user us = elementoDicionario(s->users,usr);
    boleia bol = getDeslocacao(us,date);
    if(bol != NULL){
        exist = 1;
    }
    return exist;
}

void newDeslocacao(char * usr, session s, char * origem, char * destino, char * datacmd){
    user us = elementoDicionario(s->users,usr);
    boleia bol = fillBoleia(getMail(us),origem,destino,datacmd);
    addDeslocacao(us,bol);
    char * date = (char*) malloc(sizeof(char)* MAXL);
    sscanf(datacmd,"%s",date);
    //If Date doesnt exist in database
    if(!existeElemDicionario(s->datalist,date)){
        adicionaElemDicionario(s->datalist,date,criaDicionario(MAXUSERS,1));
        dicionario d = elementoDicionario(s->datalist,date);
        adicionaElemDicionario(d,usr,bol);
    }
    else{
        dicionario d = elementoDicionario(s->datalist,date);
        adicionaElemDicionario(d,usr,bol);
    }
}

void delDeslocacao(char * usr, char * date, session s){
    user us = elementoDicionario(s->users,usr);
    remDeslocacao(us,date);
    if(existeElemDicionario(s->datalist,date)){
        dicionario d = elementoDicionario(s->datalist,date);
        removeElemDicionario(d,usr);
    }
}

int numEmptySeats(char * mail, char * date, session s){
    user master = elementoDicionario(s->users, mail);
    boleia bol = getDeslocacao(master,date);
    return (giveLugares(bol) - givenumPenduras(bol));
}

void newPendura(char * pendura, char * condutor, char * date, session s){
    user condt = elementoDicionario(s->users,condutor);
    boleia bol = getDeslocacao(condt, date);
    user pend = elementoDicionario(s->users,pendura);
    addPendura(bol,(void*)pend);
    addBoleia(pend,bol);
}

int existUsersReg(char *usr, char * date, session s){
    int exist = 0;
    user us = elementoDicionario(s->users,usr);
    boleia bol = getDeslocacao(us,date);
    if(givenumPenduras(bol)>0){
        exist = 1;
    }
    return exist;
}

void delBoleia(char * usr, char * date, session s){
    user us = elementoDicionario(s->users,usr);
    remBoleia(us,date);
}

//* LIST FUNCTIONS

iterador listDeslocacoes(char * usr, session s){
    user us = elementoDicionario(s->users,usr);
    return getDeslocacaoOrd(us);
}

iterador listBoleias(char * usr, session s){
    user us = elementoDicionario(s->users,usr);
    return getBoleiasOrd(us);
}

iterador listDatas(char * date, session s){
    int size = 0;
    boleia * vetor = (boleia *) malloc(sizeof(boleia)*MAXUSERS);
    if(existeElemDicionario(s->datalist,date)){
        dicionario d = elementoDicionario(s->datalist,date);
        iterador it = iteradorDicionario(d);
        size = tamanhoDicionario(d);
        vetor = getVecBoleia(it,size);
        insertionSort(vetor,size,strcmp,giveMaster);
    }
    
    return (criaIterador((void **)vetor,size));
}

iterador listUsersReg(boleia bol){
    return seqPenduras(bol);
}