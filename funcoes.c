#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

#define TOTAL_ASSENTOS 180
#define TOTAL_VOOS 10

void inicializarAssentos( Assento *listaAssentos, int qtdAssentosOcupados ) {
    int i;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        if(i<qtdAssentosOcupados) {
            listaAssentos[i].ocupado = 1;
            listaAssentos[i].numero = i+1;
        } else {
            listaAssentos[i].ocupado = 0;
            listaAssentos[i].numero = i+1;
        }
    }
}

int reservarAssento( int numAssento, Voo *voo ) {
    int i;

    for(i=0; i<TOTAL_ASSENTOS; i++) {
        if(voo->listaAssentos[i].numero == numAssento) {
            if(voo->listaAssentos[i].ocupado == 1) {
                return -1; // Falha ao reservar assento, assento ocupado
            } else {
                voo->listaAssentos[i].ocupado = 1;
                return 1; // Assento reservado com sucesso
            }
        }
    }

    return 0; // Não existe assento com esse número
}

int liberarAssento( Voo *voo, int numAssento ) {
    int i;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        if(voo->listaAssentos[i].numero == numAssento) {
            voo->listaAssentos[i].ocupado = 0;
            return 1; // Assento liberado com sucesso
        }
    }
    return -1; // Não existe assento com esse número
}

Voo *carregarVoos( char *Arquivo ) {
    int i;
    FILE *f = fopen(Arquivo, "r");

    if( f == NULL) {
        printf("Erro ao carregar os voos\n");
        return NULL;
    }

    Voo *voos = (Voo*)malloc(TOTAL_VOOS*sizeof(Voo));

    for(i=0; i<TOTAL_VOOS; i++) {
        if(fscanf(f, "%d %s %s %d", &voos[i].id, voos[i].destino, voos[i].origem, voos[i].qtdAssentosOcupados) != 4) {
            
            free(voos);
            fclose(f);
            return NULL;
        }
        voos[i].listaAssentos = malloc(TOTAL_ASSENTOS * sizeof(Assento));
        inicializarAssentos(voos[i].listaAssentos, voos[i].qtdAssentosOcupados);
    }

    fclose(f);
    return voos;
}

int qtdAssentosLivres( Voo *voo ) {
    int i, count = 0;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        if(voo->listaAssentos[i].ocupado == 0) count++;
    }

    return count;
}

Voo *buscarVooPorId( Voo *listaVoos, int idVoo) {
    int i;

    for(i=0; i<TOTAL_VOOS; i++) {
        if(listaVoos[i].id == idVoo) return &listaVoos[i];
    }

    printf("Não existe um voo com esse id!\n");
    return NULL;
}

void exibirVoos( Voo *listaVoos ) {
    int i;

    printf("=====================================\n");
    printf("       VOOS DISPONIVEIS               \n");
    printf("=====================================\n");
    for(i=0; i<TOTAL_VOOS; i++) {
        printf("Voo (ID %d):\n", listaVoos[i].id);
        printf("- Destino: %s\n", listaVoos[i].destino);
        printf("- Origem: %s\n", listaVoos[i].origem);
        printf("- Número de assentos disponiveis: %d\n", qtdAssentosLivres(&listaVoos[i]));
        printf("-----------------------------------------\n");
    }

    //colocar dentro do for a função de exibir assentos
}

// lista encadeada de passageiros
Passageiro* cadastrarPassageiro(Passageiro *lista) {
    Passageiro *novo = (Passageiro*)malloc(sizeof(Passageiro));
    if (novo == NULL) return lista;

    printf("ID do Passageiro: ");
    scanf("%d", &novo->id);
    printf("Nome: ");
    scanf(" %[^\n]", novo->nome);
    printf("Idade: ");
    scanf("%d", &novo->idade);
    
    // inicialmente sem passagens vinculadas
    novo->passagens = NULL; 
    
    // Big O(1) pq ta cadastrando no inicio da lista, entao nao precisa percorrer o vetor    
    novo->prox = lista;
    
    return novo;
}
