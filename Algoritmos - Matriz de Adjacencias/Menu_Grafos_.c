/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de um menu funcional e
    interativo para auxiliar na contrucao de Grafos, realizacao de
    consultas e testes com os Grafos.
*/

#include <regex.h>
#include <strings.h>
#include "Grafos_.c"
#include "Percursos_.c"
#include "Utilitarios_.c"
#include "Arvore_Geradora_.c"

// Menu principal.
#define CRIAR 1
#define INSERIR 2
#define IMPRIMIR 3
#define REMOVER 4
#define ALGORITMOS 5
#define DELETAR 6
#define SAIR 7

// Menu de algoritmos.
#define LARGURA 1
#define PROFUNDIDADE 2
#define BIPARTIDO 3
#define PRIM 4
#define KRUSKAL 5
#define VOLTAR 6

// Macros.
#define PARTIDA 0
#define CHEGADA 1
#define GRAFO_CRIADO     printf("|----| [0_0] Grafo criado com sucesso.\n");
#define ARESTA_INSERIDA  printf("|----| [0_0] Aresta inserida com sucesso.\n");
#define ARESTA_INVALIDA  printf("|----| [x_x] Aresta invalida !\n");
#define VERTICE_INVALIDO printf("|----| [x_x] Vertice invalido !\n");

Grafo *G = NULL;



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Funcao responsavel por exibir o menu
    principal e retornar o valor de uma
    operacao.
*/
int Menu_(){

    char Entrada[15];

    regex_t Numeracao_01, Numeracao_02;
    regcomp(&Numeracao_01, "^0[1-7]$", 0);  // Expressao regular (01-07).
    regcomp(&Numeracao_02, "^[1-7]$", 0);   // Expressao regular (1-7).

    do{

        printf("\n|----|________________________|");
        printf("\n|----|                        |");
        printf("\n| 01 |  CRIAR GRAFO.          |");
        printf("\n| 02 |  INSERIR ARESTAS.      |");
        printf("\n| 03 |  IMPRIMIR GRAFO.       |");
        printf("\n| 04 |  REMOVER ARESTA.       |");
        printf("\n| 05 |  TESTAR ALGORITMOS.    |");
        printf("\n| 06 |  DELETAR GRAFO.        |");
        printf("\n| 07 |  SAIR.                 |");
        printf("\n|----|________________________|");
        printf("\n|----| SELECIONE UMA OPCAO: ");

        scanf("%s", Entrada);

    }while(regexec(&Numeracao_01, Entrada, 0, NULL, 0) && regexec(&Numeracao_02, Entrada, 0, NULL, 0));
    
    // Transforma o valor da entrada para inteiro.
    int Operacao = (Entrada[0] -'0');
    if(!Operacao)
        Operacao = (Entrada[1] -'0');
    
    return Operacao;
}


/*
    Funcao responsavel por exibir o menu
    de algoritmos e retornar o valor de
    uma operacao.
*/
int Menu_Algoritmos_(){

    char Entrada[15];

    regex_t Numeracao_01, Numeracao_02;
    regcomp(&Numeracao_01, "^0[1-6]$", 0);  // Expressao regular (01-06).
    regcomp(&Numeracao_02, "^[1-6]$", 0);   // Expressao regular (1-6).

    do{

        printf("\n|----|________________________________________|");
        printf("\n|----|                                        |");
        printf("\n| 01 |  IMPRIMIR PERCURSO EM LARGURA.         |");
        printf("\n| 02 |  IMPRIMIR PERCURSO EM PROFUNDIDADE.    |");
        printf("\n| 03 |  VERIFICAR SE O GRAFO EH BIPARTIDO.    |");
        printf("\n| 04 |  ARVORE GERADORA MINIMA (PRIM).        |");
        printf("\n| 05 |  ARVORE GERADORA MINIMA (KRUSKAL).     |");
        printf("\n| 06 |  VOLTAR.                               |");
        printf("\n|----|________________________________________|");
        printf("\n|----| SELECIONE UMA OPCAO: ");

        scanf("%s", Entrada);
    }while(regexec(&Numeracao_01, Entrada, 0, NULL, 0) && regexec(&Numeracao_02, Entrada, 0, NULL, 0));
    
    // Transforma o valor da entrada para inteiro.
    int Operacao = (Entrada[0] -'0');
    if(!Operacao)
        Operacao = (Entrada[1] -'0');

    return Operacao;
}


