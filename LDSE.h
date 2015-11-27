#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define FRACASSO 0
#define SUCESSO 1



typedef struct LDSE *pLDSE, **ppLDSE;

int cria(ppLDSE pp, int tamInfo);
int insereNoInicio(pLDSE p, void *novo);
int insereNoFim(pLDSE p, void *novo);
int insereNaPosLog (pLDSE p, void *novo,unsigned int posLog);
int tamanho(pLDSE p);
void reinicia(pLDSE p);
void destroi(ppLDSE pp);
int buscaNaPosLog(pLDSE p, void *reg, unsigned int posLog);
int buscaNoFim(pLDSE p, void *reg);
int buscaNoInicio(pLDSE p, void *reg);
int removeDaPosLog(pLDSE p, void *reg, unsigned  int posLog);
int removeDoFim(pLDSE p, void *reg);
int removeDoInicio(pLDSE p, void *reg);

void mostra_lista(pLDSE p, void (*mostra_info)(void *));
