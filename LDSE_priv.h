#include "LDSE.h"


typedef struct noLDSE{
 void *dados;
 struct noLDSE *prox;
}NoLDSE,*pNoLDSE;

typedef struct LDSE{ 
  int tamInfo;
  pNoLDSE lista;
}LDSE;

