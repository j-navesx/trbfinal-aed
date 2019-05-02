#ifndef _H_USER
#define _H_USER

typedef struct _usr *user;

user fillUser(char * mail, char * name, char * pass);

void addDeslocacao(user us, char *origem, char *destino, char * data);

iterador getDeslocacaoOrd(user us);

int insertionSort(boleia elempos, boleia elem);

int compareDate(char * date1, char * date2);

int getnDeslocacoes(user us);

int checkpass(user us, char *pass);

char * name(user us);

char * mail(user us);

#endif