#ifndef _H_USER
#define _H_USER

typedef struct _usr *user;

user fillUser(char * mail, char * name, char * pass);

int checkpass(user us, char *pass);

char * name(user us);

#endif