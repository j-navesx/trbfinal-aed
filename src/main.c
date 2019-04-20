#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "session.h"

#define MAXL 50
#define MAXC 10
#define MAXPASS 7

#define MAXUSERS 10000

//MENUS
void inicialmenu(session s);
void sessionmenu(char * user, session s);
int imenuselection(char * cmd);
int smenuselection(char * cmd);

//INICIAL SELECTIONS
void selecAjudaI();
int selecEntrada(char * user,char * cmd, session s);
int selecRegista(char * cmd, session s);
void selecTermina();

//SESSION SELECTIONS
void selecAjudaS();
void selecNova(char * usr, session s);
void selecBoleia();
void selecRetira();
void selecRemove();
void selecLista(char * cmd, session s);
void listMenu(int selection);
void selecSai(char * user, session s);

//HELPER FUNCTIONS
int checksize(char * input, int size);
int checkdata(int dia, int mes, int ano);
int checkhoranminuto(int hora,int minuto);

int main(){
    session s = initialize(MAXUSERS);
    inicialmenu(s);
    return 0;
}

//*INICIAL MENU
void inicialmenu(session s){
    char entryi[MAXL];
    char cmdi[MAXC] = "NULL";
    int cmdinti = '\0';
    char * user = (char*) malloc(MAXL);
    while(cmdinti != 3){
        cmdi[0] = '\0';
        printf(">");
        fgets(entryi,MAXL-1,stdin);
        sscanf(entryi,"%s",cmdi);
        cmdinti = imenuselection(cmdi);
        switch(cmdinti){
            case 0:
                selecAjudaI();
                break;
            case 1:
                sscanf(entryi,"%*s %s",user);
                if(selecEntrada(user,entryi,s)){
                    sessionmenu(user,s);
                }
                break;
            case 2:
                if(selecRegista(entryi,s)){
                    printf("Registo efectuado.\n");
                }
                else{
                    printf("Registo nao efectuado.\n");
                }
                break;
            case 3:
                selecTermina();
                break;
            default:
                printf("Comando inexistente.\n");
                break;
        }
    }
}

//*SESSION MENU
void sessionmenu(char * user, session s){
    char entrys[MAXL];
    char cmds[MAXC] = "NULL";
    int cmdints = '\0';
    while(cmdints != 6){
        cmds[0] = '\0';
        printf("%s>",user);
        fgets(entrys,MAXL-1,stdin);
        sscanf(entrys,"%s",cmds);
        cmdints = smenuselection(cmds);
        switch(cmdints){
            case 0:
                selecAjudaS();
                break;
            case 1:
                selecNova(user,s);
                break;
            case 2:
                selecBoleia();
                break;
            case 3:
                selecRetira();
                break;
            case 4:
                selecRemove();
                break;
            case 5:
                selecLista(entrys,s);
                break;
            case 6:
                selecSai(user,s);
                break;
            default:
                printf("Comando inexistente.\n");
                break;
        }
    }
}


int imenuselection(char * cmd){
    int cmdint;
    char * cmds[] = {"ajuda","entrada","regista","termina"};
    for(int i=0; i<(sizeof(cmds)/8);i++){
        if(!strcmp(cmd,cmds[i])){
            cmdint = i;
        }
    }
    return cmdint;
}

int smenuselection(char * cmd){
    int cmdint;
    char * cmds[] = {"ajuda","nova","boleia","retira","remove","lista","sai"};
    for(int i=0; i<(sizeof(cmds)/8);i++){
        if(!strcmp(cmd,cmds[i])){
            cmdint = i;
        }
    }
    return cmdint;
}


//INICIAL SELECT
void selecAjudaI(){
    printf("ajuda - Mostra os comandos existentes\n");
    printf("termina - Termina a execucao do programa\n");
    printf("regista - Regista um novo utilizador no programa\n");
    printf("entrada - Permite a entrada (\"login\") dum utilizador no programa\n");
}

int selecEntrada(char * user,char * cmd, session s){
    int tries = 1;
    char * pass = (char*) malloc(MAXPASS);
    if(checkuser(user,s)){
        printf("password: ");
        fgets(pass,MAXL,stdin);
        while(!logIn(user,pass,s)){
            printf("Password incorreta.\n");
            if(tries == 3){
                return 0;
            }
            printf("password: ");
            fgets(pass,MAXL,stdin);
            tries+=1;
        }
    }
    else{
        printf("Utilizador nao existente.\n");
        return 0;
    }
    free(pass);
    return 1;
}

