#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIM         1           // True.
#define NAO         0           // False.
#define SEM_ARESTA  0
#define INFINITO    INT_MAX/2   // Valor maximo.
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
/*<<=============================>> PERCURSOS EM GRAFOS <<=============================>>*/
/*<<===================================================================================>>*/

void Imprimir_Percurso_Largura_(Grafo *G, int Raiz);
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

#endif

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/