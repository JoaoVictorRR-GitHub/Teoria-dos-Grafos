/*
    @ Autor:
        * Joao Victor do Rozario Recla.
    @ Atuacao:
        * Estudante.
    @ Instituicao:
        * UFES   - Universidade Federal do Espirito Santo.
        * CEUNES - Centro universitario Norte do Espirito Santo.
    
    Este arquivo contem a implementacao de metodos basicos para
    criar e deletar filas de vertices, criar, inserir e remover
    estruturas de vertices.
*/

#include <stdio.h>
#include <stdlib.h>

#define SEM_FILA    printf("|----| [0_0] Voce nao tem uma fila.\n");
#define SEM_VERTICE printf("|----| [0_0] Voce nao tem um vertice.\n");
#define SEM_MEMORIA printf("|----| [x_x] Sem memoria disponivel !\n");



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Estrutura representativa de um vertice.
*/
typedef struct Vertice{
    int No;                 // Identificador do vertice.
    struct Vertice *Prox;   // Ponteiro para o proximo vertice na fila.
}Vertice;

/*
    Estrutura representativa
    de uma fila de vertices.
*/
typedef struct{
    int Size;       // Tamanho da fila.
    Vertice *First; // Ponteiro para o primeiro vertice da fila.
    Vertice *Last;  // Ponteiro para o ultimo vertice da fila.
}Queue;



/*<<===================================================================================>>*/
/*<<===================================================================================>>*/

/*
    Metodo responsavel por criar e
    inicializar a estrutura de uma fila.

    @ Entrada:
    + ( void ).

    @ Saida:
    - Fila [ FILA ].
*/
Queue *Criar_Fila_(){

    Queue *Fila = (Queue*) malloc(sizeof(Queue));

    if(Fila){
        Fila->Size  = 0;
        Fila->First = NULL;
        Fila->Last  = NULL;
    }
    else SEM_MEMORIA

    return Fila;
}


/*
    Metodo responsavel por criar e inicializar
    a estrutura de um vertice.

    @ Entrada:
    + Identificador do vertice [ IDENTIFICADOR ].

    @ Saida:
    - Vertice [ VERT ].
*/
Vertice *Criar_Vertice_(int Identificador){

    Vertice *Vert = (Vertice*) malloc(sizeof(Vertice));

    if(Vert){
        Vert->No   = Identificador;
        Vert->Prox = NULL;
    }
    else SEM_MEMORIA

    return Vert;
}


/*
    Metodo responsavel por inserir a estrutura
    de um vertice no final de uma fila.
    
    @ Entrada:
    + Fila [ FILA ].
    + Identificador do vertice [ IDENTIFICADOR ].

    @ Saida:
    - ( void ).
*/
void Inserir_Vertice_Fila_(Queue *Fila, int Identificador){
    
    if(Fila){

        // Verifica se a fila esta vazia.
        if(Fila->Size == 0){

            Fila->First = Criar_Vertice_(Identificador);
            Fila->Last  = Fila->First;
        }
        else{
            
            Fila->Last->Prox = Criar_Vertice_(Identificador);
            Fila->Last       = Fila->Last->Prox;
        }

        Fila->Size++;
    }
    else SEM_FILA
}


/*
    Metodo responsavel por remover a estrutura de
    um vertice, do inicio de uma fila, retornando
    seu identificador.
    
    @ Entrada:
    + Fila [ FILA ].

    @ Saida:
    - Identificador do vertice [ IDENTIFICADOR ].
*/
int Remover_Vertice_Fila_(Queue *Fila){

    int Identificador = 0;

    if(Fila){
        
        Vertice *Aux  = Fila->First;
        Fila->First   = Aux->Prox;
        Identificador = Aux->No;

        Fila->Size--;
        free(Aux);  // Deleta a estrutura do vertice.
    }
    else SEM_FILA
    
    return Identificador;
}


/*
    Metodo responsavel por imprimir a estrutura de
    uma fila exibindo todos os seus vertices.

    @ Entrada:
    + Fila [ FILA ].

    @ Saida:
    - ( void ).
*/
void Imprimir_Fila_(Queue *Fila){

    if(Fila){

        Vertice *Aux = Fila->First;

        // Loop: Imprimir vertices.
        printf("|----|");
        while(Aux){

            printf(" %02d", Aux->No+1);
            Aux = Aux->Prox;
        }
        printf("\n");
    }
    else SEM_FILA
}


/*
    Metodo responsavel por deletar uma fila
    removendo cada estrutura de um vertice.

    @ Entrada:
    + Fila [ FILA ].

    @ Saida:
    - ( void ).
*/
void Deletar_Fila_(Queue *Fila){

    if(Fila){

        Vertice *Aux;

        // Loop: Deletar vertices.
        while(Fila->First){

            Aux         = Fila->First;
            Fila->First = Fila->First->Prox;
            free(Aux);
        }

        free(Fila); // Deleta a estrutura da fila.
    }
}

/*<<===================================================================================>>*/
/*<<===================================================================================>>*/