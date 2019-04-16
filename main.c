#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "boleia.h"

#define MAXL 50
#define MAXC 10

//MENUS
void inicialmenu();
void sessionmenu(char * user);
int imenuselection(char * cmd);
int smenuselection(char * cmd);

//INICIAL SELECTIONS
void selecAjudaI();
char * selecEntrada(char * cmd);
void selecRegista(char * cmd);
void selecTermina();

//SESSION SELECTIONS
void selecAjudaS();
void selecNova();
void selecBoleia();
void selecRetira();
void selecRemove();
void selecLista();
void selecSai();


int main(){
    inicialmenu();
    return 0;
}

//*INICIAL MENU
void inicialmenu(){
    char entryi[MAXL];
    char cmdi[MAXC] = "NULL";
    int cmdinti = '\0';
    char * user;
    while(cmdinti != 3){
        printf(">");
        fgets(entryi,MAXL-1,stdin);
        sscanf(entryi,"%s",cmdi);
        cmdinti = imenuselection(cmdi);
        switch(cmdinti){
            case 0:
                selecAjudaI();
                break;
            case 1:
                if((user = selecEntrada(entryi) )!= NULL){
                    sessionmenu(user);
                }
                break;
            case 2:
                selecRegista(entryi);
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
void sessionmenu(char * user){
    char entrys[MAXL];
    char cmds[MAXC] = "NULL";
    int cmdints = '\0';
    while(cmdints != 6){
        printf("%s>",user);
        fgets(entrys,MAXL-1,stdin);
        sscanf(entrys,"%s",cmds);
        cmdints = smenuselection(cmds);
        switch(cmdints){
            case 0:
                selecAjudaS();
                break;
            case 1:
                selecNova();
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
                selecLista();
                break;
            case 6:
                selecSai();
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

char * selecEntrada(char * cmd){
    printf("password: ");
    return "admin";
}

void selecRegista(char * cmd){

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

void selecNova(){

}

void selecBoleia(){

}

void selecRetira(){

}

void selecRemove(){

}

void selecLista(){

}

void selecSai(){

}
