/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de metodos basicos para
    criar, exibir e deletar grafos representados por uma matriz
    de adjacencias, inserir e remover arestas.
*/

#include "Grafos_.h"



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por criar e inicializar a
    estrutura de uma matriz de adjacencias (N x N).

    @ Entrada:
    + Numero de linhas e colunas [ N ].

    @ Saida:
    - Matriz de adjacencias [ MATRIZ ].
*/
int **Criar_Matriz_Adj_(int N){

    int **Matriz = (int**) malloc(N * sizeof(int*));    // Alocacao das linhas.
    
    for(int i = 0; i < N; i++)
        Matriz[i] = (int*) calloc(N, sizeof(int));      // Alocacao das colunas.

    return Matriz;
}


/*
    Metodo responsavel por criar e
    inicializar a estrutura de um grafo.

    @ Entrada:
    + Quantidade de vertices [ N ].

    @ Saida:
    - Grafo [ G ].
*/
Grafo *Criar_Grafo_(int N){

    Grafo *G = (Grafo*) malloc(sizeof(Grafo));

    if(G){
        G->Qnt_V = N;
        G->Qnt_E = 0;
        G->Adj   = Criar_Matriz_Adj_(N);
    }
    else SEM_MEMORIA

    return G;
}


/*
    Metodo responsavel por inserir uma
    aresta, e seu peso, em um grafo.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ V ].
    + Vertice de chegada [ W ].
    + Peso da aresta [ PESO ].

    @ Saida:
    - ( void )
*/
void Inserir_Aresta_(Grafo *G, int V, int W, int Peso){

    if(G){
        G->Adj[V][W] = Peso;    // Insere a aresta (V, W).
        G->Adj[W][V] = Peso;    // Insere a aresta (W, V).
        G->Qnt_E++;             // Atualiza a quantidade de arestas.
    }
    else SEM_GRAFO
}


/*
    Metodo responsavel por remover
    uma aresta de um grafo.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ V ].
    + Vertice de chegada [ W ].
    
    @ Saida:
    - ( void )
*/
void Remover_Aresta_(Grafo *G, int V, int W){

    if(G){
        G->Qnt_E--;                 // Atualiza a quantidade de arestas.
        G->Adj[V][W] = SEM_ARESTA;  // Remove a aresta (V, W).
        G->Adj[W][V] = SEM_ARESTA;  // Remove a aresta (W, V).
    }
    else SEM_GRAFO
}


/*
    Metodo responsavel por imprimir a estrutura de
    um grafo exibindo sua matriz de adjacencias.

    @ Entrada:
    + Grafo [ G ].
    
    @ Saida:
    - ( void )
*/
void Imprimir_Grafo_(Grafo *G){

    if(G){

        printf("\n  Grafo G:\n\n");
        for(int V = 0; V < G->Qnt_V; V++){

            // Imprime cada vertice de partida, V.
            printf("    %02d:", V+1);

            // Loop: Imprimir vertices adjacentes a V.
            for(int W = 0; W < G->Qnt_V; W++)
                if(Verificar_Adjacencia_(G, V, W))
                    printf(" %02d", W+1);
            
            printf("\n");
        }
    }
    else SEM_GRAFO
}


/*
    Metodo responsavel por deletar a estrutura
    de um grafo removendo a matriz de adjacencias.

    @ Entrada:
    + Grafo [ G ].
    
    @ Saida:
    - ( void )
*/
void Deletar_Grafo_(Grafo *G){

    if(G){

        // Deleta cada linha da matriz de adjacencia do grafo.
        for(int V = 0; V < G->Qnt_V; V++)
            free(G->Adj[V]);
        
        free(G->Adj);   // Deleta a matriz de adjacencias.
        free(G);        // Deleta o grafo.
    }
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/