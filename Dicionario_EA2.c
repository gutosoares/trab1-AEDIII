/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Implementação para o tipo dicionário usando árvore binária de busca. Assume-se que o cliente fornece um tipo Item por meio da interface Item.h.
*/

#include "Dicionario.h"

/*
Estrutura para nós em uma ABB
*/
struct No 
{
	Item I;
	struct No *esq, *dir;
};

/*
Estrutura para ABBs
*/
struct dicionario
{
	struct No* raiz;
};

Item Top_10[10]; /* Arranjo de 10 itens que mais aparecem */

//Declarações de funções internas
void DIC_Destroi_Interno(struct No* r);
Item DIC_Busca_Rec(struct No* r, Chave c);
struct No* Novo(Item I, struct No *esq, struct No *dir);
void DIC_Insere_Interno(struct No** R, Item I);
void DIC_Remove_Interno(struct No **R, Chave c, Item *I);
void DIC_Remove_Maior(struct No **R, Item *I);
void DIC_Processa_In_Ordem(struct No *r, void (*P)(Item));
void Insere_ou_Processa(struct No** R, Item I);
void DIC_Rotaciona_Direita(struct No **R);
void DIC_Rotaciona_Esquerda(struct No **R);
void Insere_ou_Processa_EA2(struct No** R, Item I);
void DIC_Imprime_Top_10();
void DIC_Inicia_Top_10();
/*
Inicializa a ABB (Dicionario)
*/
Dicionario DIC_Inicializa()
{
	Dicionario D = malloc(sizeof(struct dicionario));
	D->raiz = NULL;
}

/*
Cria um novo nó
*/
struct No* Novo(Item I, struct No *esq, struct No *dir)
{
	struct No* n = malloc(sizeof(struct No));
	n->I = I;
	n->esq = esq;
	n->dir = dir;
	return n;
}

/*
Desaloca o dicionario
*/
void DIC_Destroi(Dicionario D)
{
	DIC_Destroi_Interno(D->raiz);
}

/*
Procedimento de desalocação recursivo.
*/
void DIC_Destroi_Interno(struct No* r)
{
	if(!r) return;

	DIC_Destroi_Interno(r->esq);
	DIC_Destroi_Interno(r->dir);
	free(r);
}

/*
Retorna o item de chave c no dicionaro D.
*/
Item DIC_Busca(Dicionario D, Chave c)
{
	if(!D)
	{
		printf("Dicionario nao inicializado\n");
		return Null_Item();
	}

	DIC_Busca_Rec(D->raiz, c);
}

/*
Função interna para realização de busca.
Retorna o item de chave c na árvore de raiz r.
*/
Item DIC_Busca_Rec(struct No* r, Chave c)
{
	if(!r) return Null_Item();

	Chave d = Get_Chave(r->I);

	if( Menor( d , c ) )
		return DIC_Busca_Rec(r->dir, c);
	else if( Menor(c, d))
		return DIC_Busca_Rec(r->esq, c);
	else
		return r->I;
}

/*
Insere o item I no dicionario D
*/
void DIC_Insere(Dicionario D, Item I)
{
	Insere_ou_Processa_EA2( &(D->raiz), I );

}

/*
Procedimento interno de inserção.
*/
void DIC_Insere_Interno(struct No** R, Item I)
{
	struct No *r = *R;

	//Encontrou o ponto de inserção
	if(r == NULL)
	{
		*R = Novo(I, NULL, NULL);
		return;
	}

	//Inserção à esquerda
	if( Menor( Get_Chave( I ), Get_Chave( r->I ) ) )
	{
		DIC_Insere_Interno( &(r->esq), I );
		return;
	}

	//Inserção à direita
	if( Menor( Get_Chave( r->I ), Get_Chave( I ) ) )
	{
		DIC_Insere_Interno( &(r->dir), I );
		return;
	}

	//printf("Chave ja inserida \n");
}

/*
Remove o item com chave c do dicionario D. Retorna o item removido.
*/
Item DIC_Remove(Dicionario D, Chave c)
{
	Item I;
	DIC_Remove_Interno( &(D->raiz), c, &I);
	return I;
}

/*
Remove o item de chave c da sub-árvore *R, armazena o item removido em I.
*/
void DIC_Remove_Interno(struct No **R, Chave c, Item *I)
{
	struct No *r = *R;

	/*Item não encontrado*/
	if(r == NULL)
	{ 
		*I = Null_Item(); 
		return;  
	}

	/*Remoção à esquerda*/
	if( Menor( c, Get_Chave( r->I ) ) )
	{
		DIC_Remove_Interno( &(r->esq), c, I );
		return;
	}
	
	/*Remoção à direita*/
	if( Menor( Get_Chave( r->I ), c ) )
	{
		DIC_Remove_Interno( &(r->dir), c, I );
		return;
	}

	/*Item encontrado*/
	*I = r->I;
	/*Nó sem filhos*/
	if(r->esq == NULL && r->dir == NULL)
	{
		free(r);
		*R = NULL;
		return;
	}
	/*Nó com apenas um filho, à direita*/
	if(r->esq == NULL)
	{
		free(r);
		*R = r->dir;
		return;
	}
	/*Nó com apenas um filho, à esquerda*/
	if(r->dir == NULL)
	{
		free(r);
		*R = r->esq;
		return;
	}

	DIC_Remove_Maior(&(r->esq), &(r->I));
}

