#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    //printf("bound to %s, waiting connections\n", addrstr);

    struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }
    char buf[BUFSZ];
 ////----------COMUNICAÇÃO REALIZADA -- TROCA DE MENSAGENS--------------//////
    do{

        char caddrstr[BUFSZ];


        addrtostr(caddr, caddrstr, BUFSZ);
        memset(buf, 0, BUFSZ);

        size_t count = recv(csock, buf, BUFSZ - 1, 0);
        printf("Mensagem<<: %s\n", buf);

        char** Pokedex;//Matriz para armazenar os vetores de char
        int num_pk=20;
        Pokedex=Alocar(num_pk);

        //// separando comando do client
        int i=0;
        char cmd[11];
        memset(cmd, 0, 11);
            while(buf[i]!=' '){
                cmd[i]=buf[i];
                i++;
                }
            cmd[i]='\0';
        //////    printf("cmd:%s\n",cmd);
        //////
            //adicionar ao pokedex
            if (strcmp(cmd,"add")==0){
                char pkNovo[11];
                memset(pkNovo, 0, 11);
                int j=0;
                char textoRetorno[50];
                memset(textoRetorno, 0, 50);
                //i++;
                while(buf[i]!='\0'){
                     if((buf[i]!=' ') || (buf[i]!='\0')){
                     pkNovo[j]=buf[i];
                     j++;
                    
                     }

                     if((buf[i]==' ') || (buf[i]=='\0')){
                        pkNovo[j]='\0';
                        printf("pknovo:%s",pkNovo);
                        addPokemon(pkNovo,num_pk,Pokedex);
                        strcpy(textoRetorno,pkNovo);
                        j=-1;
                        
                     }
                i++;

                //j++;
                }
                memset(cmd, 0, 11);
                strcat(textoRetorno," added ");
                count = send(csock,textoRetorno, strlen(textoRetorno) + 1, 0);
            }

            //troca
            else if(strcmp(cmd,"exchange")==0){ //DIFICIL
                char textoRetorno[50];
                char pkEntra[11];
                int j=0;
                i++;
                while(buf[i]!=' '){//separar primeiro pokemon
                     pkEntra[j]=buf[i];
                    i++;
                    j++;
                }
                pkEntra[i]='\0';

                if (Busca(pkEntra,num_pk,Pokedex)==false){
                    i++;
                    j=0;
                    char pkSai[11];
                    while((buf[i]==' ') || (buf[i]=='\0')){//separa segundo pokemon
                        pkSai[j]=buf[i];
                        i++;
                        j++;
                    }
                    if (Busca(pkSai,num_pk,Pokedex)==true){
                        if(Troca(num_pk,Pokedex,pkEntra,pkSai)==true){
                         strcpy(textoRetorno, pkEntra);
                            strcat(textoRetorno," exchanged");
                        
                         }
                         count = send(csock,textoRetorno, strlen(textoRetorno) + 1, 0);

                    }
                }
                else{
                    i++;
                    j=0;
                    char pkSai[11];
                    while((buf[i]==' ') || (buf[i]=='\0')){//separa segundo pokemon
                        pkSai[j]=buf[i];
                        i++;
                        j++;
                    }
                    strcpy(textoRetorno,pkSai);
                    strcat(textoRetorno," does not exist");

                    count = send(csock,textoRetorno, strlen(textoRetorno) + 1, 0);

                }

                if (Busca(pkEntra,num_pk,Pokedex)==false){
                    strcpy(textoRetorno,pkEntra);
                    strcat(textoRetorno," does not exist");

                    count = send(csock,textoRetorno, strlen(textoRetorno) + 1, 0);

                }
            }
            //imprime lista do pokedex
            else if(strcmp(cmd,"list")==0) {
                for(i=0;i<num_pk;i++){
                    if(Pokedex[i]!=NULL){
                        printf("%s ",Pokedex[i]);
                    }
                }
            }

            //remove pokemon do pokedex
            else if(strcmp(cmd,"remove")==0){
                char pkDell[11];
                int j=0;
                char textoRetorno[50]="remove";

                while(buf[i]!='\0'){
                     pkDell[j]=buf[i];
                     if((buf[i]==' ') || (buf[i]=='\0')){
                        pkDell[i]='\0';
                        if(Busca(pkDell,num_pk,Pokedex)==true){

                            removePokemon(num_pk,Pokedex,pkDell);
                        }
                        j=-1;
                        strcat(textoRetorno,pkDell);
                     }
                i++;
                j++;
                }
                count = send(csock,textoRetorno, strlen(textoRetorno) + 1, 0);

            }

            else{
            memset(buf, 0, 20);
            }

        count = send(csock,cmd, strlen(buf) + 1, 0);

        if (count != strlen(buf) + 1) {
            logexit("send");
        } 
        
    }while(strcmp(buf,"exit")!=0);
    
    close(csock);

    exit(EXIT_SUCCESS);
}