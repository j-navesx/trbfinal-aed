#ifndef _H_SESSION
#define _H_SESSION

typedef struct _sess *session;

session initialize(int capUsers);

void registUser(char * usr, char * name, char * pass, session s);

int checkuser(char * mail, session s);

int logIn(char * username, char * pass, session s);

char * userName(char * mail, session s);

#endif