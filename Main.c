#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Item.h"
#include "Dicionario.h"

//int contador;

/* Cria o registro a ser enviado ao no */
Registro* novoRegistro(char * palavra){

	Registro* reg = malloc(sizeof(Registro));/* Aloca o registro */
	char *p = malloc(sizeof(palavra)); /* Aloca a chave */
	strcpy(p, palavra);
	reg->c = p;
	return reg;
}

/*void Funcao(Item I)
{
	contador++;
}*/


int main(int c, char* argv[]) {
    char word[50], *pointer = NULL;
	int eof;
	
	Dicionario D = DIC_Inicializa();
	
	eof = scanf("%s", word);
	
    while (eof != -1) {
        
        pointer = strtok(word, "0123456789!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");

        while (pointer != NULL) {
            strcpy(word, pointer);
            int tamanho;
            tamanho = strlen(word);
            //strlwr(word);
            if (tamanho < 20 && tamanho > 2) {
            //printf("%s\n", word);
				Registro *r = novoRegistro(word);
            //printf("alocou palavra\n");
				DIC_Insere(D, r);
            //printf("inseriu palavra\n");
			}
            pointer = strtok(NULL, "0123456789!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");
        }
        eof = scanf("%s", word);
    }
    
    DIC_Processa(D, Imprime);
    //contador = 0;
    //DIC_Processa(D, Funcao);
	DIC_Processa(D, DIC_Testar_No);
	DIC_Imprime_Top_10(D);
	
	//printf("Contador: %d\n", contador);

    return 0;
}
