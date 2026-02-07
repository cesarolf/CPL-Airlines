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
            listaAssentos[i].numero = i;
        } else {
            listaAssentos[i].ocupado = 0;
            listaAssentos[i].numero = i;
        }
    }
}

int reservarAssento( int numAssento, Voo *voo ) {
    int i;

    for(i=0; i<TOTAL_ASSENTOS; i++) {
        if(voo->listaAssentos[i].numero == numAssento) {
            if(voo->listaAssentos->ocupado == 1) {
                return -1; // Falha ao reservar assento, assento ocupado
            } else {
                voo->listaAssentos->ocupado = 1;
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
        fscanf(f, "%d %s %s %d", &voos[i].id, voos[i].destino, voos[i].origem, voos[i].qtdAssentosOcupados);
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