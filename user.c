#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"

#define MAXMAIL 20
#define KEY "aed18!"

struct _usr{
    char mail[MAXMAIL];
    char hashedPass[7];
    //Boleias
    //Registos ligados com dicionario
};