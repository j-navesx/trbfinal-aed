#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "boleia.h"

#define MAXC 30

struct _bol{
    //User proprietario
    char partida[MAXC];
    char destino[MAXC];
    char data[11];
    int horaH;
    int horaM;
    int duracao;
    int lugaresLivres;
    //Users registados ligados com dicionarios
};