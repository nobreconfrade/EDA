#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define FRACASSO 0
#define SUCESSO 1



typedef struct LDDE *pLDDE, **ppLDDE;

int cria(ppLDDE pp, int tamInfo);
int insereNoInicio(pLDDE p, void *novo);
int insereNoFim(pLDDE p, void *novo);
int insereNaPosLog (pLDDE p, void *novo,unsigned int posLog);
int tamanho(pLDDE p);
void reinicia(pLDDE p);
void destroi(ppLDDE pp);
int buscaNaPosLog(pLDDE p, void *reg, unsigned int posLog);
int buscaNoFim(pLDDE p, void *reg);
int buscaNoInicio(pLDDE p, void *reg);
int removeDaPosLog(pLDDE p, void *reg, unsigned  int posLog);
int removeDoFim(pLDDE p, void *reg);
int removeDoInicio(pLDDE p, void *reg);

void mostra_lista(pLDDE p, void (*mostra_info)(void *));
