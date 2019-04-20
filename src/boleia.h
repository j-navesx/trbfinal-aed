#ifndef _H_BOLEIA
#define _H_BOLEIA

typedef struct _bol *boleia;

boleia fillBoleia(user us, char * origem, char * destino,char * data);

char * giveData(boleia bol);

#endif