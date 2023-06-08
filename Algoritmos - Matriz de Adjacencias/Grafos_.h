#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Fila_.c"

#define SIM         1           // True.
#define NAO         0           // False.
#define SEM_ARESTA  0
#define INFINITO    INT_MAX/2   // Valor maximo.
#define SEM_GRAFO   printf("|----| [0_0] Voce nao tem um grafo.\n");
#define SEM_MEMORIA printf("|----| [x_x] Sem memoria disponivel !\n");



/*<<===================================================================================>>*/
/*<<==================================>> ESTRUTURA <<==================================>>*/
/*<<===================================================================================>>*/

/*
    Estrutura representativa de um grafo
    usando matriz de adjacencias.
*/
typedef struct Grafo{
    int Qnt_V;  // Quantidade de vertices.
    int Qnt_E;  // Quantidade de arestas.
    int **Adj;  // Matriz de adjacencias (N x N).
}Grafo;

int **Criar_Matriz_Adj_(int N);
Grafo *Criar_Grafo_(int N);
void Inserir_Aresta_(Grafo *G, int V, int W, int Peso);
void Remover_Aresta_(Grafo *G, int V, int W);
void Imprimir_Grafo_(Grafo *G);
void Deletar_Grafo_(Grafo *G);



/*<<===================================================================================>>*/
/*<<=============================>> PERCURSOS EM GRAFOS <<=============================>>*/
/*<<===================================================================================>>*/

void Imprimir_Percurso_em_Largura_(Grafo *G, int Raiz);
int  Verificar_Grafo_Bipartido_(Grafo *G, int Raiz);
void Percurso_em_Profundidade_(Grafo *G, int Raiz, int **Alcancados, Queue *Explorados);
void Imprimir_Percurso_em_Profundidade_(Grafo *G, int Raiz);



/*<<===================================================================================>>*/
/*<<============================>> UTILITARIOS EM GRAFOS <<============================>>*/
/*<<===================================================================================>>*/

/*
    Estrutura representativa de uma aresta.
*/
typedef struct Aresta{
    int V;      // Vertice de partida.
    int W;      // Vertice de chegada.
	int Peso;   // Peso da aresta.
}Aresta;

Aresta *Criar_Vetor_Arestas_(Grafo *G);
int    Calcular_Grau_(Grafo *G, int V);
int    Verificar_Adjacencia_(Grafo *G, int V, int W);
void   Imprimir_Adjacentes_(Grafo *G, int V);
void   Imprimir_Caminho_(int *Predecessor, int Raiz, int V);
void   Ordenar_Arestas___Insertion_Sort_(Aresta *Arestas, int Tam);



/*<<===================================================================================>>*/
/*<<===========================>>  ARVORE GERADORA MINIMA <<===========================>>*/
/*<<===================================================================================>>*/

void Union_(int **Predecessores, int V, int W);
int  FindSet_(int *Predecessor, int V);
int  FindSet_Otimizado_(int *Predecessores, int V);
int  *Arvore_Geradora_Minima___PRIM_(Grafo *G, int Raiz);
int  *Arvore_Geradora_Minima___KRUSKAL_(Grafo *GRAFOS_H);
int  Encontrar_Menor_Estimativa_(int *Distancias, int *Analisados, int Num_vertices);

#endif

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/