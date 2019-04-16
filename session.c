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

void registUser(char * user, char * name, char * pass){

}