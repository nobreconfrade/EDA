#include "LDSE_priv.h"

/*************** CRIA ***************/
int cria(ppLDSE pp, int tamInfo)
{   int ret = FRACASSO;
	if(((*pp)=(pLDSE)malloc(sizeof(LDSE)))==NULL)
		ret = FRACASSO;
	else
	{	(*pp)->lista=NULL;
        (*pp)->tamInfo=tamInfo;
        ret = SUCESSO;
	}
    return ret;
}

/*************** INSERE NO INICIO ***************/
int insereNoInicio(pLDSE p, void *novo)
{  pNoLDSE temp;
   int ret = FRACASSO;
   if((temp=(NoLDSE *)malloc(sizeof(NoLDSE)))!=NULL)
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
int insereNoFim(pLDSE p, void *novo)
{ 	pNoLDSE temp, aux;
	int ret = FRACASSO;
	if((temp=(pNoLDSE)malloc(sizeof(NoLDSE)))!= NULL)
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
int insereNaPosLog (pLDSE p, void *novo, unsigned int posLog)
{ pNoLDSE temp, pre,pos;
  unsigned int cont=0, ret=FRACASSO;
  if( p->lista != NULL && posLog > 0)
  { cont = 1;
    temp = (pNoLDSE) malloc(sizeof(NoLDSE));
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
int removeDoInicio(pLDSE p, void *reg)
{  	int ret = FRACASSO;
	pNoLDSE aux=NULL;
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
int removeDoFim(pLDSE p, void *reg)
{
	pNoLDSE aux, pre;
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
int removeDaPosLog(pLDSE p, void *reg, unsigned int posLog)
{  pNoLDSE pos=NULL,pre=NULL;
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
int buscaNoInicio(pLDSE p, void *reg)
{  int ret = FRACASSO;
   if(p->lista != NULL)
	{ memcpy(reg,p->lista->dados,p->tamInfo);
      ret = SUCESSO;
	}
   return ret;
}


/*************** BUSCA NO FINAL ***************/
int buscaNoFim(pLDSE p, void *reg)
{	pNoLDSE aux;
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
int buscaNaPosLog(pLDSE p, void *reg, unsigned int posLog)
{	int cont, ret = FRACASSO;
	pNoLDSE pos;
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
int tamanho(pLDSE p)
{ int tam=0;
  pNoLDSE aux;
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
void reinicia(pLDSE p)
{	pNoLDSE aux=NULL;	
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
void destroi(ppLDSE pp)
{
	reinicia(*pp);
	free(*pp);
   (*pp)=NULL;
}

void mostra_lista(pLDSE p, void (*mostra_info)(void *))
{
    pNoLDSE aux = p->lista;
    if (aux == NULL)
        return;

    while(aux != NULL)
    {
        mostra_info(aux->dados);
        aux = aux->prox;
    }
}

