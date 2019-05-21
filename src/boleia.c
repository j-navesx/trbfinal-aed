#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

#include "boleia.h"
#include "user.h"

struct _bol{
    char * mail;
    char * origem;
    char * destino;
    char data[11];
    int horaH;
    int horaM;
    int duracao;
    int lugaresLivres;
    //sequencia de users
    sequencia penduras;
    int numPenduras;
};

//* DESLOCACAO FORM

boleia fillBoleia(char * mail, char * origem, char * destino,char * data){
    boleia bol = (boleia) malloc(sizeof(struct _bol));
    bol->origem = (char *) malloc(strlen(origem));
    bol->destino = (char *) malloc(strlen(destino));
    bol->mail = mail;
    strcpy(bol->origem, origem);
    strcpy(bol->destino,destino);
    sscanf(data,"%s %d:%d %d %d",bol->data,&bol->horaH,&bol->horaM,&bol->duracao,&bol->lugaresLivres);
    bol->penduras = criaSequencia(bol->lugaresLivres);
    bol->numPenduras = 0;
    return bol;
}

//* PENDURA FUNCTIONS

void addPendura(boleia bol, void * pendura){
    bol->numPenduras++;
    adicionaPosSequencia(bol->penduras,pendura,bol->numPenduras);
    
}

void remPendura(boleia bol, int pos){
    removePosSequencia(bol->penduras,pos);
    bol->numPenduras--;
}

int getPosUser(boleia bol, char * us){
    iterador it = iteradorSequencia(bol->penduras);
    int pos = 0;
    int id = 0;
    while(temSeguinteIterador(it) && pos == 0){
        id++;
        char * m = getMail((user)seguinteIterador(it));
        if(strcmp(m,us) == 0){
            pos = id;
        }
    }
    destroiIterador(it);
    return pos;
}

iterador seqPenduras(boleia bol){
    return iteradorSequencia(bol->penduras);
}

//* GIVE FUNCTIONS

char * giveMaster(boleia bol){
    return bol->mail;
}
char * giveOrigem(boleia bol){
    return bol->origem;
}
char * giveDestino(boleia bol){
    return bol->destino;
}
char * giveDate(boleia bol){
    return bol->data;
}
int giveHorah(boleia bol){
    return bol->horaH;
}
int giveHoram(boleia bol){
    return bol->horaM;
}
int giveDuracao(boleia bol){
    return bol->duracao;
}
int giveLugares(boleia bol){
    return bol->lugaresLivres;
}
int givenumPenduras(boleia bol){
    return bol->numPenduras;
}