/*
Remove o item de maior chave da sub-árvore *R, armazena o item em I
*/
void DIC_Remove_Maior(struct No **R, Item *I)
{
	struct No *r = *R;

	/*sub-árvore vazia*/
	if(!r){ *I = Null_Item(); return;}
	/*Se r tem filho à direita, o maior está naquela sub-árvore*/
	if(r->dir){ DIC_Remove_Maior( &(r->dir), I ); return; }

	/*Maior elemento encontrado*/
	/*Armazena o item*/
	*I = r->I;
	/*Desaloca r*/
	free(r);
	/*Altera o ponteiro que apontava para r para seu filho à esquerda*/
	*R = r->esq;
}

void DIC_Imprime_Interno2(struct No *r, int profundidade)
{
	int i,j;
	for(i = 0; i < 2; i++)
	{	
		for(j = 0; j < profundidade; j++)
		{
			printf("   |");
		}
		printf("\n");
	}
	for(j = 0; j < profundidade-1; j++)
	{
		printf("   |");
	}
	if(!r)
	{	

		printf("   +---x\n");
	}
	else
	{
		if(profundidade == 0)
			printf("+---( ");
		else
			printf("   +---( ");
		Escreve(r->I);
		printf(")\n");
		DIC_Imprime_Interno2(r->dir, profundidade+1);
		DIC_Imprime_Interno2(r->esq, profundidade+1);
	}

}
void DIC_Imprime_Interno(struct No *r)
{
	if(r == NULL) return;

	Escreve(r->I);
	DIC_Imprime_Interno(r->esq);
	DIC_Imprime_Interno(r->dir);
}

void DIC_Imprime(Dicionario D)
{
	DIC_Imprime_Interno2(D->raiz, 0);
	printf("\n********************\n");
}


void DIC_Processa(Dicionario D, void (*P)(Item))
{
	DIC_Processa_In_Ordem(D->raiz, P);
}

void DIC_Processa_In_Ordem(struct No *r, void (*P)(Item))
{
	if(!r) return;
	DIC_Processa_In_Ordem(r->esq, P);
	(*P)(r->I);
	DIC_Processa_In_Ordem(r->dir, P);
}

/*
Procedimento interno de inserção ou processamento.
*/
void Insere_ou_Processa(struct No** R, Item I)
{
	struct No *r = *R;

	//Encontrou o ponto de inserção
	if(r == NULL)
	{
		*R = Novo(I, NULL, NULL);
		return;
	}

	//Inserção à esquerda
	if( Menor( Get_Chave( I ), Get_Chave( r->I ) ) )
	{
		Insere_ou_Processa( &(r->esq), I );
		return;
	}

	//Inserção à direita
	if( Menor( Get_Chave( r->I ), Get_Chave( I ) ) )
	{
		Insere_ou_Processa( &(r->dir), I );
		return;
	}
	
	Incrementa_contador((*R)->I);
	//printf("Chave ja inserida \n");
}

void DIC_Rotaciona_Direita(struct No **R)
{
	struct No *r = *R;
	if(!r) return;
	if(!(r->esq)) return;

	struct No* e = r->esq;

	r->esq = e->dir;
	e->dir = r;
	*R = e;

}

void DIC_Rotaciona_Esquerda(struct No **R)
{
	struct No *r = *R;
	if(!r) return;
	if(!(r->dir)) return;

	struct No* d = r->dir;

	r->dir = d->esq;
	d->esq = r; 
	*R = d;

}

void Insere_ou_Processa_EA2(struct No** R, Item I)
{
	struct No *r = *R;

	//Encontrou o ponto de inserção
	if(r == NULL)
	{
		I->contador = 1;
		*R = Novo(I, NULL, NULL);
		return;
	}

	//Inserção à esquerda
	if( Menor( Get_Chave( I ), Get_Chave( r->I ) ) )
	{
		Insere_ou_Processa_EA2( &(r->esq), I );
		DIC_Rotaciona_Direita(R);
		return;
	}

	//Inserção à direita
	if( Menor( Get_Chave( r->I ), Get_Chave( I ) ) )
	{
		Insere_ou_Processa_EA2( &(r->dir), I );
		DIC_Rotaciona_Esquerda(R);
		return;
	}
	
	Incrementa_contador((*R)->I);
	//printf("Chave ja inserida \n");
}


void DIC_Imprime_Top_10()
{
	printf("\nAs 10 palavras que mais aparecem no texte são:\n");
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		if (Top_10 != NULL){
			printf("%s - %d\n", Get_Chave(Top_10[i]), Get_Contador(Top_10[i]));
		}
	}
}

void DIC_Insere_TOP_10(int indice, Item I)
{
	int j;
	for (j = 9; j > indice; j--)
	{
		Top_10[j] = Top_10[j - 1];
		
	}
	Top_10[indice] = I;	
} 

void DIC_Testar_No(Item I)
{
	int i = 0;
	while(Top_10[i] != NULL && i < 10){
		if (Get_Contador(I) <= Get_Contador(Top_10[i]))
		{
			i++;
		} else 
		{
			DIC_Insere_TOP_10(i, I);
			return;	
		}	
	}
	if (i < 10)	DIC_Insere_TOP_10(i, I);
}

void DIC_Inicia_Top_10()
{
	int i;
	for(i = 0; i < 10; i++)
	{
		Top_10[i] = NULL;
	}
}

