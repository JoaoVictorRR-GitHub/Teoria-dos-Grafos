/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de metodos basicos para
    criar, exibir e deletar grafos representados por uma lista
    de adjacencias, inserir e remover arestas.
*/

#include "Grafos_.h"



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

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
        G->Adj   = (Vertice*) calloc(N, sizeof(Vertice));

        // Numeracao da lista.
        for(int i = 0; i < N; i++)
            G->Adj[i].No = i;
    }
    else SEM_MEMORIA

    return G;
}


/*
    Metodo responsavel por criar e inicializar
    a estrutura de um vertice.

    @ Entrada:
    + Identificador do vertice [ IDENTIFICADOR ].

    @ Saida:
    - Vertice [ VERT ].
*/
Vertice *Criar_Vertice_(int Identificador, int Peso){

    Vertice *Vert = (Vertice*) malloc(sizeof(Vertice));

    if(Vert){
        Vert->No   = Identificador;
        Vert->Peso = Peso;
        Vert->Prox = NULL;
    }
    else SEM_MEMORIA

    return Vert;
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

        Vertice *Adj = G->Adj[V].Prox;

        // Loop: Encontrar W nas adjacencias de V.
        while(Adj){

            if(Adj->No == W) break;   // Encontrou o vertice W ja inserido.
            Adj = Adj->Prox;
        }

        // Insere o novo vertice na lista de adjacencia de V.
        if(Adj == NULL){

            Vertice *Novo = Criar_Vertice_(W, Peso);
            
            Novo->Prox     = G->Adj[V].Prox;
            G->Adj[V].Prox = Novo;
            G->Qnt_E++;
        }
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
void Remover_Aresta(Grafo *G, int V, int W){

    if(G){

        Vertice *Aux  = G->Adj[V].Prox;
        Vertice *Prev = &(G->Adj[V]);

        // Loop: Encontrar W nas adjacencias de V.
        while(Aux){
            
            if(Aux->No == W) break; // Encontrou o vertice W.
            Prev = Aux;
            Aux  = Aux->Prox;
        }

        // Remove o vertice W da lista de adjacencia de V.
        if(Aux){

            G->Qnt_E--;
            Prev->Prox = Aux->Prox;
            free(Aux);
        }
    }
    else SEM_GRAFO
}


/*
    Metodo responsavel por imprimir a estrutura de
    um grafo exibindo sua lista de adjacencias.

    @ Entrada:
    + Grafo [ G ].
    
    @ Saida:
    - ( void )
*/
void Imprimir_Grafo_(Grafo *G){

    if(G){

        Vertice *W;

        printf("\n  Grafo G:\n\n");
        for(int V = 0; V < G->Qnt_V; V++){

            // Imprime cada vertice de partida, V.
            printf("    %02d:", V+1);
            W = G->Adj[V].Prox;

            // Loop: Imprimir vertices adjacentes a V.
            while(W != NULL){
                
                printf(" %02d", W->No+1);
                W = W->Prox;
            }
            printf("\n");
        }
    }
    else SEM_GRAFO
}


/*
    Metodo responsavel por deletar a estrutura
    de um grafo removendo a lista de adjacencias.

    @ Entrada:
    + Grafo [ G ].
    
    @ Saida:
    - ( void )
*/
void Deletar_Grafo_(Grafo *G){

    if(G){         

        // Loop: Deletar cada lista do grafo.
        for(int V = 0; V < G->Qnt_V; V++){

            Vertice *W = G->Adj[V].Prox;

            // Loop: Deletar cada vertice adjacente a V.
            while(W){

                Vertice *Aux = W->Prox;
                free(W);
                W = Aux;
            }
        }
        
        free(G->Adj);   // Deleta a lista de adjacencias.
        free(G);        // Deleta o grafo.
    }
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/