int selecRegista(char * cmd, session s){
    int finish = -1;
    char * user = (char * ) malloc(MAXL);
    char * name = (char * ) malloc(MAXL);
    char * passtmp = (char *) malloc(MAXL);
    char pass[MAXPASS];
    int tries = 0;
    sscanf(cmd,"%*s %s", user);
    if(checkuser(user,s)){
        printf("Utilizador ja existe.\n");
        finish = 0;
    }
    else{
        printf("nome (maximo 50 caracteres): ");
        fgets(name,MAXL,stdin);
        name[strlen(name)-1] = '\0';
        while ((!(checksize(passtmp,3)) || (checksize(passtmp,MAXPASS))) && tries++!=3){    
            printf("password (entre 4 e 6 caracteres - digitos e letras): ");
            fgets(passtmp,MAXL,stdin);
            if ((!(checksize(passtmp,3)) || (checksize(passtmp,MAXPASS))) && tries!=0){
                printf("Password incorreta.\n");
            }
        }
        if(tries<=3){
            strncpy(pass,passtmp,MAXPASS);
            registUser(user,name,pass,s);
            finish = 1;
        }
        else{
            printf("Password incorreta.\n");
            finish = 0;
        }
    }
    free(name);
    free(user);
    return finish;
}

void selecTermina(){
    printf("Obrigado. Ate a proxima.\n");
}


//SESSION SELECT
void selecAjudaS(){
    printf("ajuda - Mostra os comandos existentes\n");
    printf("sai - Termina a sessao deste utilizador no programa\n");
    printf("nova - Regista uma nova deslocacao\n");
    printf("lista - Lista todas ou algumas deslocacoes registadas\n");
    printf("boleia - Regista uma boleia para uma dada deslocacao\n");
    printf("retira - Retira uma dada boleia\n");
    printf("remove - Elimina uma dada deslocacao\n");
}

void selecNova(char * usr, session s){
    char * origem = (char *) malloc(MAXL);
    char * destino = (char *) malloc(MAXL);
    char * datacmd = (char *) malloc(MAXL);
    int dia,mes,ano;
    int hora,minuto = -1;
    int duracao = -1;
    int numLugares = -1;
    
    fgets(origem,MAXL,stdin);
    fgets(destino,MAXL,stdin);
    fgets(datacmd,MAXL,stdin);

    if((sscanf(datacmd,"%d-%d-%d %d:%d %d %d",&dia,&mes,&ano,&hora,&minuto,&duracao,&numLugares)) != 7){
        printf("Dados invalidos.\n");
    }
    else if(!checkdata(dia,mes,ano) && !checkhoranminuto(hora,minuto) && duracao<0 && numLugares<0){
        printf("Dados invalidos.\n");
    }
    else{
        sprintf(datacmd,"%d-%d-%d %d:%d %d %d",dia,mes,ano,hora,minuto,duracao,numLugares);
        newDeslocacao(usr,s,origem,destino,datacmd);
    }

    free(origem);
    free(destino);
    free(datacmd);
}

void selecBoleia(){

}

void selecRetira(){

}

void selecRemove(){

}

void selecLista(char * cmd, session s){
    char * option = (char *) malloc(MAXL);
    sscanf(cmd,"%*s %s",option);
    int selec = -1;
    //KEYWORDS
    char * cmds[] = {"minhas","boleias",};
    for(int i=0; i<(sizeof(cmds)/8);i++){
        if(!strcmp(option,cmds[i])){
            selec = i;
        }
    }
    //MAIL
    if(strchr(option,'@')!=NULL){
        selec = 2;
    }
    //DATE
    else if(strchr(option,'-')!=NULL){
        selec = 3;
    }
    listMenu(selec);
}

void listMenu(int selection){
    switch(selection){
        case 0:
            printf("Minhas\n");
            //TODO: Printf Minhas
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

void selecSai(char * user, session s){
    printf("Fim de sessao.  Obrigado %s.\n", userName(user,s));
}

int checksize(char * input, int size){
    if(strlen(input)>size){return 1;}
    else{return 0;}
}

int checkdata(int dia, int mes, int ano){
    int bisexto = 0;
    int valid = 1;
    if (ano >= 1800 && ano <= 9999){
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
            bisexto = 1;
        }
        if(mes >= 1 && mes <= 12){
            if (mes == 2){
                if (bisexto && dia == 29){
                    valid = 1;
                }
                else if (dia > 28){
                    valid = 0;
                }
            }
 
            else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
                if (dia > 30){
                    valid = 0;
                }
            }

            else if(dia > 31){            
                valid = 0;
            }        
        }
        
        else{
            valid = 0;
        }
 
    }
    else{
        valid = 0;
    }
    return valid;
}

int checkhoranminuto(int hora,int minuto){
    int valid;
    if(hora>=0 && hora<=24){
        if(minuto>=0 && minuto<60){
            valid = 1;
        }
        else{
            valid = 0;
        }
    }
    else{
        valid = 0;
    }
    return valid;
}