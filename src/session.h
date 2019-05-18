#ifndef _H_SESSION
#define _H_SESSION

#include "boleia.h"
#include "user.h"

typedef struct _sess *session;

/***************************************
initialize - comeca uma sessao do programa
Parametros:
    - capUsers (capacidade maxima prevista de users)
Retorno:
    (struct) session
***************************************/
session initialize(int capUsers);

/***************************************
registUser - regista um user na base de dados
Parametros:
    - user (mail)
    - user (nome)
    - password
    - session
***************************************/
void registUser(char * usr, char * name, char * pass, session s);

/***************************************
userLogin - faz login de um user
Parametros:
    - user (mail)
    - password
    - session
Retorno:
    1 - se o login foi feito com sucesso
    0 - se o contrario
***************************************/
int userLogin(char * username, char * pass, session s);

/***************************************
userCheck - verifica se o user existe
Parametros:
    - user (mail)
    - session
Retorno:
    1 - caso exista
    0 - caso contrario 
***************************************/
int userCheck(char * mail, session s);

/***************************************
userName - devolve o nome do user
Parametros:
    - user (mail)
    - session
Retorno:
    (char *) nome do user
***************************************/
char * userName(char * mail, session s);

/***************************************
userMail - devolve o mail de um user
Parametros:
    - user (struct)
Retorno:
    (char *) mail do user
***************************************/
char * userMail(user us);

/***************************************
userCheckBol - verifica se um user esta registado numa viagem
Parametros:
    - user (mail)
    - data (da viagem)
    - session
Retorno:
    1 - se existe
    0 - caso contrario
***************************************/
int userCheckBol(char * mail, char * date, session s);

/***************************************
newDeslocacao - regista uma nova deslocacao para um user
Parametros:
    - user (mail)
    - session
    - local de origem
    - local de destino
    - datacmd (uma string com a data hora duracao e numero de lugares)
***************************************/
void newDeslocacao(char * usr, session s, char * origem, char * destino, char * datacmd);

/***************************************
delDeslocacao - elimina uma deslocacao
Parametros:
    - user (mail)
    - data (da viagem)
    - session
***************************************/
void delDeslocacao(char * usr, char * date, session s);

/***************************************
checkDeslocacao - verifica se existe uma deslocacao de um user numa data
Parametros:
    - user (mail)
    - data
    - session
Retorno:
    1 - caso exista
    0 - caso contrario
***************************************/
int checkDeslocacao(char *usr, char * date, session s);

/***************************************
numEmptySeats - devolve o numero de lugares livres numa viagem
Parametros:
    - user (mail)
    - data
    - session
Retorno:
    (int) numero de lugares livres
***************************************/
int numEmptySeats(char * mail, char * date, session s);

/***************************************
newPendura - adiciona um novo pendura a viagem 
Parametros:
    - pendura (mail)
    - condutor (mail)
    - data
    - session
***************************************/
void newPendura(char * pendura, char * condutor, char * data, session s);

/***************************************
existUsersReg - verifica se existem useres registados numa viagem
Parametros:
    - user (mail)
    - data
    - session
Retorno:
    1 - caso exista
    0 - caso contrario
***************************************/
int existUsersReg(char *usr, char * date, session s);

/***************************************
delBoleia - retira um user da boleia
Parametros:
    - user (mail)
    - data
    - session    
***************************************/
void delBoleia(char * usr, char * date, session s);

/***************************************
listDeslocacoes - devolve iterador para listar as deslocacoes
Parametros:
    - user (mail)
    - session
Retorno:
    (iterador) iterador de deslocacoes
***************************************/
iterador listDeslocacoes(char * usr, session s);

/***************************************
listBoleias - devolve iterador para listar as boleias em que esta registado
Parametros:
    - user (mail)
    - session
Retorno:
    (iterador) iterador de boleias
***************************************/
iterador listBoleias(char * usr, session s);

/***************************************
listDatas - devolve iterador para listar as viagens de uma data
Parametros:
    - data
    - session
Retorno:
    (iterador) iterador de viagens de uma data
***************************************/
iterador listDatas(char * date, session s);

/***************************************
insertionSortAlpha - algoritmo de ordenacao por ordem alfabetica
Parametros:
    - vetor (boleias)
    - boleia (elemento a inserir)
    - size (tamanho do vetor)
***************************************/
void insertionSortAlpha(boleia * vetor, boleia bol, int size);

/***************************************
listUsersReg - iterador para listar users registados numa boleia
Parametros:
    - boleia
Retorno:
    (iterador) iterador de users registados
***************************************/
iterador listUsersReg(boleia bol);

#endif