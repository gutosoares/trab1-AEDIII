/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Implementação para o tipo dicionário usando árvore binária de busca. Assume-se que o cliente fornece um tipo Item por meio da interface Item.h.
*/

#include "Dicionario.h"
#include <math.h>

/*
Estrutura para nós em uma ABB
*/
struct No 
{
	Item I;
	struct No *esq, *dir;
	int n;//Número de nós na sub-árvore
};

/*
Estrutura para ABBs
*/
struct dicionario
{
	struct No* raiz;
};


//Declarações de funções internas
void DIC_Rotaciona_Direita(struct No **R);
void DIC_Rotaciona_Esquerda(struct No **R);
void DIC_Destroi_Interno(struct No* r);
Item DIC_Busca_Rec(struct No* r, Chave c);
struct No* Novo(Item I, struct No *esq, struct No *dir);
void DIC_Insere_Interno(struct No** R, Item I);
void DIC_DSW_1(struct No **R);
void DIC_DSW_2(struct No **R);
void DIC_DSW(struct No **R);
void DIC_Remove_Interno(struct No **R, Chave c, Item *I);
void DIC_Remove_Maior(struct No **R, Item *I);
void DIC_Processa_In_Ordem(struct No *r, void (*P)(Item));
int DIC_n(struct No *r);

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
	n->n = 0;
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
	DIC_Insere_Interno( &(D->raiz), I );
	DIC_DSW(&(D->raiz));
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
		((*R)->n)++;
		return;
	}

	//Inserção à esquerda
	if( Menor( Get_Chave( I ), Get_Chave( r->I ) ) )
	{
		DIC_Insere_Interno( &(r->esq), I );
		(r->n)++;
		return;
	}

	//Inserção à direita
	if( Menor( Get_Chave( r->I ), Get_Chave( I ) ) )
	{
		DIC_Insere_Interno( &(r->dir), I );
		(r->n)++;
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
	DIC_DSW(&(D->raiz));
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
		r->n = 1 + DIC_n(r->dir) + DIC_n(r->esq);
		return;
	}
	
	/*Remoção à direita*/
	if( Menor( Get_Chave( r->I ), c ) )
	{
		DIC_Remove_Interno( &(r->dir), c, I );
		r->n = 1 + DIC_n(r->dir) + DIC_n(r->esq);
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
	if(r->dir)
	{
		DIC_Remove_Maior( &(r->dir), I ); 
		r->n = 1 + DIC_n(r->dir) + DIC_n(r->esq);
		return; 
	}

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
		printf(" , %d)\n", r->n);
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

void DIC_DSW(struct No **R)
{
	DIC_DSW_1(R);
	DIC_DSW_2(R);
}

/*Primeira fase do balanceamento DSW*/
void DIC_DSW_1(struct No **R)
{
	if(!(*R)) return;

	while( (*R)->esq ) DIC_Rotaciona_Direita(R);
	DIC_DSW_1( &((*R)->dir) );
}

void DIC_DSW_2(struct No **R)
{
	if(!(*R)) return;
	int log2 = log((*R)->n+1)/log(2.0);
	int m = pow(2, log2)-1;
	int i;

	struct No** S = R;
	for(i = 0; i < (*R)->n-m; i++)
	{
		DIC_Rotaciona_Esquerda(S);
		S = &((*S)->dir);
	}

	while(m>1)
	{
		m/=2;

		S = R;
		for(i = 0; i < m; i++)
		{
			DIC_Rotaciona_Esquerda(S);
			S = &((*S)->dir);
		}
	}
}

void DIC_Rotaciona_Direita(struct No **R)
{
	struct No *r = *R;
	if(!r) return;
	if(!(r->esq)) return;

	struct No* e = r->esq;
	struct No* ed = e->dir;
	int nrd = DIC_n(r->dir), 
		ned = DIC_n(e->dir), 
		nee = DIC_n(e->esq);
	e->dir = r;
	e->n = nee+ned+nrd+2;
	r->esq = ed;
	r->n = ned+nrd+1;
	*R = e;
}

void DIC_Rotaciona_Esquerda(struct No **R)
{
	struct No *r = *R;
	if(!r) return;
	if(!(r->dir)) return;

	struct No* d = r->dir;
	struct No* de = d->esq;
	int nre = DIC_n(r->esq), 
		ndd = DIC_n(d->dir), 
		nde = DIC_n(d->esq);

	d->esq = r;
	d->n = ndd+nde+nre+2;
	r->dir = de; 
	r->n = nre+nde+1;
	*R = d;
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

int DIC_n(struct No* r)
{
	return r ? r->n : 0;
}
