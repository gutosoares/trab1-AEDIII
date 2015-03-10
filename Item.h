/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Este arquivo apresenta a definição de um item genérico, para ser usado com um tipo dicionário.
O dicionário não sabe o tipo do item. A única coisa que se assume é que cada item possui uma chave. 
O dicionário não sabe o tipo da chave. O dicionário só acessa itens e chaves por meio das funções definidas aqui.
*/

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Atenção
As funções abaixo foram implementadas usando macros, mas poderiam ser funções normais
*/
/*
Retorna a chave do item
*/
#define Get_Chave(A) (A->c)

/*
Retorna o contador do item
*/
#define Get_Contador(A) (A->contador)

/*
Retorna verdadeiro se c1 < c2, falso caso contrário
*/
#define Menor(c1, c2) (strcmp(c1,c2) < 0 ? 1 : 0)

/*
Retorna verdadeiro se c1 for igual a c2, falso caso contrário
*/
#define Igual(c1, c2) (strcmp(c1,c2) == 0 ? 1 : 0)

/*
Retorna um item vazio
*/
#define Null_Item() (NULL)

/*
Escreve um item
*/
#define Escreve(A) printf("%s - %d ", A->c, A->contador)

/*
Incrementa contador do item
*/
#define Incrementa_contador(A) A->contador++

/*
Tipo chave
*/
typedef char* Chave;

/*
Tipo Registro
*/
typedef struct
{
	Chave c;
	int contador;
	/*Outros campos do registros seriam inseridos aqui*/
} Registro;

/*
Tipo item
*/
typedef Registro* Item;

void Imprime(Item i);



#endif
