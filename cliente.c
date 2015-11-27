//para compilar: gcc -Wall -o main cliente.c LDSE.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "LDSE.h"

void mostra_struct(void *info);

void listaTexto();

int main()
{
    int opcao;

    do
    {
        printf("> EDA\n");
        printf("1. Lista com frases do arquivo.\n"
			   "2. \n"
               "0. Sair.\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            listaTexto();
            break;
        default:
            break;
        }
    } while(opcao != 0);

    return 0;
}

void listaTexto()
{
    char buffer[2000], temp[99];
    int  vertAtual, offset;    
	int nVertices = 0;
    int i;
    int x=0,y=0;

    pLDSE pListaTexto;

    cria(&pListaTexto, sizeof(ppLDSE));


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
            pLDSE pL;
            cria(&pL, sizeof(Palavra));
            
			//fscanf(arquivo, "%s ", &vertAtual); // Ler o vertice a ser analisado. Numero antes do ":" no arquivo
            fgets(buffer, sizeof(buffer), arquivo); // Le as palavras na linha e guarda na string
            //sscanf(buffer, "%s", &temp);
            char *pBuffer = buffer; // Ponteiro para o buffer, para poder mover o ponteiro na hora de ler as palavras
            // printf("hue%s\n", pbuffer);
            while (sscanf(pBuffer, "%s%n", &temp, &offset) == 1){ // Le palavra por palavra ate chegar ao final da linha
                printf("%s %d\n", temp, offset);
                // getchar();getchar();
                c.x=x;
                c.y=y;
                pBuffer += offset; // Aponta o ponteiro para o proximo numero
                //c.palavra=temp;
                strcpy(c.palavra,temp);
                // printf("%s\n", c.palavra);
                insereNoFim(pL, &c);
                x+= offset;
            }
            insereNoFim(pListaTexto, &pL);//insere na lista "principal" a sub-lista, que são os vertices "filhos"
        }
    }
    for (i = 0; i < y; i++)
    {
        pLDSE pL=NULL;
        buscaNaPosLog(pListaTexto, &pL, i+1);
        mostra_lista(pL, mostra_struct);
        printf("-\n");
    }
}
void mostra_struct(void *palavra)
{
    Palavra *n = (Palavra*) palavra;
    printf("%d,%d -> %s ", n->y,n->x,n->palavra);
}
