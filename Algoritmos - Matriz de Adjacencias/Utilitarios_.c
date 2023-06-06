/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de funcoes utilitarias,
    envolvendo grafos, que auxliam na construcao de algoritmos
    usando uma matriz de adjacencias.
*/

#include "Grafos_.h"



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por verificar se dois vertices sao adjacentes.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ V ].
    + Vertice de chegada [ W ].

    @ Saida:
    - [ 0 ] - Nao sao adjacentes.
    - [ 1 ] - Sao adjacentes.
*/
int Verificar_Adjacencia_(Grafo *G, int V, int W){

    if(G->Adj[V][W] != SEM_ARESTA)  return SIM; // V e W sao adjacentes.
    else                            return NAO; // V e W nao sao adjacentes.
}


/*
    Metodo responsavel por calcular o grau de um vertice.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ V ].

    @ Saida:
    - Numero de arestas que partem de V [ GRAU ].
*/
int Calcular_Grau_(Grafo *G, int V){

    int Grau = 0;

    // Loop: Contar os vertices adjacentes a V.
    for(int W = 0; W < G->Qnt_V; W++)
        if(Verificar_Adjacencia_(G, V, W))
            Grau++;

    return Grau;
}


/*
    Metodo responsavel por imprimir todos os
    vertices que sao adjacentes a um vertice V.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ V ].

    @ Saida:
    - ( void )
*/
void Imprimir_Adjacentes_(Grafo *G, int V){

    // Loop: Imprimir os vertices adjacentes a V.
    printf("|----|");
    for(int W = 0; W < G->Qnt_V; W++)
		if(Verificar_Adjacencia_(G, V, W))
            printf(" %02d", W+1);
    printf("\n");
}



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por gerar um vetor de
    arestas com todas as arestas de um grafo.

    @ Entrada:
    + Grafo [ G ].

    @ Saida:
    - Vetor de arestas [ ARESTAS ].
*/
Aresta *Criar_Vetor_Arestas_(Grafo *G){

    int V, W;   // Indice dos vertices.
    int E = 0;  // Indice de arestas.
    Aresta *Arestas = NULL;

	if(G && (G->Qnt_E != 0)){

	    Arestas = (Aresta*) malloc(G->Qnt_E * sizeof(Aresta));  // Vetor de arestas.

	    if(Arestas){

		    /* Loop para percorrer o conjunto
                de vertices de um grafo.    */
		    for(V = 0; V < G->Qnt_V; V++){

			    /*  Loop para percorrer o conjunto
                    de vertices adjacentes a V. */
			    for(W = 0; W < G->Qnt_V; W++){

                    // (V >= W): Grafos nao direcionados contam arestas duas vezes.
                    if((V >= W) && Verificar_Adjacencia_(G, V, W)){
                        
                        // Insere a aresta no vetor de arestas.
                        Arestas[E].V    = V;
                        Arestas[E].W    = W;
                        Arestas[E].Peso = G->Adj[V][W];
                        E++;    // Atualiza o indice de arestas.
                    }
			    }
		    }
	    }
        else SEM_MEMORIA
    }
    else SEM_GRAFO

	return Arestas;
}


/*
    Metodo responsavel por ordenar um vetor
    de arestas por ordem crescente de peso.

    @ Entrada:
    + Vetor de arestas [ ARESTAS ].
    + Tamanho do vetor [ TAM ].

    @ Saida:
    - ( void ).
*/
void Ordenar_Arestas___Insertion_Sort_(Aresta *Arestas, int Tam){

    int i, j;
    Aresta *Aux = (Aresta*) malloc(sizeof(Aresta));

    // Loop: Percorrer vetor.
    for(i = 1; i < Tam; i++){

        Aux->V    = Arestas[i].V;
        Aux->W    = Arestas[i].W;
        Aux->Peso = Arestas[i].Peso;
        j = i-1;

        // Loop: Ordenar vetor de arestas.
        while((j >= 0) && (Aux->Peso < Arestas[j].Peso)){
            
            Arestas[j+1].V    = Arestas[j].V;
            Arestas[j+1].W    = Arestas[j].W;
            Arestas[j+1].Peso = Arestas[j].Peso;
            j--;
        }

        Arestas[j+1].V    = Aux->V;
        Arestas[j+1].W    = Aux->W;
        Arestas[j+1].Peso = Aux->Peso;
    }

    free(Aux);
}



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por imprimir o caminho entre
    dois vertice, partido-se de um vertice raiz ate
    outro, usando um vetor de predecessores.

    @ Entrada:
    + Vetor com os predecessores de cada vertice [ PREDECESSOR ].
    + Vertice de partida [ RAIZ ].
    + Vertice de chegada [ V ].

    @ Saida:
    - ( void )
*/
void Imprimir_Caminho_(int *Predecessor, int Raiz, int V){

    if(Raiz == V)
        printf("|----| %02d ", Raiz+1);  // Chegou ate a raiz.
    else{

        // Verifica se nao existe caminho.
        if(Predecessor[V] < 0)
            printf("|----| Nao existe caminho de '%d' ate '%d'.\n", Raiz+1, V+1);
        else{

            Imprimir_Caminho_(Predecessor, Raiz, Predecessor[V]);   // Realiza o caminho de V ate a raiz.
            printf("%02d ", V+1);                                   // Imprime o vertice V.
        }
    }
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/