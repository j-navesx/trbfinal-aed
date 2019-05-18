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


struct _sess{
    //Users dicionario
    dicionario users;
};

//*INITIALIZER
session initialize(int capUsers){
    session s;
    s = (session) malloc(sizeof(struct _sess));
    s->users = criaDicionario(capUsers,1);
    if(s->users == NULL){
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
    return name(us);
}

char * userMail(user us){
    return mail(us);
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
    addDeslocacao(us,origem,destino,datacmd);
}

void delDeslocacao(char * usr, char * date, session s){
    user us = elementoDicionario(s->users,usr);
    remDeslocacao(us,date);
}

int numEmptySeats(char * mail, char * date, session s){
    user master = elementoDicionario(s->users, mail);
    boleia bol = getDeslocacao(master,date);
    return (giveLugares(bol) - givenumPenduras(bol));
}

void newRegist(char * pendura, char * condutor, char * date, session s){
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

iterador listDeslocacoes(char * usr, session s){
    user us = elementoDicionario(s->users,usr);
    return getDeslocacaoOrd(us);
}

iterador listBoleias(char * usr, session s){
    user us = elementoDicionario(s->users,usr);
    return getBoleiasOrd(us);
}

iterador listDatas(char * date, session s){
    boleia * vetor = (boleia *) malloc(sizeof(boleia) * tamanhoDicionario(s->users));
    iterador it = iteradorDicionario(s->users);
    int id = 0;
    while(temSeguinteIterador(it)){
        user us = seguinteIterador(it);
        boleia bol = getDeslocacao(us,date);
        if(bol != NULL){
            insertionSortAlpha(vetor,bol,id);
            id++;
        }
    }
    destroiIterador(it);
    return (criaIterador((void **)vetor,id));
}

void insertionSortAlpha(boleia * vetor, boleia bol, int size){
    int i=0;
    for(i = size; i>0 && strcmp(giveMaster(vetor[i-1]),giveMaster(bol))>0; i--){
        vetor[i] = vetor[i-1];
    }
    vetor[i] = bol;
}

iterador listUsersReg(boleia bol){
    return seqPenduras(bol);
}