#ifndef _H_SESSION
#define _H_SESSION

#include "boleia.h"
#include "user.h"

typedef struct _sess *session;

session initialize(int capUsers);

void registUser(char * usr, char * name, char * pass, session s);

int logIn(char * username, char * pass, session s);

int userCheck(char * mail, session s);

char * userName(char * mail, session s);

char * userMail(user us);

int userCheckBol(char * mail, char * date, session s);

void newDeslocacao(char * usr, session s, char * origem, char * destino, char * datacmd);

void delDeslocacao(char * usr, char * date, session s);

int checkDeslocacao(char *usr, char * date, session s);

int numEmptySeats(char * mail, char * date, session s);

void newRegist(char * pendura, char * condutor, char * data, session s);

void delBoleia(char * usr, char * date, session s);

iterador listDeslocacoes(char * usr, session s);

iterador listBoleias(char * usr, session s);

iterador listDatas(char * date, session s);

void insertionSortAlpha(boleia * vetor, boleia bol, int size);

iterador listUsersReg(boleia bol);

#endif