#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "session.h"
#include "boleia.h"
#include "user.h"

#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

struct _sess{
    sequencia boleias;
    //Users dicionario
    dicionario users;
    int countBoleias;
};

session initialize(int capUsers){
    session s;
    s = (session) malloc(sizeof(struct _sess));
    s->users = criaDicionario(capUsers,1);
    s->countBoleias = 0;
    if(s->users == NULL){
        return NULL;
    }
    return s;
}

void registUser(char * usr, char * name, char * pass, session s){
    user us = fillUser(usr,name,pass);
    adicionaElemDicionario(s->users,usr,us);
}

int checkuser(char * mail, session s){
    return existeElemDicionario(s->users,mail);
}

int logIn(char * mail, char * pass, session s){
    user us;
    us = elementoDicionario(s->users,mail);
    return (checkpass(us,pass));
}

char * userName(char * mail, session s){
    user us;
    us = elementoDicionario(s->users,mail);
    return name(us);
}

void newDeslocacao(char * usr){

}