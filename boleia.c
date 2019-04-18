#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "boleia.h"
#include "user.h"
#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

struct _bol{
    user master;
    char * partida;
    char * destino;
    char data[11];
    int horaH;
    int horaM;
    int duracao;
    int lugaresLivres;
    //Users registados ligados com dicionarios
    dicionario penduras;
};

boleia fillBoleia(){
    boleia bol = (boleia) malloc(sizeof(struct _bol));
    return bol;
}