#include "LDDE_priv.h"

/*************** CRIA ***************/
int cria(ppLDDE pp, int tamInfo)
{   int ret = FRACASSO;
	if(((*pp)=(pLDDE)malloc(sizeof(LDDE)))==NULL)
		ret = FRACASSO;
	else
	{	(*pp)->lista=NULL;
        (*pp)->tamInfo=tamInfo;
        ret = SUCESSO;
	}
    return ret;
}

/*************** INSERE NO INICIO ***************/
int insereNoInicio(pLDDE p, void *novo)
{  pNoLDDE temp;
   int ret = FRACASSO;
   if((temp=(NoLDDE *)malloc(sizeof(NoLDDE)))!=NULL)
   { if((temp->dados = (void *) malloc(p->tamInfo)) !=NULL )
     {   memcpy(temp->dados,novo,p->tamInfo);
 		 temp->prox=p->lista;
         p->lista=temp;
         ret = SUCESSO;
     }
     else
       free(temp);
	}
   return ret;
}

/*************** INSERE NO FINAL ***************/
int insereNoFim(pLDDE p, void *novo)
{ 	pNoLDDE temp, aux;
	int ret = FRACASSO;
	if((temp=(pNoLDDE)malloc(sizeof(NoLDDE)))!= NULL)
	{ if((temp->dados = (void *) malloc(p->tamInfo))!=NULL)
	     {   memcpy(temp->dados,novo,p->tamInfo);
        	 temp->prox = NULL;
		 if(p->lista==NULL)
		 {	p->lista=temp;
        		//temp->ant=NULL;
		 }
		 else
		 {	aux=p->lista;
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=temp;
			//temp->ant=aux;
		 }
         ret = SUCESSO;
     }
     else
      free(temp);
   }
   return ret;
}

/*************** INSERE NA POSIÇÃO LÓGICA ***************/
int insereNaPosLog (pLDDE p, void *novo, unsigned int posLog)
{ pNoLDDE temp, pre,pos;
  unsigned int cont=0, ret=FRACASSO;
  if( p->lista != NULL && posLog > 0)
  { cont = 1;
    temp = (pNoLDDE) malloc(sizeof(NoLDDE));
    if(temp!=NULL)
    {
      if((temp->dados = (void *) malloc(p->tamInfo))!=NULL)
      {	
            memcpy(temp->dados,novo,p->tamInfo);
      	    if(posLog == cont)/*PosLog == 1: inserção de um novo primeiro elemento*/
      	    {
      	      	temp->prox = p->lista;
		        p->lista = temp;
           	    ret = SUCESSO;
            }
            else /* posLog >= 2, no minimo igual a dois */
            {
                pre=p->lista;
		        pos = p->lista->prox;/*pos:apontara p/ no de dados na posLog==cont*/
           	    if (pos != NULL)
		        {
		            cont = 2;
                    while(cont < posLog && pos->prox != NULL)/*1<posLog<=tam.dalista*/
                    {
                        pre=pos;
			            pos = pos->prox;
                	    cont++;
                    }
                    if (cont == posLog)
                	{
                	    temp->prox=pos;
        	            pre->prox = temp;
                   	    ret = SUCESSO;
                 	}
                }  
            }
      }
    }
    else
        free(temp);
  }
  return ret;/*posLog nao existe na lista: lista vazia ou PosLog>tamLista*/
}

/*************** REMOVE DO INICIO ***************/
int removeDoInicio(pLDDE p, void *reg)
{  	int ret = FRACASSO;
	pNoLDDE aux=NULL;
	if(p->lista != NULL)
	{  	memcpy(reg,p->lista->dados,p->tamInfo);
      		free(p->lista->dados);
		aux=p->lista;
		p->lista=p->lista->prox;
		free(aux);
      		ret = SUCESSO;
	}
   return ret;
}


/*************** REMOVE DO FINAL ***************/
int removeDoFim(pLDDE p, void *reg)
{
	pNoLDDE aux, pre;
	int ret = FRACASSO;
	if(p->lista != NULL)
	{	pre=p->lista;
		aux=p->lista->prox;
		if(aux == NULL) // existe apenas um unico elemento
		{	memcpy(reg,pre->dados,p->tamInfo);			
	       		free(pre->dados);
			free(pre);
			p->lista=NULL;
		}
		else
		{	while(aux->prox != NULL)
			{	pre=aux;				
				aux=aux->prox;
			}
			pre->prox=NULL;
			memcpy(reg,aux->dados,p->tamInfo);
       			free(aux->dados);
	         	free (aux);
			
		}
	 	ret = SUCESSO;
	}
   	return ret;
}

