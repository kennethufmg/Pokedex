#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>


void logexit(const char *msg);

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage);

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init(const char *proto, const char *portstr,
                         struct sockaddr_storage *storage);

// FUNÇOES POKEDEX

char **Alocar(int num_pokemons);

bool Busca(char *Pokemon, unsigned int num_pokemons, char **Pokedex);

void addPokemon(char *pokemonNovo, unsigned int num_pokemons,char **Pokedex);

void removePokemon(int num_pokemons,char **Pokedex,char *pokemonDelete);
    
char **reAlocar(int num_pokemons, char **PokedexVelho);
    
void LiberaMatriz(int **M, int m);

bool Troca(unsigned int num_pokemons,char** Pokedex,char *pokemonEntra,char *pokemonSai);

char Ordem(const char *mensagem);

int numeroDePokemons(char*mensagem);
