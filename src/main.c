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

#define MAXL 50
#define MAXC 10

#define MINPASS 4
#define MAXPASS 6

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
void selecBoleia(char * cmd, session s, char * mail);
void selecRetira(char * user, char * cmd, session s);
void selecRemove(char * user, char * cmd, session s);
void selecLista(char * cmd, session s, char * user);
void listMenu(int selection, session s, char * user, char * option);
void listaUser(session s, char * user);
void listaBoleias(session s, char * user);
void listaDate(session s, char * date);
void selecSai(char * user, session s);

//HELPER FUNCTIONS
int checksize(char * input, int size);
int verifypass(char * cmd);
int checkstrdata(char * data);
int checkdata(int dia, int mes, int ano);
int checkhoranminuto(int hora,int minuto);
char * lowerIN(char * input, int size);

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
        printf("> ");
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
    char entrys[MAXL];
    char cmds[MAXC] = "NULL";
    int cmdints = '\0';
    while(cmdints != 6){
        cmds[0] = '\0';
        printf("%s> ",user);
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
                selecBoleia(entrys,s,user);
                break;
            case 3:
                selecRetira(user,entrys,s);
                break;
            case 4:
                selecRemove(user,entrys,s);
                break;
            case 5:
                selecLista(entrys,s,user);
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
    if(userCheck(user,s)){
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
    int tries = 1;
    //USER
    sscanf(cmd,"%*s %s", user);
    if(userCheck(user,s)){
        printf("Utilizador ja existente.\n");
        finish = 0;
    }
    //NAME
    else{
        printf("nome (maximo 50 caracteres): ");
        fgets(name,MAXL,stdin);
        name[strlen(name)-1] = '\0';
        
        //PASSint userCheckBol(char * mail, char * date, session s){

        printf("password (entre 4 e 6 caracteres - digitos e letras): ");
        fgets(passtmp,MAXL,stdin);
      
        while (!(verifypass(passtmp)) && tries++!=3){    
            printf("Password incorrecta.\n");
            printf("password (entre 4 e 6 caracteres - digitos e letras): ");
            fgets(passtmp,MAXL,stdin);
        }
        if(tries<=3){
            //COMPLETED
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
    else if(!checkdata(dia,mes,ano) || !checkhoranminuto(hora,minuto) || duracao<0 || numLugares<0){
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
        printf("Deslocacao registada.  Obrigado %s.\n", userName(usr,s));
    }

    free(origem);
    free(destino);
    free(datacmd);
}

void selecBoleia(char * cmd, session s, char * mail){
    char * master = (char*) malloc(sizeof(char)*MAXL);
    char * data = (char*) malloc(sizeof(char)*MAXL);
   
    sscanf(cmd,"%*s %s %s", master, data);
    if(!userCheck(master,s)){
        printf("Utilizador inexistente.\n");
    }
    else if(!checkstrdata(data)){
        printf("Data invalida.\n");
    }
    else if(strcmp(mail,master)!=0){
        printf("%s nao pode dar boleia a si proprio. Boleia nao registada.\n",userName(mail,s));
    }
    else if(!checkDeslocacao(master,data,s)){
        printf("Deslocacao nao existe.\n");
    }
    else if(!userCheckBol(mail,data,s)){
        printf("%s ja registou uma boleia nesta data. Boleia nao registada.\n",userName(mail,s));
    }
    else if(numEmptySeats(master,data,s)==0){
         printf("%s nao existe lugar. Boleia nao registada.\n",userName(mail,s));
    }
    else{
        newRegist(mail,master,data,s);
        printf("Boleia registada.\n");
    }
}

void selecRetira(char * user, char * cmd, session s){
    char * date = (char*) malloc(sizeof(char)*MAXL);
    sscanf(cmd,"%*s %s", date);
    if(!checkstrdata(date)){
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
    if(!checkstrdata(date)){
        printf("Data invalida.\n");
    }
    else if(!checkDeslocacao(user,date,s)){
        printf("%s nesta data nao tem registo de deslocacao.\n",userName(user,s));
    }
    else{
        //TODO: delDeslocacao
    }
}

void selecLista(char * cmd, session s, char * user){
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
    listMenu(selec,s,user,option);
}

void listMenu(int selection, session s, char * master,char * data){
    switch(selection){
        case 0:
            listaUser(s,master);
            break;
        case 1:
            listaBoleias(s,master);
            break;
        case 2:
            listaUser(s,data);
            break;
        case 3:
            listaDate(s,data);
            break;
        default:
            break;
    }
}

void displayViagens(boleia bol){
    printf("%s\n",giveMaster(bol));
    printf("%s\n%s\n",giveOrigem(bol),giveDestino(bol));
    printf("%s %d:%d %d %d\n",giveDate(bol),giveHorah(bol),giveHoram(bol),giveDuracao(bol),giveLugares(bol));
    printf("Lugares Vagos: %d\n",(giveLugares(bol)-givenumPenduras(bol)));
    if(givenumPenduras(bol)>0){ 
        printf("Boleias registadas:");
        iterador penduras = seqPenduras(bol);
        while(temSeguinteIterador(penduras)){
            char * username = seguinteIterador(penduras);
            printf(" %s;", username);
        }
        printf("\n");
        destroiIterador(penduras);
    }
    else{
        printf("Sem boleias registadas.\n");
    }
    printf("\n");
}

void listaUser(session s, char * user){
    iterador deslocacoes = listDeslocacoes(user,s);
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void listaBoleias(session s, char * user){
    iterador deslocacoes = listBoleias(user,s);
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void listaDate(session s, char * date){
    iterador deslocacoes = listDatas(date,s);
    while(temSeguinteIterador(deslocacoes)){
        displayViagens((boleia)seguinteIterador(deslocacoes));
    }
    destroiIterador(deslocacoes);
}

void selecSai(char * user, session s){
    printf("Fim de sessao. Obrigado %s.\n", userName(user,s));
}

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
    if(letters>0 && numeric > 0 && others == 0 && strlen(pass)>=4 && strlen(pass)<=6){
        valid = 1;
    }
    return valid;
}

int checksize(char * input, int size){
    if(strlen(input)>size){return 1;}
    else{return 0;}
}

int checkstrdata(char * data){
    int dia,mes,ano;
    sscanf(data,"%d-%d-%d",&dia,&mes,&ano);
    return (checkdata(dia,mes,ano));
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
char* lowerIN(char * input, int size){
    char *out = malloc(size);
    int i;
    for(i = 0; i<size; i++){
        out[i] = tolower(input[i]);
    }
    out[i] = '\0';
    return out;
}