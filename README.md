#include <stdio.h>
#include <stdlib.h> //necessário para usar as funções malloc() e free()
#include <string.h>
#include <stdbool.h>

void main()
{

char **Alocar(int num_pokemons){//alocar matrix n_elementos * 30 caracteres;
int i,j;
char **Pokedex;

Pokedex = (char**)malloc (num_pokemons * sizeof (char*)) ;
for (i=0; i < num_pokemons; i++)
   Pokedex[i]= (char*) malloc (10 * sizeof (char)) ;
//preencher a matriz com null
for (i=0; i < num_pokemons; i++)
      Pokedex[i] = NULL ;
}

bool Busca(char Pokemon[10], unsigned int num_pokemons, char **Pokedex){
    int i;

    for (i = 0; i < num_pokemons; i++)
    {
       if (Pokedex[i]==(char*)Pokemon)
           return true; 
    } 

    return false;
}

void addPokemon(char pokemonNovo[10], unsigned int num_pokemons,char **Pokedex){
    //Armazena o pokemon na matriz de char
    
    if(Busca(pokemonNovo[10],num_pokemons,Pokedex)==true){
        int i,j;
        for (i = 0; i < num_pokemons; i++)
        {
           if (Pokedex[i]==NULL){
                Pokedex[i]=(char*)pokemonNovo;
            return ; 
        }
    } 
    return ;
    }
    
}

void removePokemon(int num_pokemons,char **Pokedex,char pokemonDelete[10]){
    int i;

    for (i = 0; i < num_pokemons; i++)
    {
       if (Pokedex[i]==(char*)pokemonDelete){
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
}

void LiberaMatriz(int **M, int m){
  int i;
  for(i = 0; i < m; i++)
    free(M[i]);
  free(M);
}



bool trocaTroca(unsigned int num_pokemons,char** Pokedex,char pokemonEntra[10,char pokemonSai[10]){
    
    if(Busca(pokemonSai[10],num_pokemons,Pokedex)==true){
        
        for (i = 0; i < num_pokemons; i++){
             if (Pokedex[i]==(char*)pokemonSai){
             Pokedex[i]=pokemonEntra;
             return true;
            }
     } 

    return false;    

    }
}
