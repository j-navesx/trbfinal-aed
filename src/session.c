#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "boleia.h"
#include "session.h"

#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

struct _sess{
    //Users dicionario
    dicionario users;
    int countBoleias;
};

//*INITIALIZER
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

//*USER RELATED ACTIONS
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

//*DESLOCACOES RELATED ACTIONS
void newDeslocacao(char * usr, session s, char * origem, char * destino, char * datacmd){
    user us = elementoDicionario(s->users,usr);
    addDeslocacao(us,origem,destino,datacmd);
    s->countBoleias++;
}

void ** sortDeslocacoes(char * usr, session s){
    user us = elementoDicionario(s->users,usr);
    int numDeslocacao = getnDeslocacoes(us);
    void ** lista = malloc(sizeof(boleia)*getnDeslocacoes(us));
    void ** sorted = malloc(sizeof(boleia)*getnDeslocacoes(us));
    getDeslocacao(us,lista);
    *sorted = sortLista(*lista,getnDeslocacoes(us));
    return sorted;
}

char * getInfo(boleia lista){
    char * info = malloc(sizeof(lista));
    
    char * master = giveMaster(lista);
    char * origem = giveOrigem(lista);
    char * destino = giveDestino(lista);
    char * data = giveDate(lista);
    int horaH = giveHorah(lista);
    int horaM = giveHoram(lista);
    int duracao = giveDuracao(lista);
    int lugaresLivres = giveLugares(lista);

    sprintf(info,"%s %s %s %s %d:%d %d %d",master, origem,destino,data,horaH,horaM,duracao,lugaresLivres);
    return info;
}

boleia * sortLista(boleia * lista,int size){
    int i, j;
    boleia key;
    for (i = 1; i < size; i++) { 
        key = lista[i];
        j = i - 1;
        while (j >= 0 && !compareDate(giveDate(lista[j]),giveDate(key))) { 
            lista[j + 1] = lista[j]; 
            j = j - 1; 
        } 
        lista[j + 1] = key; 
    } 

    return lista;
}

int compareDate(char * date1, char * date2){
    int menor = -1;
    int dia1,mes1,ano1;
    int dia2,mes2,ano2;
    sscanf(date1,"%d-%d-%d",&dia1,&mes1,&ano1);
    sscanf(date1,"%d-%d-%d",&dia2,&mes2,&ano2);
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