/*************** REMOVE DA POSIÇÃO LÓGICA ***************/
int removeDaPosLog(pLDDE p, void *reg, unsigned int posLog)
{  pNoLDDE pos=NULL,pre=NULL;
   unsigned int cont=0, ret = FRACASSO;
   if( p->lista != NULL && posLog > 0)
   { cont = 1;
     if(posLog == cont)/*PosLog == 1: inserção de um novo primeiro elemento*/
     	ret = removeDoInicio(p, reg);
         else /* posLog >= 2, no minimo igual a dois */
         {	pre=p->lista;
		pos = p->lista->prox;/*pos:apontara p/ no de dados na posLog==cont*/
           	if (pos != NULL)
		{cont = 2;

                 while(cont < posLog && pos->prox != NULL)/* 1 < posLog <= tam.dalista*/
                 {  	pre=pos;
			pos = pos->prox;
                	cont++;
                 }
              	if (cont == posLog) /* encontrou a posLog ? */
             	{ 
                  pre->prox = pos->prox;
		  memcpy(reg,pos->dados,p->tamInfo);
                  free(pos->dados);
                  free(pos);
                  ret = SUCESSO;
              	}
           }
     }
    }
    return ret;/*posLog nao existe na lista*/
}



/*************** BUSCA NO INICIO ***************/
int buscaNoInicio(pLDDE p, void *reg)
{  int ret = FRACASSO;
   if(p->lista != NULL)
	{ memcpy(reg,p->lista->dados,p->tamInfo);
      ret = SUCESSO;
	}
   return ret;
}


/*************** BUSCA NO FINAL ***************/
int buscaNoFim(pLDDE p, void *reg)
{	pNoLDDE aux;
	int ret = FRACASSO;
	if(p->lista != NULL)
	{ aux=p->lista;
	  while(aux->prox!=NULL)
      	   aux=aux->prox;

	  memcpy(reg,aux->dados,p->tamInfo);
      ret = SUCESSO;
	}
   return ret;
}

/*************** BUSCA NA POSIÇÃO LÓGICA ***************/
int buscaNaPosLog(pLDDE p, void *reg, unsigned int posLog)
{	int cont, ret = FRACASSO;
	pNoLDDE pos;
	if(p->lista != NULL && posLog > 0)
	{	cont = 1;
		pos = p->lista;
		while(cont < posLog && pos->prox != NULL )
		{  	pos = pos->prox;
			cont++;
		}
		if(cont == posLog)
        {
            memcpy(reg,pos->dados,p->tamInfo);
        	ret = SUCESSO;
		}
	}
	return ret;
}

/*************** TAMANHO ***************/
int tamanho(pLDDE p)
{ int tam=0;
  pNoLDDE aux;
  aux=p->lista;
  if(aux==NULL)
    tam=0;
  else
  { while(aux!=NULL)
    { aux=aux->prox;
		tam++;
    }
  }
  return tam;
}

/*************** PURGA ***************/
void reinicia(pLDDE p)
{	pNoLDDE aux=NULL;	
	if(p->lista != NULL)
	{	aux=p->lista->prox;
		while(aux != NULL)
		{
	         	free(p->lista->dados);
		 	free(p->lista);
			p->lista=aux;
			aux=aux->prox;
		}
	   	free(p->lista->dados);
	     	free(p->lista);
      		p->lista = NULL;
	}
}

/*************** DESTROI ***************/
void destroi(ppLDDE pp)
{
	reinicia(*pp);
	free(*pp);
   (*pp)=NULL;
}
/************** EDITA *****************/
int editaNaPosLog(pLDDE p, void *reg, unsigned int posLog)
{ int cont, ret = FRACASSO;
  pNoLDDE pos;
  if(p->lista != NULL && posLog > 0)
  { cont = 1;
    pos = p->lista;
    while(cont < posLog && pos->prox != NULL ){
      pos = pos->prox;
      cont++;
    }
    if(cont == posLog){
      memcpy(pos->dados,reg,p->tamInfo);
      ret = SUCESSO;
    }
  }
  return ret;
}