#ifndef _H_USER
#define _H_USER

typedef struct _usr *user;

user fillUser(char * mail, char * name, char * pass);

boleia getDeslocacao(user us, char * date);

boleia getBoleia(user us, char * date);

void addDeslocacao(user us, char *origem, char *destino, char * data);

void addBoleia(user master, boleia bol);

void remBoleia(user us, char * data);

iterador getDeslocacaoOrd(user us);

iterador getBoleiasOrd(user us);

void insertionSort(iterador it, boleia * vetor);

int compareDate(char * date1, char * date2);

int getnDeslocacoes(user us);

int checkpass(user us, char *pass);

char * name(user us);

char * mail(user us);

#endif