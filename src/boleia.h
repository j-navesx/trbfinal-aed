#ifndef _H_BOLEIA
#define _H_BOLEIA

typedef struct _bol *boleia;

boleia fillBoleia(user us, char * origem, char * destino,char * data);

char * giveMaster(boleia bol);

char * giveOrigem(boleia bol);

char * giveDestino(boleia bol);

char * giveDate(boleia bol);

int giveHorah(boleia bol);

int giveHoram(boleia bol);

int giveDuracao(boleia bol);

int giveLugares(boleia bol);

#endif