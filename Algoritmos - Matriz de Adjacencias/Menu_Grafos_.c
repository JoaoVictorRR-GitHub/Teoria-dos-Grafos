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
#define LIMPAR           printf("\n\n\n\n\n\n\n\n\n");
#define GRAFO_CRIADO     printf("|----| [0_0] Grafo criado com sucesso.\n\n");
#define ARESTA_INSERIDA  printf("|----| [0_0] Aresta inserida com sucesso.\n\n");
#define ARESTA_REMOVIDA  printf("|----| [0_0] Aresta removida com sucesso.\n\n");
#define ARESTA_INVALIDA  printf("|----| [x_x] Aresta invalida !\n\n");
#define VERTICE_INVALIDO printf("|----| [x_x] Vertice invalido !\n\n");

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
    printf("\n");
    
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

        printf("\n|----|________________________________________________________|");
        printf("\n|----|                                                        |");
        printf("\n| 01 |  IMPRIMIR PERCURSO EM LARGURA.                         |");
        printf("\n| 02 |  IMPRIMIR PERCURSO EM PROFUNDIDADE.                    |");
        printf("\n| 03 |  VERIFICAR SE O GRAFO EH BIPARTIDO.                    |");
        printf("\n| 04 |  IMPRIMIR CAMINHO NA ARVORE GERADORA MINIMA (PRIM).    |");
        printf("\n| 05 |  IMPRIMIR CAMINHO NA ARVORE GERADORA MINIMA (KRUSKAL). |");
        printf("\n| 06 |  VOLTAR.                                               |");
        printf("\n|----|________________________________________________________|");
        printf("\n|----| SELECIONE UMA OPCAO: ");

        scanf("%s", Entrada);
    }while(regexec(&Numeracao_01, Entrada, 0, NULL, 0) && regexec(&Numeracao_02, Entrada, 0, NULL, 0));
    printf("\n");

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
        
        if(Direcao == PARTIDA) printf("|----| Insira o vertice de partida:\t");
        if(Direcao == CHEGADA) printf("|----| Insira o vertice de chegada:\t");
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
    int *Predecessor = NULL;

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

                if(Verificar_Grafo_Bipartido_(G, V)) printf("|----| SIM.");
                else                                 printf("|----| NAO.");
            break;
            case (PRIM):

                V = Escolher_Vertice_(PARTIDA);
                W = Escolher_Vertice_(CHEGADA);

                Predecessor = Arvore_Geradora_Minima___PRIM_(G, V);
                Imprimir_Caminho_(Predecessor, V, W);

                free(Predecessor); Predecessor = NULL;
            break;
            case (KRUSKAL):

                Predecessor = Arvore_Geradora_Minima___KRUSKAL_(G);

                // Loop: Imprimir arvore geradora minima (KRUSKAL).
                for(int i = 0; i < G->Qnt_V; i++){
                    if(Predecessor[i] < 0) printf("\n|----| Raiz:   %d", i+1);
                    else                   printf("\n|----| Aresta: (%d, %d)", i+1, Predecessor[i]+1);
                }

                free(Predecessor); Predecessor = NULL;
            break;
        }

        LIMPAR
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
                printf("|----| Insira a quantidade de vertices:\t"); scanf("%d", &N);
                G = Criar_Grafo_(N);
                if(G) GRAFO_CRIADO
            break;
            case (INSERIR):

                if(G){
                    printf("|----| Informe a quantidade de arestas:\t"); scanf("%d", &M);

                    // Loop: Inserir arestas.
                    for(int i = 0; i < M; i++){

                        printf("|----|--------------------------------------|\n");
                        V = Escolher_Vertice_(PARTIDA);
                        W = Escolher_Vertice_(CHEGADA);
                        printf("|----| Indique o peso da aresta:\t"); scanf("%d", &Peso);

                        Inserir_Aresta_(G, V, W, Peso); // Aresta (V, W).
                        Inserir_Aresta_(G, W, V, Peso); // Aresta (W, V).
                        ARESTA_INSERIDA
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

                    Remover_Aresta_(G, V, W);   // Aresta (V, W).
                    Remover_Aresta_(G, W, V);   // Aresta (W, V).
                    ARESTA_REMOVIDA
                }
                else SEM_GRAFO
            break;
            case (DELETAR):

                Deletar_Grafo_(G);
                G = NULL;
            break;
            case (ALGORITMOS):
                
                if(G && G->Qnt_E){
                    LIMPAR
                    Algoritmos_();
                }
                else SEM_GRAFO
                break;
            case (SAIR):

                Deletar_Grafo_(G);
                printf("|----| [0_0] Ta baum entao... Tchau.\n");
            break;
        }
        
        LIMPAR
    }while(Operacao != SAIR);

    return 0;
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/