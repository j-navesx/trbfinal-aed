#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "iterador.h"
#include "sequencia.h"
#include "dicionario.h"

#define MAXMAIL 20
#define KEY "aed18!"

struct _usr{
    char mail[MAXMAIL];
    char * nome;
    char hashedPass[7];
    //Deslocacao
    sequencia deslocacoes;
    //Registos ligados com dicionario
    dicionario boleiasregistadas;
};

