#ifndef _H_BOLEIA
#define _H_BOLEIA

typedef struct _bol *boleia;

boleia fillBoleia(char * mail, char * origem, char * destino,char * data);

void addPendura(boleia bol, void * pendura);

void remPendura(boleia bol, int pos);

int getPosUser(boleia bol, char * us);

iterador seqPenduras(boleia bol);

char * giveMaster(boleia bol);

char * giveOrigem(boleia bol);

char * giveDestino(boleia bol);

char * giveDate(boleia bol);

int giveHorah(boleia bol);

int giveHoram(boleia bol);

int giveDuracao(boleia bol);

int giveLugares(boleia bol);

int givenumPenduras(boleia bol);

#endif