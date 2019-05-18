#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

#include "boleia.h"
#include "user.h"

#define MAXMAIL 20
#define PASS 6

const char * key = "aed18!";

struct _usr{
    char mail[MAXMAIL];
    char * nome;
    char hashedPass[PASS];
    //Deslocacao (sem ser ordenado)
    dicionario dicboleias;
    int numDeslocacoes;
    //Registos ligados com dicionario
    dicionario boleiasregistadas;
    int numBoleias;
};

void xorstring(char * keyword, int max , char * out){
    for(int i = 0; i<max;i++){
        out[i]=key[i]^keyword[i];
    }
}

void encryption(user us,char * pass){
    xorstring(pass,PASS,us->hashedPass);
}

user fillUser(char * mail, char * name, char * pass){
    user us = (user) malloc(sizeof(struct _usr));
    us->nome = (char * ) malloc(strlen(name));
    strcpy(us->mail, mail);
    strcpy(us->nome, name);
    us->dicboleias = criaDicionario(7,1);
    us->boleiasregistadas = criaDicionario(7,1);
    encryption(us,pass);
    us->numDeslocacoes = 0;
    us->numBoleias = 0;
    return us;
}

boleia getDeslocacao(user us, char * date){
    if(existeElemDicionario(us->dicboleias,date)){
        return (boleia)elementoDicionario(us->dicboleias,date);
    }
    return NULL;
}

boleia getBoleia(user us, char * date){
    if(existeElemDicionario(us->boleiasregistadas,date)){
        return (boleia)elementoDicionario(us->boleiasregistadas,date);
    }
    return NULL;
}

void addDeslocacao(user us, char *origem, char *destino, char * data){
    boleia bol = fillBoleia(mail(us),origem,destino,data);
    adicionaElemDicionario(us->dicboleias,giveDate(bol),bol);
    us->numDeslocacoes++;
}

void remDeslocacao(user us, char * date){
    removeElemDicionario(us->dicboleias,date);
    us->numDeslocacoes--;
}

void addBoleia(user us, boleia bol){
    adicionaElemDicionario(us->boleiasregistadas,giveDate(bol),bol);
    us->numBoleias++;
}

void remBoleia(user us, char * data){
    boleia bol = removeElemDicionario(us->boleiasregistadas,data);
    us->numBoleias--;
    int pos = getPosUser(bol,mail(us));
    remPendura(bol,pos);
}

iterador getDeslocacaoOrd(user us){
    boleia * vetor = (boleia *) malloc(sizeof(boleia) * us->numDeslocacoes);
    int size = us->numDeslocacoes;
    iterador it = iteradorDicionario(us->dicboleias);
    insertionSort(it,vetor);
    return (criaIterador((void **)vetor,size));
}

iterador getBoleiasOrd(user us){
    boleia * vetor = (boleia *) malloc(sizeof(boleia) * us->numBoleias);
    int size = us->numBoleias;
    iterador it = iteradorDicionario(us->boleiasregistadas);
    insertionSort(it,vetor);
    return (criaIterador((void **)vetor,size));
}

void insertionSort(iterador it, boleia * vetor){
    boleia boldic;
    int id = 0;
    int i =0;
    while(temSeguinteIterador(it)){
        boldic = seguinteIterador(it);
        for(i = id; i>0 && compareDate(giveDate(boldic),giveDate(vetor[i-1])) != 0; i--){
            vetor[i] = vetor[i-1];
        }
        vetor[i] = boldic;
        id++;
    }
    destroiIterador(it);
}

int compareDate(char * date1, char * date2){
    int menor = -1;
    int dia1,mes1,ano1;
    int dia2,mes2,ano2;
    sscanf(date1,"%d-%d-%d",&dia1,&mes1,&ano1);
    sscanf(date2,"%d-%d-%d",&dia2,&mes2,&ano2);
    if(ano1<ano2){
        menor = 1;
    }
    else if(ano1==ano2){
        if(mes1<mes2){
            menor = 1;
        }
        else if(mes1==mes2){
            if(dia1<dia2){
                menor = 1;
            }
            else{
                menor = 0;
            }
        }
        else{
            menor = 0;
        }
    }
    else{
        menor = 0;
    }
    return menor;
}

int getnDeslocacoes(user us){
    return us->numDeslocacoes;
}

int checkpass(user us, char *pass){
    pass[strlen(pass)-1] = '\0';
    char * test = (char *) malloc(PASS);
    xorstring(us->hashedPass,PASS,test);
    if(strncmp(test,pass,7)==0){
        return 1;
    }
    else{
        return 0;
    }
}

char * name(user us){
    return us->nome;
}
char * mail(user us){
    return us->mail;
}