/*
 * dicTabDis.c
 *
 *  Created on: 12 de Abr de 2014
 *      Author: fernanda
 */

#include <stdlib.h>

#include "iterador.h"
#include "dicionario.h"
#include "chaves.h"
#include "noSimples.h"
#include "tuplo.h"


/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos não podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario{
	noSimples * elems; // apontador para vector de noSimples (lista com cabeça)
	int numElems;
	int capacidade; // capacidade prevista
	int tamanho; // tamanho do vector criado
	int tipoCh; // 0-inteiro; 1-string
};

/* Prototipos das funcoes associadas a um dicionario */

/* função auxiliar para calcular o primo maior que n */

int primo(int n){
	int nextPrime = 0;
	if((n+1)==1){
		return 2;
	}
	for(int i = (n+1); i < (n*2);i++){
		int isPrime = 1;
		for(int j = 2; j < (i-1); j++){
			if((i%j)==0){
				isPrime = 0;
			}
		}
		if(isPrime){
			return i;
		}
	}
	return 0;
}

/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
     cap - capacidade prevista do dicionario
     TipoChave – 0 – inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
dicionario criaDicionario(int cap, int tipoChave){
	dicionario d;
	int i;
	d = (dicionario) malloc(sizeof(struct _dicionario));
	if ( d == NULL) return NULL;
	d->tamanho = primo(2*cap);
	d->elems = (noSimples*)malloc(sizeof(noSimples) * d->tamanho);
	if (d->elems == NULL){
		free(d);
		return NULL;
	}
	for (i=0;i<d->tamanho;i++)
		d->elems[i] = NULL;
	d->numElems = 0;
	d->capacidade = cap;
	d->tipoCh =tipoChave;
	return d;
}

/***********************************************
destroiDicionario - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario.
Parametros:	d - dicionario a destruir
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicionario (dicionario d ){
	int i = 0;
	noSimples  aux;
	tuplo t;
	for(;i<d->tamanho;i++){
		aux = d->elems[i];
		while (aux != NULL){
			d->elems[i] = segNoSimples(aux);
			t = (tuplo) elemNoSimples(aux);
			destroiNoSimples(aux);
			destroiTuplo(t);
			aux = d->elems[i];
		}
	}
	free(d);
}

/***********************************************
destroiDicEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicEElems(dicionario d, void (*destroi)(void *) ){
	int i = 0;
	noSimples  aux;
	tuplo t;
	for(;i<d->tamanho;i++){
		aux = d->elems[i];
		while (aux != NULL){
			d->elems[i] = segNoSimples(aux);
			t = elemNoSimples(aux);
			destroi(segTuplo(t));
			destroiNoSimples(aux);
			destroiTuplo(t);
			aux = d->elems[i];
		}
	}
	free(d);
}

/***********************************************
vazioDicionario - Indica se o dicionario está vazio.
Parametros:
	d - dicionario
Retorno: 1- caso dicionario vazio; 0 - caso contrário
Pre-condicoes: d != NULL
***********************************************/
int vazioDicionario(dicionario d){
	if (d->numElems == 0)
		return 1;
	return 0;
}

/***********************************************
tamanhoDicionario - Consulta o numero de elementos no dicionario.
Parametros:
	d - dicionario
Retorno: numero de elementos no dicionario
Pre-condicoes: d != NULL
***********************************************/
int tamanhoDicionario(dicionario d){
	return d->numElems;
}
/***********************************************
existeElemDicionario – Indica se o elemento  com a chave dada existe no dicionario.
Parametros:
	d – dicionario
	ch – endereço da chave do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int existeElemDicionario(dicionario d, void * ch){
	if (elementoDicionario(d,ch) != NULL)
		return 1;
	return 0;
}

/***********************************************
elementoDicionario - retorna o elemento no dicionario com a chave dada
Parametros:
	d – dicionario	ch - endereco da chave do elemento
Retorno: retorna o elemento
Pre-condicoes: d != NULL
***********************************************/
void * elementoDicionario(dicionario d, void * ch){
	tuplo t;
	noSimples auxNo;
	int pos = dispersao(ch,d->tamanho,d->tipoCh);
	auxNo = d->elems[pos];
	while (auxNo != NULL){
		t = elemNoSimples(auxNo);
		if (igualChaves(priTuplo(t), ch,d->tipoCh) == 1)
			return segTuplo(t);
		auxNo = segNoSimples(auxNo);
	}
	return NULL;
}

