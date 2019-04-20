#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "boleia.h"
#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

struct _bol{
    user master;
    char * origem;
    char * destino;
    char data[11];
    int horaH;
    int horaM;
    int duracao;
    int lugaresLivres;
    //Users registados ligados com dicionarios
    dicionario penduras;
};

boleia fillBoleia(user us, char * origem, char * destino,char * data){
    boleia bol = (boleia) malloc(sizeof(struct _bol));
<<<<<<< HEAD:src/boleia.c
    bol->origem = (char *) malloc(strlen(origem));
    bol->destino = (char *) malloc(strlen(destino));
=======
>>>>>>> 336f79890b1f046b2bef1b1d0aaddff4d982a1bb:src/boleia.c
    bol->master = us;
    strcpy(bol->origem, origem);
    strcpy(bol->destino,destino);
    sscanf(data,"%s %d:%d %d %d",bol->data,&bol->horaH,&bol->horaM,&bol->duracao,&bol->lugaresLivres);
    return bol;
}

char * giveData(boleia bol){
    return bol->data;
}