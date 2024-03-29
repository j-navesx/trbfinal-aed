#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "iterador.h"
#include "sequencia.h"

#include "boleia.h"
#include "user.h"
#include "session.h"

#define MAXL 50 //MAX LINE CHARACTERS
#define MAXC 10 //MAX COMMAND CHARACTERS

#define MINPASS 4 //PASS MINIMUM
#define MAXPASS 6 //PASS MAXIMUM

#define MAXUSERS 10000 //MAX USERS

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
void selecBoleia(char * cmd, session s, char * mail);
void selecRetira(char * user, char * cmd, session s);
void selecRemove(char * user, char * cmd, session s);
void selecLista(char * cmd, session s, char * user);
void listMenu(int selection, session s, char * user, char * option);
void listaMinhas(session s, char * user);
void listaUser(session s, char * user);
void listaBoleias(session s, char * user);
void listaDate(session s, char * date, char * user);
void selecSai(char * user, session s);

//HELPER FUNCTIONS
int verifypass(char * cmd);
int checkstrdate(char * date);
int checkdate(int dia, int mes, int ano);
int checkhoranminuto(int hora,int minuto);
char * lowerIN(char * input, int size);

int main(){
    session s = initialize(MAXUSERS);
    inicialmenu(s);
    return 0;
}

