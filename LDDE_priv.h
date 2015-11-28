#include "LDDE.h"


typedef struct noLDDE{
 void *dados;
 struct noLDDE *prox;
 struct noLDDE *ant;
}NoLDDE,*pNoLDDE;

typedef struct LDDE{ 
  int tamInfo;
  pNoLDDE lista;
}LDDE;

