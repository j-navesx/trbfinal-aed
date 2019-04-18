#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

#define MAXMAIL 20
#define PASS 7
#define KEY "aed18!"

struct _usr{
    char mail[MAXMAIL];
    char * nome;
    char hashedPass[PASS];
    //Deslocacao
    sequencia deslocacoes;
    int numDeslocacoes;
    //Registos ligados com dicionario
    dicionario boleiasregistadas;
    int numBoleias;
};

void xorstring(char * key,char * keyword, int max , char * out){
    for(int i = 0; i<max;i++){
        out[i]=key[i]^keyword[i];
    }
}

void encryption(user us,char * pass){
    char * key = (char *) malloc(PASS);
    strcpy(key, KEY);
    xorstring(key,pass,PASS,us->hashedPass);
    free(key);
}

user fillUser(char * mail, char * name, char * pass){
    user us = (user) malloc(sizeof(struct _usr));
    us->nome = (char * ) malloc(strlen(name));
    strcpy(us->mail, mail);
    strcpy(us->nome, name);
    encryption(us,pass);
    us->numDeslocacoes = 0;
    us->numBoleias = 0;
    return us;
}

int checkpass(user us, char *pass){
    char * key = (char *) malloc(PASS);
    strcpy(key, KEY);
    char * test = (char *) malloc(PASS);
    xorstring(key,us->hashedPass,PASS,test);
    free(key);
    if(!strncmp(test,pass,8)){
        return 1;
    }
    else{
        return 0;
    }
}

char * name(user us){
    return us->nome;
}