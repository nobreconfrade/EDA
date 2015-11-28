//para compilar: gcc -Wall -o main cliente.c LDSE.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "LDSE.h"

void buscaPalavra(pLDSE pListaVertical,char *temp);

void listaTexto(pLDSE pListaVertical);

void carregaLista(pLDSE pListaVertical);

void contaTexto(pLDSE pListaVertical);

int main(){
    system("clear");
    int opcao;
    char temp[99];
    pLDSE pListaVertical = NULL;
    cria(&pListaVertical, sizeof(ppLDSE)); //cria lista vertical, a horizontal sera criada dentro do "carregaLista"
    carregaLista(pListaVertical); //carrega as palavras do arquivo nas listas
    do{
        printf("> EDA - Trabalho final LISTA DE LISTAS\n");
        printf("1. Lista com palavras do arquivo.\n"
                "2. Busca uma palavra no arquivo.\n"
                "3. Conta quantas palavras o arquivo possui.\n"
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
                break;
            case 3:
                contaTexto(pListaVertical);
                break;
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
    printf("---------------------------------------------------\n");
    while(buscaNaPosLog(pListaVertical,&pListaHorizontal,i++) != FRACASSO){ //vai indexar o valor do nó de "pListaVertical" (que é outra lista, "pListaHorizontal") 
        // printf("Hello\n");
        j=1;	
        while(buscaNaPosLog(pListaHorizontal,&c,j++) != FRACASSO){ //vai procurar pela "pListaHorizontal" até encontrar "NULL" 
            printf("%d %d -> %s |",c.y,c.x,c.palavra);
        }
        printf("\n");
    }
    printf("---------------------------------------------------\n");
}

void buscaPalavra(pLDSE pListaVertical,char *temp){
    int i,j;
    Palavra c;    
    pLDSE pListaHorizontal;
    i=1;
    printf("\n");
    while(buscaNaPosLog(pListaVertical,&pListaHorizontal,i++) != FRACASSO){
        j=1;	
        while(buscaNaPosLog(pListaHorizontal,&c,j++) != FRACASSO){
            if(strcmp(c.palavra,temp)==0) // se o retorno de "strcmp" for igual a 0 indica sucesso e retorna a palavra
                printf(" %d %d -> %s | \n",c.y,c.x,c.palavra);
            
        }
        
    }
    printf("\n");
}

void contaTexto(pLDSE pListaVertical){
    int i,tam=0;    
    pLDSE pListaHorizontal;
    i=1;
    while(buscaNaPosLog(pListaVertical,&pListaHorizontal,i++) != FRACASSO){
        tam+=tamanho(pListaHorizontal); // utiliza funcao "tamanho" para contar palavras
    }
    printf("\n");
    printf("Seu arquivo contem %d palavras. \n", tam);
    printf("\n");

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

            cria(&pListaHorizontal, sizeof(Palavra)); //cria segunda lista, está vai possuir struct com as palavras e posicoes

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
