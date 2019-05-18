#ifndef _H_BOLEIA
#define _H_BOLEIA

typedef struct _bol *boleia;

/***************************************
fillBoleia - preenche uma boleia e devolve
Parametros:
    - mail
    - origem
    - destino
    - data (toda a informacao relacionada com a data, hora, duracao e lugares)
Retorno:
    (struct) boleia
***************************************/
boleia fillBoleia(char * mail, char * origem, char * destino,char * data);

/***************************************
addPendura - adiciona um pendura a viagem
Parametros:
    - boleia
    - (user)pendura (usou se o void * para evitar recursividade)
***************************************/
void addPendura(boleia bol, void * pendura);

/***************************************
remPendura - remove um pendura da viagem
Parametros:
    - boleia
    - pos (posicao do user a retirar)
***************************************/
void remPendura(boleia bol, int pos);

/***************************************
getPosUser - devolve a posicao de um user numa boleia
Parametros:
    - boleia
    - email do user
Retorno:
    (int) posicao do user na boleia
***************************************/
int getPosUser(boleia bol, char * us);

/***************************************
seqPenduras - devolve um iterador da sequencia de penduras
Parametros:
    - boleia
Retorno:
    (iterador) iterador da Sequencia
***************************************/
iterador seqPenduras(boleia bol);

/***************************************
giveMaster - devolve o dono da viagem
Parametros:
    - boleia
Retorno:
    (char *) email do dono da viagem
***************************************/
char * giveMaster(boleia bol);

/***************************************
giveOrigem - devolve o local de comeco da viagem
Parametros:
    - boleia
Retorno:
    (char *) origem da viagem
***************************************/
char * giveOrigem(boleia bol);

/***************************************
giveDestino - devolve o local de destino da viagem
Parametros:
    - boleia
Retorno:
    (char *) destino da viagem
***************************************/
char * giveDestino(boleia bol);

/***************************************
giveDate - devolve a data da viagem
Parametros:
    - boleia
Retorno:
    (char *) data da viagem
***************************************/
char * giveDate(boleia bol);

/***************************************
giveHorah - devolve a hora da viagem
Parametros:
    - boleia
Retorno:
    (int) hora da viagem
***************************************/
int giveHorah(boleia bol);

/***************************************
giveHoram - devolve os minutos da hora de viagem
Parametros:
    - boleia
Retorno:
    (int) minutos da hora viagem
***************************************/
int giveHoram(boleia bol);

/***************************************
giveDuracao - devolve a duracao da viagem
Parametros:
    - boleia
Retorno:
    (int) duracao da viagem
***************************************/
int giveDuracao(boleia bol);

/***************************************
giveLugares - devolve o numero de lugares da viagem (no momento inicial)
Parametros:
    - boleia
Retorno:
    (int) numero de lugares
***************************************/
int giveLugares(boleia bol);

/***************************************
givenumPenduras - devolve o numero de penduras inscritos
Parametros:
    - boleia
Retorno:
    (int) numero de penduras inscritos
***************************************/
int givenumPenduras(boleia bol);

#endif