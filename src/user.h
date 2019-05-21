#ifndef _H_USER
#define _H_USER

typedef struct _usr *user;

/***************************************
fillUser - preenche uma estrutura de user
Parametros:
    - mail
    - nome
    - password
Retorno:
    (struct) user
***************************************/
user fillUser(char * mail, char * name, char * pass);

/***************************************
getDeslocacao - devolve a viagem relacionada a data
Parametros:
    - user
    - data
Retorno:
    (struct) boleia
***************************************/
boleia getDeslocacao(user us, char * date);

/***************************************
getBoleia - devolve a boleia relacionada a data
Parametros:
    - user
    - data
Retorno:
    (struct) boleia
***************************************/
boleia getBoleia(user us, char * date);

/***************************************
addDeslocacao - adicona uma nova deslocacao ao user
Parametros:
    - user
    - boleia
***************************************/
void addDeslocacao(user us, boleia bol);

/***************************************
remDeslocacao - remove uma deslocacao do user
Parametros:
    - user
    - data
***************************************/
void remDeslocacao(user us, char * date);

/***************************************
addBoleia - adiciona uma boleia a lista de boleias a que o user esta relacionado
Parametros:
    - user
    - boleia
***************************************/
void addBoleia(user master, boleia bol);

/***************************************
remBoleia - remove o user de uma boleia em que estava registado
Parametros:
    - user
    - data
***************************************/
void remBoleia(user us, char * date);

/***************************************
getnDeslocacoes - devolve o numero de deslocacoes que o user tem
Parametros:
    - user
Retorno:
    (int) numero de deslocacoes
***************************************/
int getnDeslocacoes(user us);

/***************************************
getDeslocacaoOrd - devolve um iterador com as deslocacoes do user ordenadas por data
Parametros:
    - user
Retorno:
    (iterador) lista de deslocacoes
***************************************/
iterador getDeslocacaoOrd(user us);

/***************************************
getBoleiasOrd - devolve um iterador com as boleias em que o user esta registado ordenadas por data
Parametros:
    - user
Retorno:
    (iterador) lista de viagens registadas
***************************************/
iterador getBoleiasOrd(user us);

/***************************************
insertionSort - ordena boleias por data
Parametros:
    - iterador a usar
    - vetor de boleias
***************************************/
void insertionSort(iterador it, boleia * vetor);

/***************************************
compareDate - compara duas datas em formato string
Parametros:
    - data1
    - data2
Retorno:
    1 - data1<data2
    0 - data1>=data2
***************************************/
int compareDate(char * date1, char * date2);

/***************************************
checkpass - verifica se a pass do user e igual a inserida
Parametros:
    - user
    - password a verficar
Retorno:
    1 - caso esteja correta
    0 - caso contrario
***************************************/
int checkpass(user us, char *pass);

/***************************************
getName - devolve o nome do user
Parametros:
    - user
Retorno:
    (char *) nome do user
***************************************/
char * getName(user us);

/***************************************
getMail - devolve o mail do user
Parametros:
    - user
Retorno:
    (char *) mail do user
***************************************/
char * getMail(user us);

#endif