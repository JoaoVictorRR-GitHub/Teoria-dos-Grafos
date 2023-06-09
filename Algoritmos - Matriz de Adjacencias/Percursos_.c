/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de algoritmos que utilizam,
    ou realizam, percursos para solucionar problemas de grafos com
    uma matriz de adjacencias.
*/

#include "Grafos_.h"



/*<<===================================================================================>>*/
/*<<============================>>  PERCURSOS EM LARGURA <<============================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por explorar um grafo, usando o
    percurso em largura, e imprimir o caminho realizado.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ RAIZ ].

    @ Saida:
    - ( void )
*/
void Imprimir_Percurso_em_Largura_(Grafo *G, int Raiz){

    int V, W;                                                       // Indice dos vertices.
    int *Alcancado        = (int*) calloc(G->Qnt_V, sizeof(int));   // Conjunto de vertices alcancados.
    Queue *Explorados     = Criar_Fila_();                          // Conjunto de vertices explorados.
    Queue *Nao_explorados = Criar_Fila_();                          // Conjunto de vertices nao explorados.

    Alcancado[Raiz] = SIM;
    Inserir_Vertice_Fila_(Nao_explorados, Raiz);


    /*  Loop para percorrer a fila
        de vertices nao explorados. */
    while(Nao_explorados->First != NULL){

        V = Remover_Vertice_Fila_(Nao_explorados);

        /*  Loop para percorrer o conjunto
            de vertices adjacentes a V. */
        for(W = 0; W < G->Qnt_V; W++){

            if((Alcancado[W] == NAO) && Verificar_Adjacencia_(G, V, W)){
                
                Alcancado[W] = SIM;                         // Indica que o vertice W foi alcancado.
                Inserir_Vertice_Fila_(Nao_explorados, W);   // Insere W na fila de vertices nao explorados.
            }
        }

        Inserir_Vertice_Fila_(Explorados, V);   // Insere V no conjunto de vertices ja explorados.

        /*  [GRAFOS DESCONEXOS] Verifica se existe
            algum vertice desconexo nao explorado.  */
        if((Nao_explorados->First == NULL) && (Explorados->Size < G->Qnt_V)){

            for(V = 0; V < G->Qnt_V; V++){

                if(Alcancado[V] == NAO){

                    Alcancado[V] = SIM;                         // Indica que o vertice V foi alcancado.
                    Inserir_Vertice_Fila_(Nao_explorados, V);   // Insere V na fila de vertices nao explorados.
                    break;
                }
            }
        }
    }

    Imprimir_Fila_(Explorados); // Imprime o percuro em largura realizado no grafo.
    Deletar_Fila_(Explorados);
    Deletar_Fila_(Nao_explorados);
    free(Alcancado);
}


