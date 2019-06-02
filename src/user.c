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

//SECRET ENCRYPTION KEY
const char * key = "aed18!";

//ENCRYPTION FUNCTIONS
void xorstring(char * keyword, int max , char * out);
void encryption(user us,char * pass);

struct _usr{
    char mail[MAXMAIL];
    char * nome;
    char hashedPass[PASS];
    //Dictionary of deslocacoes
    dicionario dicboleias;
    int numDeslocacoes;
    //Dictionary of boleias
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

//* USER FORM

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

//* BOLEIA GETTERS

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

boleia * getVecBoleia (iterador it,int size){
    boleia * vetor = (boleia *) malloc(sizeof(boleia)*size);
    int id=0; 
    while(temSeguinteIterador(it)){
        vetor[id]=seguinteIterador(it);
        id++;
    }
    destroiIterador(it);
    return vetor;
}

//* DESLOCACOES RELATED FUNCTIONS

void addDeslocacao(user us, boleia bol){
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

void remBoleia(user us, char * date){
    boleia bol = removeElemDicionario(us->boleiasregistadas,date);
    us->numBoleias--;
    int pos = getPosUser(bol,getMail(us));
    remPendura(bol,pos);
}

int getnDeslocacoes(user us){
    return us->numDeslocacoes;
}

//* BOLEIAS SORT FUNCTIONS

iterador getDeslocacaoOrd(user us){
    iterador it = iteradorDicionario(us->dicboleias);
    int size = us->numDeslocacoes;
    boleia * vetor = getVecBoleia(it,size);
    insertionSort(vetor,size,compareDate,giveDate);
    return (criaIterador((void **)vetor,size));
}

iterador getBoleiasOrd(user us){
    iterador it = iteradorDicionario(us->boleiasregistadas);
    int size = us->numBoleias;
    boleia * vetor = getVecBoleia(it,size);
    insertionSort(vetor,size,compareDate,giveDate);
    return (criaIterador((void **)vetor,size));
}

//* SORT ALGORITHM

int binarySearch(boleia * vetor, boleia elem, int low, int high, int compare(const char*, const char*), char* giveFunc(boleia)){
    char * elemCh = giveFunc(elem);
    
    if(high <= low){
        if(compare(elemCh,giveFunc(vetor[low]))>0){
            return low+1;
        }
        else{
            return low;
        }
    }
    
    int mid = (low + high)/2;

    if(compare(elemCh,giveFunc(vetor[mid]))==0){ 
        return mid+1; 
    }

    if(compare(elemCh,giveFunc(vetor[mid]))>0){
        return binarySearch(vetor, elem, mid+1, high, compare, giveFunc);
    }

    return binarySearch(vetor, elem, low, mid-1, compare, giveFunc); 
}

void insertionSort(boleia * vetor, int size, int compare(const char*, const char*), char* giveFunc(boleia)){
    boleia selected;
    int i, loc, j;
    for (i = 1; i < size; i++) { 
        j = i - 1; 
        selected = vetor[i]; 
  
        // find location where selected sould be inseretd 
        loc = binarySearch(vetor, selected, 0, j,compare,giveFunc); 
  
        // Move all elements after location to create space 
        while (j >= loc) 
        { 
            vetor[j+1] = vetor[j]; 
            j--; 
        } 
        vetor[j+1] = selected; 
    } 
}

//* DATE COMPARER

int compareDate(const char * date1, const char * date2){
    int result;
    int dia1,mes1,ano1;
    int dia2,mes2,ano2;
    sscanf(date1,"%d-%d-%d",&dia1,&mes1,&ano1);
    sscanf(date2,"%d-%d-%d",&dia2,&mes2,&ano2);
    if(ano1<ano2){
        result = -1;
    }
    else if(ano1==ano2){
        if(mes1<mes2){
            result = -1;
        }
        else if(mes1==mes2){
            if(dia1<dia2){
                result = -1;
            }
            else if(dia1 == dia2){
                result = 0;
            }
            else{
                result = 1;
            }
        }
        else{
            result = 1;
        }
    }
    else{
        result = 1;
    }
    return result;
}

//* PASSWORD CHECKER FUNCTION

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

//* USER INFO GETTERS

char * getName(user us){
    return us->nome;
}
char * getMail(user us){
    return us->mail;
}