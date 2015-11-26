//para compilar: gcc -Wall -o main cliente.c LDSE.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "LDSE.h"

void mostra_struct(void *info);

void chamaBuscaPalavra();

void listaTexto(pLDSE pListaVertical, pLDSE pListaHorizontal);

void carregaLista(pLDSE pListaVertical, pLDSE pListaHorizontal);

int main(){
    int opcao;
    pLDSE pListaVertical;
    pLDSE pListaHorizontal;
    
    do{
        carregaLista(pListaVertical,pListaVertical);
        printf("> EDA\n");
        printf("1. Lista com frases do arquivo.\n"
			   "2. Busca uma palavra no arquivo.\n"
               "0. Sair.\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            listaTexto(pListaVertical,pListaHorizontal);
            break;
        case 2:
            chamaBuscaPalavra();
        default:
            break;
        }
    }while(opcao != 0);

    return 0;
}

void listaTexto(pLDSE pListaVertical, pLDSE pListaHorizontal)
{
    while(pListaVertical != NULL){
        pLDSE pListaHorizontal=NULL;
        buscaNaPosLog(pListaVertical, &pListaHorizontal, i+1);
        mostra_lista(pListaHorizontal, mostra_struct);
        printf("\n");
    }
}

void mostra_struct(void *palavra)
{
    Palavra *n = (Palavra*) palavra;
    printf(" %d,%d -> %s |", n->y,n->x,n->palavra);
}

void chamaBuscaPalavra(){
    char temp[99];
    printf("Escolha uma palavra\n");
    scanf("%s",temp);
    buscaPalavra();
}

void carregaLista(pLDSE *pListaVertical, pLDSE *pListaHorizontal){
    char buffer[2000], temp[99];
    int offset;    
    int x=0,y=0;

    cria(&pListaVertical, sizeof(ppLDSE));


    FILE *arquivo = fopen("arquivo.txt", "r"); // Abre o arquivo de texto
    if(arquivo == NULL) // Se falhou abrir o arquivo
    {
        printf("Erro ao abrir arquivo!");
    }
    else
    {
        
        while( !feof(arquivo)) // Enquanto nao chegar no final do texto
        {
            Palavra c;
            y++;
            x=0;
            cria(&pListaHorizontal, sizeof(Palavra));
            
            fgets(buffer, sizeof(buffer), arquivo); // Le as palavras na linha e guarda na string
            char *pBuffer = buffer; // Ponteiro para o buffer, para poder mover o ponteiro na hora de ler as palavras
            while (sscanf(pBuffer,"%s%n", &temp, &offset) == 1){ // Le palavra por palavra ate chegar ao final da linha
                // printf("%s %d\n", temp, offset)
                c.x=x;
                c.y=y;
                pBuffer += offset; // Aponta o ponteiro para a proxima palavra
                if(x==0)
                    x+= offset+1;
                else
                    x+= offset;
                strcpy(c.palavra,temp);
                insereNoFim(pListaHorizontal, &c);
                
            }
            insereNoFim(pListaVertical, &pListaHorizontal);//indexa pListaHorizontal na lista vertical 
        }
    }
}