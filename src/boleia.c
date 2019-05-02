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
};

boleia fillBoleia(char * mail, char * origem, char * destino,char * data){
    boleia bol = (boleia) malloc(sizeof(struct _bol));
    bol->origem = (char *) malloc(strlen(origem));
    bol->destino = (char *) malloc(strlen(destino));
    bol->mail = mail;
    strcpy(bol->origem, origem);
    strcpy(bol->destino,destino);
    sscanf(data,"%s %d:%d %d %d",bol->data,&bol->horaH,&bol->horaM,&bol->duracao,&bol->lugaresLivres);
    bol->penduras = criaSequencia(bol->lugaresLivres);
    return bol;
}

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