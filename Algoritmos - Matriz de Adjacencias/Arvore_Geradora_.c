/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de algoritmos avancados para
    encontrar a representacao de uma arvore geradora minima de um
    grafo usando matriz de adjacencias.
*/

#include "Grafos_.h"



/*<<===================================================================================>>*/
/*<<==============================>> ALGORITMO DE PRIM <<==============================>>*/
/*<<===================================================================================>>*/

/*
    Metodo auxiliar do algoritmo de PRIM responsavel por
    encontrar o vertice que possui a menor estimativa de
    distancia ate um vertice raiz.

    @ Entrada:
    + Vetor com a estimativa de distancia de cada vertice [ DISTANCIAS ].
    + Conjunto de vertices nao analisados [ ANALISADOS ].
    + Numero de vertices [ N ].

    @ Saida:
    - Vertice com a menor estimativa de distancia [ VERTICE ].
*/
int Encontrar_Menor_Estimativa_(int *Distancias, int *Analisados, int N){

    int Vertice;
    int Menor = INFINITO;

    // Loop: Encontrar menor distancia.
    for(int V = 0; V < N; V++){

        // Verifica a menor estimativa de distancia.
        if((Analisados[V] == NAO) && (Distancias[V] < Menor)){

            Vertice = V;
            Menor = Distancias[V];
        }
    }

    // Vertice com a menor estimativa.
    return Vertice;
}


/*
    @ Algoritmo de Prim:

    Metodo responsavel por explorar um grafo, usando
    uma matriz de adjacencias, e construir uma arvore
    geradora minima a partir de um vertice raiz.
    
    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ RAIZ ].

    @ Saida:
    - Vetor com os predecessores de cada vertice [ PREDECESSORES ].
*/
int *Arvore_Geradora_Minima___PRIM_(Grafo *G, int Raiz){
    
    int V, W;           // Indice dos vertices.
    int N = G->Qnt_V;   // Numero de vertices.

    int *Analisado   = (int*) calloc(N, sizeof(int));   // Conjunto de vertices analisados.
    int *Distancias  = (int*) calloc(N, sizeof(int));   // Vetor das estimativas de distancia ate a raiz.
    int *Predecessor = (int*) calloc(N, sizeof(int));   // Vetor dos predecessores de cada vertice.

    // Loop: Inicializar vetores.
    for(V = 0; V < N; V++){
        
        Distancias[V]  = INFINITO;  // Estimativa inicial.
        Predecessor[V] = -1;        // Predecessor inicial de cada vertice.
    }

    Distancias[Raiz] = 0;


    /*  Loop para percorrer o conjunto de
        vertices ainda nao analisados.  */
    for(V = 0; V < N; V++){

        Raiz = Encontrar_Menor_Estimativa_(Distancias, Analisado, N);   // Encontra o vertice com a menor estimativa de distancia ate a raiz.
        Analisado[Raiz] = SIM;                                          // Atualiza o vertice como analisado.

        /*  Loop para percorrer o conjunto
            de vertices adjacentes a raiz.  */
        for(W = 0; W < N; W++){

            // Compara a estimativa de distancia do vertice com o peso da aresta.
            if((Analisado[W] == NAO) && Verificar_Adjacencia_(G, Raiz, W) && (G->Adj[Raiz][W] < Distancias[W])){

                Distancias[W]  = G->Adj[Raiz][W];   // Atualiza a estimativa da distancia de W com o peso da aresta.
                Predecessor[W] = Raiz;              // Indica que a raiz eh o predecessor de W na arvore.
            }
        }
    }

    free(Analisado);
    free(Distancias);
    return Predecessor;
}



/*<<===================================================================================>>*/
/*<<============================>>  ALGORITMO DE KRUSKAL <<============================>>*/
/*<<===================================================================================>>*/

/*
    Metodo auxiliar do algoritmo de KRUSKAL responsavel por
    explorar os predecessores de um vertice ate encontrar
    o vertice que eh a raiz do conjunto.

    @ Entrada:
    + Vetor com os predecessores de cada vertice [ PREDECESSOR ].
    + Vertice de chegada [ V ].

    @ Saida:
    - Vertice de partida [ RAIZ ].
*/
int FindSet_Otimizado_(int *Predecessor, int V){

    int Pai, Raiz;

    // Loop: Encontrar a raiz do conjunto.
    Raiz = V;
    while(Predecessor[Raiz] >= 0)
        Raiz = Predecessor[Raiz];

    // Loop: Trocar predecessores.
    while(Predecessor[V] >= 0){
        
        Pai = Predecessor[V];
        Predecessor[V] = Raiz;  // Aponta os predecessores de V para a raiz.
        V = Pai;
    }

    return Raiz;
}


/*
    Metodo auxiliar do algoritmo de KRUSKAL responsavel
    por criar um conjunto unindo dois vertices por meio
    de seus predecessores.

    @ Entrada:
    + Vetor com os predecessores de cada vertice [ PREDECESSOR ].
    + Raiz do conjunto de V [ RAIZ_V ].
    + Raiz do conjunto de W [ RAIZ_W ].

    @ Saida:
    - ( void )
*/
void Union_(int **Predecessor, int Raiz_V, int Raiz_W){

    if(Raiz_V != Raiz_W){

        // Verifica a raiz com o menor numero de vertices no conjunto.
        if((*Predecessor)[Raiz_V] < (*Predecessor)[Raiz_W]){

            // Troca o valor das raizes.
            int Aux = Raiz_V;
            Raiz_V  = Raiz_W;
            Raiz_W  = Aux;
        }

        (*Predecessor)[Raiz_V] += (*Predecessor)[Raiz_W];   // Atualiza o numero de vertices no conjunto raiz de V.
        (*Predecessor)[Raiz_W] = Raiz_V;                    // Aponta o predecessor de W para a raiz de V.
    }
}


/*
    @ Algoritmo de Kruskal:
    
    Metodo responsavel por explorar as arestas de
    um grafo e construir uma arvore geradora minima
    usando conjuntos.

    @ Entrada:
    + Grafo [ G ].

    @ Saida:
    - Vetor com os predecessores de cada vertice [ PREDECESSOR ].
*/
int *Arvore_Geradora_Minima___KRUSKAL_(Grafo *G){

    int *Predecessor = (int*) malloc(G->Qnt_V * sizeof(int));
    Aresta *Arestas  = Criar_Vetor_Arestas_(G);
    Ordenar_Arestas___Insertion_Sort_(Arestas, G->Qnt_E);   // Ordena o vetor de arestas.

    // Loop: Inicializar vetor de predecessores.
    for(int i = 0; i < G->Qnt_V; i++)
        Predecessor[i] = -1;

    // Loop: Montar conjuntos.
    for(int i = 0; i < G->Qnt_E; i++){

        int RV = FindSet_Otimizado_(Predecessor, Arestas[i].V); // Encontra a raiz do vertice V.
        int RW = FindSet_Otimizado_(Predecessor, Arestas[i].W); // Encontra a raiz do vertice W.
        
        if(RV != RW)
            Union_(&Predecessor, RV, RW);
    }

    return Predecessor;
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/