contapalavrasABB: Main.o Dicionario_Arvore_Binaria.o Item.o
	gcc Main.o Dicionario_Arvore_Binaria.o Item.o -o contapalavrasABB -lm

contapalavrasDSW: Main.o Dicionario_ABB_DSW.o Item.o
	gcc Main.o Dicionario_ABB_DSW.o Item.o -o contapalavrasDSW -lm

contapalavrasAVL: Main.o Dicionario_ABB_AVL.o Item.o
	gcc Main.o Dicionario_ABB_AVL.o Item.o -o contapalavrasAVL -lm
	
contapalavrasEA1: Main.o Dicionario_EA1.o Item.o
	gcc Main.o Dicionario_EA1.o Item.o -o contapalavrasEA1 -lm

contapalavrasEA2: Main.o Dicionario_EA2.o Item.o
	gcc Main.o Dicionario_EA2.o Item.o -o contapalavrasEA2 -lm

contapalavrasEA3: Main.o Dicionario_EA3.o Item.o
	gcc Main.o Dicionario_EA3.o Item.o -o contapalavrasEA3 -lm
	
contapalavrasEA4: Main.o Dicionario_EA4.o Item.o
	gcc Main.o Dicionario_EA4.o Item.o -o contapalavrasEA4 -lm
	
Main.o: Main.c Item.h Dicionario.h
	gcc -c Main.c

Dicionario_Arvore_Binaria.o: Dicionario_Arvore_Binaria.c Item.h Dicionario.h
	gcc -c Dicionario_Arvore_Binaria.c

Dicionario_ABB_DSW.o: Dicionario_ABB_DSW.c Item.h Dicionario.h
	gcc -c Dicionario_ABB_DSW.c

Dicionario_ABB_AVL.o: Dicionario_ABB_AVL.c Item.h Dicionario.h
	gcc -c Dicionario_ABB_AVL.c

Dicionario_EA1.o: Dicionario_EA1.c Item.h Dicionario.h
	gcc -c Dicionario_EA1.c

Dicionario_EA2.o: Dicionario_EA2.c Item.h Dicionario.h
	gcc -c Dicionario_EA2.c
	
Dicionario_EA3.o: Dicionario_EA3.c Item.h Dicionario.h
	gcc -c Dicionario_EA3.c	

Dicionario_EA4.o: Dicionario_EA4.c Item.h Dicionario.h
	gcc -c Dicionario_EA4.c	

Item.o: Item.c Item.h
	gcc -c Item.c
