#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIM         1           // True.
#define NAO         0           // False.
#define SEM_ARESTA  0
#define INFINITO    INT_MAX/2   // Valor maximo.
#define SEM_FILA    printf("\n|----| [0_0] Voce nao tem uma fila.\n");
#define SEM_GRAFO   printf("\n|----| [0_0] Voce nao tem um grafo.\n");
#define SEM_MEMORIA printf("\n|----| [x_x] Sem memoria disponivel !\n");



/*<<===================================================================================>>*/
/*<<==================================>> ESTRUTURA <<==================================>>*/
/*<<===================================================================================>>*/

/*
    Estrutura representativa de um vertice.
*/
typedef struct Vertice{
    int No;                 // Identificador do vertice.
    int Peso;               // Peso de uma aresta.
    struct Vertice *Prox;   // Ponteiro para vertices adjacentes.
}Vertice;

/*
    Estrutura representativa de um grafo
    usando lista de adjacencias.
*/
typedef struct Grafo{
    int Qnt_V;      // Quantidade de vertices.
    int Qnt_E;      // Quantidade de arestas.
    Vertice *Adj;   // Lista de adjacencias.
}Grafo;

Grafo *Criar_Grafo_(int N);
Vertice *Criar_Vertice_(int Identificador, int Peso);
void Inserir_Aresta_(Grafo *G, int V, int W, int Peso);
void Remover_Aresta_(Grafo *G, int V, int W);
void Imprimir_Grafo_(Grafo *G);
void Deletar_Grafo_(Grafo *G);



/*<<===================================================================================>>*/
/*<<===============================>>  ESTRUTURA FILA <<===============================>>*/
/*<<===================================================================================>>*/

/*
    Estrutura representativa
    de uma fila de vertices.
*/
typedef struct{
    int Size;       // Tamanho da fila.
    Vertice *First; // Ponteiro para o primeiro vertice da fila.
    Vertice *Last;  // Ponteiro para o ultimo vertice da fila.
}Queue;

Queue *Criar_Fila_();
void Inserir_Vertice_Fila_(Queue *Fila, int Identificador);
int Remover_Vertice_Fila_(Queue *Fila);
void Imprimir_Fila_(Queue *Fila);
void Deletar_Fila_(Queue *Fila);



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