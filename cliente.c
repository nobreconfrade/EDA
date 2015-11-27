//para compilar: gcc -Wall -o main cliente.c LDSE.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "LDSE.h"

void mostra_struct(void *info);

void buscaPalavra(pLDSE pListaVertical,char *temp);

void listaTexto(pLDSE pListaVertical);

void carregaLista(pLDSE pListaVertical);

int main(){
    int opcao;
    char temp[99];
    pLDSE pListaVertical = NULL;
    cria(&pListaVertical, sizeof(ppLDSE));
    carregaLista(pListaVertical);
    do{
        printf("> EDA\n");
        printf("1. Lista com frases do arquivo.\n"
                "2. Busca uma palavra no arquivo.\n"
                "0. Sair.\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
            case 1:
                listaTexto(pListaVertical);
                break;
            case 2:
                printf("Escolha uma palavra\n");
                scanf("%s",temp);
                buscaPalavra(pListaVertical,temp);
            default:
                break;
        }
    }while(opcao != 0);

    return 0;
}

void listaTexto(pLDSE pListaVertical)
{
    int i,j;
    Palavra c;    
    pLDSE pListaHorizontal;
    //printf("%p\n",pListaVertical);
    i=1;
    while(buscaNaPosLog(pListaVertical,&pListaHorizontal,i++) != FRACASSO){
        // printf("Hello\n");
        j=1;	
        while(buscaNaPosLog(pListaHorizontal,&c,j++) != FRACASSO){
            printf("%d %d -> %s |",c.y,c.x,c.palavra);
        }
        printf("\n");
    }
}

void mostra_struct(void *palavra)
{
    Palavra *n = (Palavra*) palavra;
    printf(" %d,%d -> %s |", n->y,n->x,n->palavra);
}

void buscaPalavra(pLDSE pListaVertical,char *temp){
    int i,j;
    Palavra c;    
    pLDSE pListaHorizontal;
    i=1;
    while(buscaNaPosLog(pListaVertical,&pListaHorizontal,i++) != FRACASSO){
        j=1;	
        while(buscaNaPosLog(pListaHorizontal,&c,j++) != FRACASSO){
            if(strcmp(c.palavra,temp)==0)
                printf(" %d %d -> %s |",c.y,c.x,c.palavra);
        }
        printf("\n");
    }
}

void carregaLista(pLDSE pListaVertical){
    char buffer[2000], aux[99];
    int offset;    
    int x=0,y=0;

    FILE *arquivo = fopen("arquivo.txt", "r"); // Abre o arquivo de texto
    if(arquivo == NULL) // Se falhou abrir o arquivo
        printf("Erro ao abrir arquivo!");
    else {
        while(!feof(arquivo)) // Enquanto nao chegar no final do texto
        {
            Palavra c;
            pLDSE pListaHorizontal;
            y++;
            x=0;
            cria(&pListaHorizontal, sizeof(Palavra));

            fgets(buffer, sizeof(buffer), arquivo); // Le as palavras na linha e guarda na string
            char *pBuffer = buffer; // Ponteiro para o buffer, para poder mover o ponteiro na hora de ler as palavras
            while (sscanf(pBuffer,"%s%n", aux, &offset) == 1){ // Le palavra por palavra ate chegar ao final da linha
                //printf("%s %d\n", aux, offset);
                c.x=x;
                c.y=y;
                pBuffer += offset; // Aponta o ponteiro para a proxima palavra
                if(x==0)
                    x+= offset+1;
                else
                    x+= offset;
                strcpy(c.palavra,aux);
                insereNoFim(pListaHorizontal, &c);
                // printf("%s\n",c.palavra);

            }
            insereNoFim(pListaVertical, &pListaHorizontal);//indexa pListaHorizontal na lista vertical 
        }
    }
}