/***********************************************
adicionaElemDicionario - Adiciona o elemento dado no dicionario, se não existir um elemento com a mesma chave.
Parametros:
	d – dicionario
	ch - endereco da chave do elemento
	elem - endereco do elemento
Retorno: Retorna 1 se adicionar, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int adicionaElemDicionario(dicionario d, void * ch, void * elem){
	int pos;
	noSimples auxNo;
	if (existeElemDicionario(d,ch) == 1)
		return 0;
	pos = dispersao(ch,d->tamanho,d->tipoCh);
	auxNo = criaNoSimples((void *)criaTuplo(d->tipoCh,ch,elem),NULL);
	if(d->elems[pos] != NULL){
		atribuiSegNoSimples(auxNo,d->elems[pos]);
	}
	d->elems[pos] = auxNo;
	d->numElems++;
	return 1;
}

/***********************************************
removeElemDicionario - Remove o elemento com a chave dada no dicionario, se existir.
Parametros:
	d – dicionario	ch – endereco da chave
Retorno: Retorna o elemento, caso exista ou NULL, caso contrario
Pre-condicoes: d != NULL
***********************************************/
void * removeElemDicionario(dicionario d, void * ch){
	int i;
	tuplo t;
	void * elem;
	void * auxCh;
	noSimples auxNo, antNo = NULL;
	int pos = dispersao(ch,d->tamanho,d->tipoCh);
	auxNo = d->elems[pos];
	if (auxNo == NULL)
		return 0;
	for(i=1; igualChaves(priTuplo(elemNoSimples(auxNo)),ch,d->tipoCh)==0; i++){
		antNo = auxNo;
		auxNo = segNoSimples(auxNo);
	}
	if(i==1){
		d->elems[pos] = segNoSimples(auxNo);
	}
	else{
		atribuiSegNoSimples(antNo,segNoSimples(auxNo));
	}
	d->numElems--;
	elem = segTuplo(elemNoSimples(auxNo));
	destroiNoSimples(auxNo);
	return elem;
}

/***********************************************
iteradorDicionario - Cria e devolve um iterador para os elementos do dicionario.
Parametros:
	d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorDicionario(dicionario d){
	int count = 0;
	void * * vector = malloc(sizeof(void*)* d->numElems);
	noSimples auxNo;
	for(int i = 0; count != d->numElems; i++){
		if(d->elems[i] != NULL){
			auxNo = d->elems[i];
			do{
				vector[count] = segTuplo((tuplo)elemNoSimples(auxNo));
				auxNo = segNoSimples(auxNo);
				count++;
			}while(auxNo != NULL);
		}
	}
	return criaIterador(vector,d->numElems);
}


/***********************************************
iteradorChaveDicionario - Cria e devolve um iterador para as chaves dos elementos do dicionario.
Parametros:
	d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorChaveDicionario(dicionario d){
	int count = 0;
	void * * vector = malloc(sizeof(void*)* d->numElems);
	noSimples auxNo;
	for(int i = 0; count != d->numElems; i++){
		if(d->elems[i] != NULL){
			auxNo = d->elems[i];
			do{
				vector[count] = priTuplo((tuplo)elemNoSimples(auxNo));
				auxNo = segNoSimples(auxNo);
				count++;
			}while(auxNo != NULL);
		}
	}
	return criaIterador(vector,d->numElems);
}




