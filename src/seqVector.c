#include <stdlib.h>
#include <stdio.h>

#include "iterador.h"
#include "sequencia.h"

/* Estrutura de dados: sequencia implementada em vector */
struct _sequencia{
	void * * elems; // apontador para vector de enderecos de elementos
	int numElems;
	int capacidade; // capacidade corrente do vector
};


sequencia criaSequencia(int cap){
	sequencia s;
	s = (sequencia) malloc(sizeof(struct _sequencia));
	s->elems = (void **) malloc(sizeof(void*)*cap);
	if(s->elems == NULL){
		free(s);
		return NULL;
	}
	s->capacidade = cap;
	s->numElems = 0;
	return s;
}


void destroiSequencia (sequencia s){
	free(s);
}


void destroiSeqElems(sequencia s, void (*destroi)(void *) ){
	for(int i=0; i< s->numElems;i++){
		destroi(s->elems[i]);
	}
	free(s->elems);
	destroiSequencia(s);
}


int vaziaSequencia(sequencia s){
	int vazia = 1;
	for(int i = 0; i<s->capacidade; i++){
		if(s->elems != NULL){
			vazia = 0;
		}
	}
	return vazia;
}


int tamanhoSequencia(sequencia s){
	return s->numElems;
}


void * elementoPosSequencia(sequencia s, int i){
	return s->elems[i-1];
}


void adicionaPosSequencia(sequencia s, void * elem, int i){
	s->numElems++;
    if (i < s->numElems) {
        for(int k= s->numElems; k > i; k--) {
        s->elems[k]= s->elems[k-1];
        }
    }
    s->elems[i-1]= elem;
}


void * removePosSequencia(sequencia s, int i){
	void ** backup;
	backup = (void**) malloc(sizeof(void*));
	backup = s->elems[i-1];
	for(int j = i-1; j>s->numElems-1; j++){
		s->elems[j] = s->elems[j+1];
	}
	s->numElems--;
	return backup;
}


iterador iteradorSequencia(sequencia s){
	//CUIDADO: DEVE DAR AO ITERADOR UMA COPIA DO VECTOR A PERCORRER
	void ** vector = (void **) malloc(sizeof(void*)*s->numElems);
	for (int i=0;i<s->numElems;i++){
		vector[i] = s->elems[i];
	}
	return criaIterador(vector,s->numElems);
}
