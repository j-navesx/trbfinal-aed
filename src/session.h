#ifndef _H_SESSION
#define _H_SESSION

#include "user.h"
#include "boleia.h"

typedef struct _sess *session;

session initialize(int capUsers);

void registUser(char * usr, char * name, char * pass, session s);

int checkuser(char * mail, session s);

int logIn(char * username, char * pass, session s);

char * userName(char * mail, session s);

void newDeslocacao(char * usr, session s, char * origem, char * destino, char * datacmd);

void ** sortDeslocacoes(char * usr, session s);

char * getInfo(boleia lista);

boleia * sortLista(boleia * lista,int size);

int compareDate(char * date1, char * date2);

#endif