//*INICIAL MENU
void inicialmenu(session s){
    char cmdi[MAXL];
    char selecti[MAXC] = "NULL";
    int selecinti = '\0';
    char * user = (char*) malloc(MAXL);
    while(selecinti != 3){
        selecti[0] = '\0';
        printf("> ");
        fgets(cmdi,MAXL-1,stdin);
        sscanf(cmdi,"%s",selecti);
        selecinti = imenuselection(selecti);
        switch(selecinti){
            case 0:
                selecAjudaI();
                break;
            case 1:
                sscanf(cmdi,"%*s %s",user);
                if(selecEntrada(user,cmdi,s)){
                    sessionmenu(user,s);
                }
                break;
            case 2:
                if(selecRegista(cmdi,s)){
                    printf("Registo efetuado.\n");
                }
                else{
                    printf("Registo nao efetuado.\n");
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
    char cmds[MAXL];
    char selects[MAXC] = "NULL";
    int selecints = '\0';
    while(selecints != 6){
        selects[0] = '\0';
        printf("%s> ",user);
        fgets(cmds,MAXL-1,stdin);
        sscanf(cmds,"%s",selects);
        selecints = smenuselection(selects);
        switch(selecints){
            case 0:
                selecAjudaS();
                break;
            case 1:
                selecNova(user,s);
                break;
            case 2:
                selecBoleia(cmds,s,user);
                break;
            case 3:
                selecRetira(user,cmds,s);
                break;
            case 4:
                selecRemove(user,cmds,s);
                break;
            case 5:
                selecLista(cmds,s,user);
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

//* MENU FUNCTIONS NUMBER ATRIBUTION

int imenuselection(char * cmd){
    int cmdint = -1;
    char * cmdl = lowerIN(cmd, strlen(cmd));
    char * cmds[] = {"ajuda","entrada","regista","termina"};
    for(int i=0; i<(sizeof(cmds)/8);i++){
        if(!strcmp(cmdl,cmds[i])){
            cmdint = i;
        }
    }
    return cmdint;
}

int smenuselection(char * cmd){
    int cmdint = -1;
    char * cmdl = lowerIN(cmd, strlen(cmd));
    char * cmds[] = {"ajuda","nova","boleia","retira","remove","lista","sai"};
    for(int i=0; i<(sizeof(cmds)/8);i++){
        if(!strcmp(cmdl,cmds[i])){
            cmdint = i;
        }
    }
    return cmdint;
}

//* INICIAL SELECT

void selecAjudaI(){
    printf("ajuda - Mostra os comandos existentes\n");
    printf("termina - Termina a execucao do programa\n");
    printf("regista - Regista um novo utilizador no programa\n");
    printf("entrada - Permite a entrada (\"login\") dum utilizador no programa\n");
}

int selecEntrada(char * user,char * cmd, session s){
    int tries = 1;
    char * pass = (char*) malloc(MAXPASS);
    if(userCheck(user,s)){
        printf("password: ");
        fgets(pass,MAXL,stdin);
        while(!userLogin(user,pass,s)){
            printf("Password incorrecta.\n");
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
    int tries = 1;

    sscanf(cmd,"%*s %s", user);
    if(userCheck(user,s)){
        printf("Utilizador ja existente.\n");
        finish = 0;
    }
    else{
        printf("nome (maximo 50 caracteres): ");
        fgets(name,MAXL,stdin);
        name[strlen(name)-1] = '\0';
        

        printf("password (entre 4 e 6 caracteres - digitos e letras): ");
        fgets(passtmp,MAXL,stdin);
        passtmp[strlen(passtmp)-1] = '\0';

        while (!(verifypass(passtmp)) && tries++!=3){    
            printf("Password incorrecta.\n");
            printf("password (entre 4 e 6 caracteres - digitos e letras): ");
            fgets(passtmp,MAXL,stdin);
            passtmp[strlen(passtmp)-1] = '\0';
        }
        if(tries<=3){
            strncpy(pass,passtmp,MAXPASS);
            registUser(user,name,pass,s);
            finish = 1;
        }
        else{
            printf("Password incorrecta.\n");
            finish = 0;
        }
    }
    return finish;
}

void selecTermina(){
    printf("Obrigado. Ate a proxima.\n");
}

//* SESSION SELECT

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
    char * datastr = (char *) malloc(MAXL);
    int dia,mes,ano;
    int hora,minuto = -1;
    int duracao = -1;
    int numLugares = -1;
    
    fgets(origem,MAXL,stdin);
    origem[strlen(origem)-1] = '\0';
    fgets(destino,MAXL,stdin);
    destino[strlen(destino)-1] = '\0';
    fgets(datacmd,MAXL,stdin);

    sscanf(datacmd,"%d-%d-%d",&dia, &mes, &ano);
    sprintf(datastr,"%d-%d-%d",dia,mes,ano);

    if((sscanf(datacmd,"%d-%d-%d %d:%d %d %d",&dia,&mes,&ano,&hora,&minuto,&duracao,&numLugares)) != 7){
        printf("Dados invalidos.\n");
        printf("Deslocacao nao registada.\n");
    }
    else if(!checkdate(dia,mes,ano) || !checkhoranminuto(hora,minuto) || duracao<0 || numLugares<0){
        printf("Dados invalidos.\n");
        printf("Deslocacao nao registada.\n");
    }
    else if(checkDeslocacao(usr,datastr,s)){
        printf("%s ja tem uma deslocacao registada nesta data.\n",userName(usr,s));
        printf("Deslocacao nao registada.\n");
    }
    else{
        sprintf(datacmd,"%d-%d-%d %d:%d %d %d",dia,mes,ano,hora,minuto,duracao,numLugares);
        newDeslocacao(usr,s,origem,destino,datacmd);
        printf("Deslocacao registada. Obrigado %s.\n", userName(usr,s));
    }

}

void selecBoleia(char * cmd, session s, char * mail){
    char * master = (char*) malloc(sizeof(char)*MAXL);
    char * data = (char*) malloc(sizeof(char)*MAXL);
   
    sscanf(cmd,"%*s %s %s", master, data);
    
    if(!userCheck(master,s)){
        printf("Utilizador nao existente.\n");
    }
    else if(!checkstrdate(data)){
        printf("Data invalida.\n");
    }
    else if(strcmp(mail,master)==0){
        printf("%s nao pode dar boleia a si proprio. Boleia nao registada.\n",userName(mail,s));
    }
    else if(!checkDeslocacao(master,data,s)){
        printf("Deslocacao nao existe.\n");
    }
    else if(userCheckBol(mail,data,s)){
        printf("%s ja registou uma boleia nesta data. Boleia nao registada.\n",userName(mail,s));
    }
    else if(numEmptySeats(master,data,s)==0){
         printf("%s nao existe lugar. Boleia nao registada.\n",userName(mail,s));
    }
    else{
        newPendura(mail,master,data,s);
        printf("Boleia registada.\n");
    }
}

void selecRetira(char * user, char * cmd, session s){
    char * date = (char*) malloc(sizeof(char)*MAXL);
    
    sscanf(cmd,"%*s %s", date);
    
    if(!checkstrdate(date)){
        printf("Data invalida.\n");
    }
    else if(!userCheckBol(user,date,s)){
        printf("%s nesta data nao tem registo de boleia.\n",userName(user,s));
    }
    else{
        delBoleia(user,date,s);
        printf("%s boleia retirada.\n", userName(user,s));
    }
}

void selecRemove(char * user, char * cmd, session s){
    char * date = (char*) malloc(sizeof(char)*MAXL);
    
    sscanf(cmd,"%*s %s",date);
    
    if(!checkstrdate(date)){
        printf("Data invalida.\n");
    }
    else if(!checkDeslocacao(user,date,s)){
        printf("%s nesta data nao tem registo de deslocacao.\n",userName(user,s));
    }
    else if(existUsersReg(user,date,s)){
        printf("%s ja nao pode eliminar esta deslocacao.\n",userName(user,s));
    }
    else{
        delDeslocacao(user,date,s);
        printf("Deslocacao removida.\n");
    }
}

//* LISTA OPTIONS

void selecLista(char * cmd, session s, char * user){
    char * option = (char *) malloc(MAXL);
    int selec = -1;
    
    sscanf(cmd,"%*s %s",option);
    
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
    listMenu(selec,s,user,option);
}

//* LISTA SELECTER

void listMenu(int selection, session s, char * master,char * data){
    switch(selection){
        case 0:
            listaMinhas(s,master);
            break;
        case 1:
            listaBoleias(s,master);
            break;
        case 2:
            listaUser(s,data);
            break;
        case 3:
            listaDate(s,data,master);
            break;
        default:
            listaUser(s,data);
            break;
    }
}

//* LIST DISPLAY FUNCTION

void displayViagens(boleia bol){
    printf("%s\n",giveMaster(bol));
    printf("%s\n%s\n",giveOrigem(bol),giveDestino(bol));
    printf("%s %d:%d %d %d\n",giveDate(bol),giveHorah(bol),giveHoram(bol),giveDuracao(bol),giveLugares(bol));
    printf("Lugares vagos: %d\n",(giveLugares(bol)-givenumPenduras(bol)));
    if(givenumPenduras(bol)>0){ 
        printf("Boleias:");
        iterador penduras = seqPenduras(bol);
        while(temSeguinteIterador(penduras)){
            char * username = seguinteIterador(penduras);
            printf(" %s", username);
            if(temSeguinteIterador(penduras)){
                printf(";");
            }
        }
        printf("\n");
        destroiIterador(penduras);
    }
    else{
        printf("Sem boleias registadas.\n");
    }
    printf("\n");
}

//* LISTA FUNCTIONS

void listaMinhas(session s, char * user){
    iterador deslocacoes = listDeslocacoes(user,s);
    
    if(temSeguinteIterador(deslocacoes)==0){
        printf("%s nao tem deslocacoes registadas.\n",userName(user,s));
    }
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void listaUser(session s, char * user){
    iterador deslocacoes = listDeslocacoes(user,s);
    
    if(temSeguinteIterador(deslocacoes)==0){
        printf("Nao existem deslocacoes registadas para esse utilizador.\n");
    }
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void listaBoleias(session s, char * user){
    iterador deslocacoes = listBoleias(user,s);
    
    if(temSeguinteIterador(deslocacoes)==0){
        printf("%s nao tem boleias registadas.\n",userName(user,s));
    }
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void listaDate(session s, char * date, char * user){
    iterador deslocacoes = listDatas(date,s);
    
    if(temSeguinteIterador(deslocacoes)==0){
        printf("%s nao existem deslocacoes registadas para %s.\n",userName(user,s), date);
    }
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void selecSai(char * user, session s){
    printf("Fim de sessao. Obrigado %s.\n", userName(user,s));
}

//* HELPER FUNCTIONS

//* PASSWORD CONDITIONS VERIFIER

int verifypass(char * pass){
    int valid = 0;
    int numeric = 0, letters = 0, others = 0;
    
    for(int i = 0; i < strlen(pass); i++){
        if(isalpha(pass[i])){
            letters++;
        }
        if(isdigit(pass[i])){
            numeric++;
        }
        if(ispunct(pass[i])){
            others++;
        }
    }
    
    if(letters>0 && numeric > 0 && others == 0 && strlen(pass)>=MINPASS && strlen(pass)<=MAXPASS){
        valid = 1;
    }
    
    return valid;
}

//* DATE CHECKERS

int checkstrdate(char * date){
    int dia,mes,ano;
    
    sscanf(date,"%d-%d-%d",&dia,&mes,&ano);
    
    return (checkdate(dia,mes,ano));
}

int checkdate(int dia, int mes, int ano){
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
    
    if(ano<=0||mes<=0||dia<=0){
        valid = 0;
    }
    
    return valid;
}

//* TIME CHECKER

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

//* LOWER INPUT FUNCTION

char* lowerIN(char * input, int size){
    char *out = malloc(size);
    int i;
    
    for(i = 0; i<size; i++){
        out[i] = tolower(input[i]);
    }

    out[i] = '\0';
    
    return out;
}