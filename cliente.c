//para compilar: gcc -Wall -o main main.c LDSE.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "LDSE.h"

void mostra_inteiro(void *info);

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
    char buffer[2000], temp[200];
    int  vertAtual, offset;    
	int nVertices = 0;
    int i;

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
            Info c;
			c.i++;
            pLDSE pL;
            cria(&pL, sizeof(info));
            
			//fscanf(arquivo, "%s ", &vertAtual); // Ler o vertice a ser analisado. Numero antes do ":" no arquivo
            fgets(buffer, sizeof(buffer), arquivo); // Le as palavras na linha e guarda na string
            //sscanf(buffer, "%s", &temp);

            char *pBuffer = buffer; // Ponteiro para o buffer, para poder mover o ponteiro na hora de ler as palavras
            while (sscanf(pBuffer, "%s%n", &temp, &offset)){ // Le palavra por palavra ate chegar ao final da linha
				c.j+=sizeof(temp)/sizeof(char) + offset;
                pBuffer += offset; // Aponta o ponteiro para o proximo numero
                insereNoFim(pL, &temp);
            }
            insereNoFim(pListaTexto, &pL);//insere na lista "principal" a sub-lista, que são os vertices "filhos"
        }
    }
    for (i = 0; i < nVertices-1; i++)
    {
        pLDSE pL=NULL;
        buscaNaPosLog(pListaTexto, &pL, i+1);
        printf("%d: ", i);
        mostra_lista(pL, mostra_inteiro);
        printf("-\n");
    }
}
void mostra_inteiro(void *info)
{
    int *n = (int*) info;
    printf("%d -> ", *n);
}
