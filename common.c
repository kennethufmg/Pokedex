#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <arpa/inet.h>
#include "common.h"

void logexit(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage) {
    if (addrstr == NULL || portstr == NULL) {
        return -1;
    }

    uint16_t port = (uint16_t)atoi(portstr); // unsigned short
    if (port == 0) {
        return -1;
    }
    port = htons(port); // host to network short

    struct in_addr inaddr4; // 32-bit IP address
    if (inet_pton(AF_INET, addrstr, &inaddr4)) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    struct in6_addr inaddr6; // 128-bit IPv6 address
    if (inet_pton(AF_INET6, addrstr, &inaddr6)) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = port;
        // addr6->sin6_addr = inaddr6
        memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
        return 0;
    }

    return -1;
}

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize) {
    int version;
    char addrstr[INET6_ADDRSTRLEN + 1] = "";
    uint16_t port;

    if (addr->sa_family == AF_INET) {
        version = 4;
        struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
        if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr,
                       INET6_ADDRSTRLEN + 1)) {
            logexit("ntop");
        }
        port = ntohs(addr4->sin_port); // network to host short
    } else if (addr->sa_family == AF_INET6) {
        version = 6;
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
        if (!inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr,
                       INET6_ADDRSTRLEN + 1)) {
            logexit("ntop");
        }
        port = ntohs(addr6->sin6_port); // network to host short
    } else {
        logexit("unknown protocol family.");
    }
    if (str) {
        snprintf(str, strsize, "IPv%d %s %hu", version, addrstr, port);
    }
}

int server_sockaddr_init(const char *proto, const char *portstr,
                         struct sockaddr_storage *storage) {
    uint16_t port = (uint16_t)atoi(portstr); // unsigned short
    if (port == 0) {
        return -1;
    }
    port = htons(port); // host to network short

    memset(storage, 0, sizeof(*storage));
    if (0 == strcmp(proto, "v4")) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_addr.s_addr = INADDR_ANY;
        addr4->sin_port = port;
        return 0;
    } else if (0 == strcmp(proto, "v6")) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = in6addr_any;
        addr6->sin6_port = port;
        return 0;
    } else {
        return -1;
    }
}
//////////////////------------ FUNÇÕES POKEDEX ------------////////////////////
char **Alocar(int num_pokemons){//alocar matrix n_elementos * 30 caracteres;

int i;
char **Pokedex;

Pokedex = (char**)malloc (num_pokemons * sizeof (char*)) ;
for (i=0; i < num_pokemons; i++)
   Pokedex[i]= (char*) malloc (11 * sizeof (char)) ;
//preencher a matriz com null
for (i=0; i < num_pokemons; i++)
      Pokedex[i] = "VAZIO" ;

return Pokedex;
}

bool Busca(char *Pokemon, unsigned int num_pokemons, char **Pokedex){
    int i;//j;
    //char temp[10];
    for (i = 0; i < num_pokemons; i++)
    {   
       /* for(j=0; j < strlen(Pokedex[i]) ; j++){
            temp[j]=Pokedex[i][j];
        }
        temp[j]='\0';*/
       //if ( strcmp(temp,Pokemon)==0)
       if (strcmp( Pokedex[i], Pokemon)==0)
           return true; 
    } 
    return false;
}

void addPokemon(char *pokemonNovo, unsigned int num_pokemons,char **Pokedex){
    //Armazena o pokemon na matriz de char
    
    if(Busca(pokemonNovo,num_pokemons,Pokedex)==true){
        int i;
        for (i = 0; i < num_pokemons; i++)
        {
           if (Pokedex[i]==NULL){
                //for(j=0; j < strlen(pokemonNovo) ; j++){
                //Pokedex[i][j]= pokemonNovo[j];
                Pokedex[i]=pokemonNovo;
                return ; 
           }
        }
        }
     
    return ;
    }
    
void removePokemon(int num_pokemons,char **Pokedex,char *pokemonDelete){
    int i;

    for (i = 0; i < num_pokemons; i++)
    {
       if (strcmp(Pokedex[i],pokemonDelete)==0){
           Pokedex[i]=NULL;
           return ; 
       }
     } 
    return ;
}

char **reAlocar(int num_pokemons, char **PokedexVelho){//realocar matrix n_elementos * 30 caracteres;
    int i,j;
    char **Pokedex;

    Pokedex = (char**)malloc (2*num_pokemons * sizeof (char*)) ;
    for (i=0; i < num_pokemons; i++)
    Pokedex[i]= (char*) malloc (10 * sizeof (char)) ;
        //preencher a matriz com null
    for (i=0; i < num_pokemons; i++)
      Pokedex[i] = NULL ;

    j=0;
    for (i = 0; i < num_pokemons; i++){
       if (PokedexVelho[i]!=NULL){
            Pokedex[j]=PokedexVelho[i];
            j++; 
       }
    } 
    return Pokedex;
}

void LiberaMatriz(int **M, int m){
  int i;
  for(i = 0; i < m; i++)
    free(M[i]);
  free(M);
}

bool Troca(unsigned int num_pokemons,char** Pokedex,char *pokemonEntra,char* pokemonSai){
    
    if(Busca(pokemonSai,num_pokemons,Pokedex)==true){
        int i;
        for (i = 0; i < num_pokemons; i++){
             if (strcmp(Pokedex[i],pokemonSai)==0){
                strcpy(Pokedex[i],pokemonEntra);
             return true;
             }
        }
    } 
    return false;    
}

char Ordem(const char *mensagem){
    int i=0;
    char cmd[20];
    while(mensagem[i]!=' '){
        cmd[i]=mensagem[i];
        i++;
    }
    printf("%s",cmd);
    return *cmd;
}

int numeroDePokemons(char*mensagem){
    int i=0,j=0;

    while(mensagem[i]!='\0'){
        if(mensagem[i]==' '){
            j++;
        }
        i++;
    }
    return j;
}