/*
    Metodo responsavel por verificar se um um grafo
    eh bipartido usando o percurso em largura.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ RAIZ ].

    @ Saida:
    - [ 0 ] - Nao eh bipartido.
    - [ 1 ] - Eh bipartido.
*/
int Verificar_Grafo_Bipartido_(Grafo *G, int Raiz){

    int V, W;               // Indice dos vertices.
    int Alc = 0;            // Contador de vertices alcancados.
    int Eh_Bipartido = SIM; // Indica que o grafo eh biartido inicialmente.

    int *Nivel            = (int*) calloc(G->Qnt_V, sizeof(int));   // Nivel de cada vertice.
    int *Alcancado        = (int*) calloc(G->Qnt_V, sizeof(int));   // Conjunto de vertices alcancados.
    Queue *Nao_explorados = Criar_Fila_();                          // Conjunto de vertices nao explorados.

    Nivel[Raiz]     = 1;
    Alcancado[Raiz] = ++Alc;
    Inserir_Vertice_Fila_(Nao_explorados, Raiz);


    /*  Loop para percorrer o conjunto
        de vertices nao explorados. */
    while(Nao_explorados->First != NULL){

        V = Remover_Vertice_Fila_(Nao_explorados);

        /*  Loop para percorrer o conjunto
            de vertices adjacentes a V. */
        for(W = 0; W < G->Qnt_V; W++){

            if(Verificar_Adjacencia_(G, V, W)){

                if(Alcancado[W] == NAO){

                    Alcancado[W] = ++Alc;                       // Indica que o vertice W foi alcancado.
                    Nivel[W]     = Nivel[V] +1;                 // Atualiza o nivel de W a partir do nivel de V.
                    Inserir_Vertice_Fila_(Nao_explorados, W);   // Insere W na fila de vertices nao explorados.
                }

                // Verifica se o grafo nao eh bipartido.
                if((Alcancado[V] < Alcancado[W]) && (Nivel[V] == Nivel[W])){

                    Deletar_Fila_(Nao_explorados);
                    Eh_Bipartido = NAO;
                    return Eh_Bipartido;
                }
            }
        }

        /*  [GRAFOS DESCONEXOS] Verifica se existe
            algum vertice desconexo nao explorado.  */
        if(Nao_explorados->First == NULL){

            for(V = 0; V < G->Qnt_V; V++){
                
                if(Alcancado[V] == NAO){

                    Alcancado[V] = SIM;                         // Indica que o vertice V foi alcancado.
                    Inserir_Vertice_Fila_(Nao_explorados, V);   // Insere V na fila de vertices nao explorados.
                    break;
                }
            }
        }
    }

    Deletar_Fila_(Nao_explorados);
    free(Alcancado);
    free(Nivel);
    return Eh_Bipartido;
}



/*<<===================================================================================>>*/
/*<<==========================>> PERCURSOS EM PROFUNDIDADE <<==========================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por explorar um grafo usando
    o percurso em profundidade recursivamente.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ RAIZ ].
    + Conjunto de vertices alcancados [ ALCANCADOS ].
    + Conjunto de vertices explorados [ EXPLORADOS ].

    @ Saida:
    - ( void )
*/
void Percurso_em_Profundidade_(Grafo *G, int Raiz, int **Alcancados, Queue *Explorados){

    (*Alcancados)[Raiz] = SIM;  // Indica que o vertice 'Raiz' foi alcancado.

    /*  Loop para percorrer o conjunto
        de vertices adjacentes a 'Raiz'.    */
    for(int W = 0; W < G->Qnt_V; W++){

        // Percurso em profundidade recursivo.
        if(((*Alcancados)[W] == NAO) && Verificar_Adjacencia_(G, Raiz, W))
            Percurso_em_Profundidade_(G, W, Alcancados, Explorados);
    }

    // Insere a raiz no conjunto de vertices ja explorados.
    Inserir_Vertice_Fila_(Explorados, Raiz);
}


/*
    Metodo auxiliar responsavel por explorar um grafo, usando
    o percurso em profundidade, e imprimir o caminho realizado.

    @ Entrada:
    + Grafo [ G ].
    + Vertice de partida [ RAIZ ].

    @ Saida:
    - ( void )
*/
void Imprimir_Percurso_em_Profundidade_(Grafo *G, int Raiz){

    int *Alcancados   = (int*) calloc(G->Qnt_V, sizeof(int));   // Conjunto de vertices alcancados.
    Queue *Explorados = Criar_Fila_();                          // Conjunto de vertices explorados.

    Percurso_em_Profundidade_(G, Raiz, &Alcancados, Explorados);

    /*  [GRAFOS DESCONEXOS] Verifica se existe
        algum vertice desconexo nao explorado.  */
    if(Explorados->Size != G->Qnt_V){

        for(int V = 0; V < G->Qnt_V; V++){

            if(Alcancados[V] == NAO)
                Percurso_em_Profundidade_(G, V, &Alcancados, Explorados);
            
            if(Explorados->Size == G->Qnt_V)
                break;
        }
    }

    Imprimir_Fila_(Explorados); // Imprime o percuro em profundidade realizado no grafo.
    Deletar_Fila_(Explorados);
    free(Alcancados);
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/