/*
    Funcao responsavel por receber um vertice
    valido para a entrada dos algoritmos.
*/
int Escolher_Vertice_(int Direcao){
    
    int Vert = 0;

    // Loop: Escolher vertice.
    while(1){
        
        if(Direcao == PARTIDA) printf("\n|----| Insira o vertice de partida: ");
        if(Direcao == CHEGADA) printf("|----| Insira o vertice de chegada: ");
        scanf("%d", &Vert);

        // Verifica se o vertice existe no grafo.
        if((Vert > 0) && (Vert <= G->Qnt_V)) break;
        else VERTICE_INVALIDO
    }

    // Correcao de indice.
    return Vert-1;
}



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Funcao responsavel por realizar a chamada
    dos algoritmos seguindo a logica do menu.
*/
void Algoritmos_(){

    int V, W;
    int Operacao;
    int *Predecessor;

    do{

        Operacao = Menu_Algoritmos_();  // Operacao escolhida.

        switch(Operacao){
            case (LARGURA):

                V = Escolher_Vertice_(PARTIDA);
                Imprimir_Percurso_em_Largura_(G, V);
                break;
            case (PROFUNDIDADE):

                V = Escolher_Vertice_(PARTIDA);
                Imprimir_Percurso_em_Profundidade_(G, V);
                break;
            case (BIPARTIDO):

                V = Escolher_Vertice_(PARTIDA);
                if(Verificar_Grafo_Bipartido_(G, V)) printf("|----| SIM.");
                else                                 printf("|----| NAO.");
                break;
            case (PRIM):

                V = Escolher_Vertice_(PARTIDA);
                W = Escolher_Vertice_(CHEGADA);
                Predecessor = Arvore_Geradora_Minima___PRIM_(G, V);
                Imprimir_Caminho_(Predecessor, V, W);
                break;
            case (KRUSKAL):

                V = Escolher_Vertice_(PARTIDA);
                W = Escolher_Vertice_(CHEGADA);
                Predecessor = Arvore_Geradora_Minima___KRUSKAL_(G);
                Imprimir_Caminho_(Predecessor, V, W);
                break;
        }

        printf("\n\n\n");
    }while(Operacao != VOLTAR);
}


/* 
    Main:
    Funcao principal responsavel por realizar
    as principais operacoes com grafos.
*/
int main(){

    int N, M;
    int Operacao;
    int V, W, Peso;

    do{
        Operacao = Menu_();  // Operacao escolhida.

        switch(Operacao){
            case (CRIAR):

                Deletar_Grafo_(G);
                printf("\n|----| Insira a quantidade de vertices:   ");     scanf("%d", &N);
                G = Criar_Grafo_(N);
                if(G) GRAFO_CRIADO
                break;
            case (INSERIR):

                if(G){
                    
                    printf("\n|----| Informe a quantidade de arestas:   "); scanf("%d", &M);

                    // Loop: Inserir arestas.
                    int i = 0;
                    while(i < M){
                        printf("\n|----|--------------------------------------|\n");
                        printf("|----| Indique o vertice de partida:    "); scanf("%d", &V);
                        printf("|----| Indique o vertice de chegada:    "); scanf("%d", &W);
                        printf("|----| Indique o peso da aresta:        "); scanf("%d", &Peso);
                        
                        // Verifica se os vertices existem no grafo.
                        if((V > 0) && (V <= G->Qnt_V) && (W > 0) && (W <= G->Qnt_V)){
                            
                            i++;
                            if(!Verificar_Adjacencia_(G, V-1, W-1)){
                                Inserir_Aresta_(G, V-1, W-1, Peso);
                                ARESTA_INSERIDA
                            }
                        }
                        else ARESTA_INVALIDA
                    }
                }
                else SEM_GRAFO
                break;
            case (IMPRIMIR):
            
                Imprimir_Grafo_(G);
                break;
            case (REMOVER):

                if(G){
                    
                    V = Escolher_Vertice_(PARTIDA);
                    W = Escolher_Vertice_(CHEGADA);

                    if(Verificar_Adjacencia_(G, V, W)){
                        Remover_Aresta_(G, V, W);
                        printf("|----| [0_0] Aresta removida com sucesso !\n");
                    }
                }
                else SEM_GRAFO
                break;
            case (DELETAR):

                Deletar_Grafo_(G);
                G = NULL;
                break;
            case (ALGORITMOS):
                
                if(G && G->Qnt_E) Algoritmos_();
                else SEM_GRAFO
                break;
            case (SAIR):

                Deletar_Grafo_(G);
                printf("|----| [0_0] Ta baum entao... Tchau.\n");
                break;
        }
        
        printf("\n\n\n");
    }while(Operacao != SAIR);

    return 0;
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/