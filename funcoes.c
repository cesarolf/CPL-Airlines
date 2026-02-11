#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void inicializarAssentos( Assento *listaAssentos, int qtdAssentosOcupados ) {
    int i;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        if(i<qtdAssentosOcupados) {           // Esse if pode estar colocando acentos vagos como ocupados, não?
            listaAssentos[i].ocupado = 1;     // Olha ali em baixo se fica melhor
            listaAssentos[i].numero = i+1;
        } else {
            listaAssentos[i].ocupado = 0;
            listaAssentos[i].numero = i+1;
        }
    }
}
/*
void inicializarAssentos(Assento *listaAssentos) {
    for(int i = 0; i < TOTAL_ASSENTOS; i++) {
        listaAssentos[i].numero = i + 1;
        listaAssentos[i].ocupado = 0;
    }
}
*/

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

    // Da pra diminuir a complexidade se fizer assim ou nada haver?
    /*
    if ( numAssento > TOTAL_ASSENTOS || numAssento < 0 ) return 0;   // Não existe assento com esse número
    else if ( voo->listaAssentos[numAssento-1].ocupado == 1 ) return -1;  // Falha ao reservar assento, assento ocupado
    else voo->listaAssentos[numAssento-1].ocupado = 1;
        return 1;// Assento reservado com sucesso
    */
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

    // Mesma coisa aqui, acho que tem como melhorar
    /*
    if ( numAssento > TOTAL_ASSENTOS || numAssento < 0 ) return -1; // Não existe
    else voo->listaAssentos[numAssento-1].ocupado = 0; // Liberado com sucesso
    */
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
        mostrarAssentos( listaVoos[i].listaAssentos);
    }

    //colocar dentro do for a função de exibir assentos
    //colocado
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

void mostrarAssentos( Assento *listaAssentos ){

    int i, flgQuebraLinha = 0;

    printf("               DISPOSICAO DE ASSENTOS DO AVIAO\n");
    printf("\n-----------------------------------------------------------------------------\n");
    for ( i = 0; i < TOTAL_ASSENTOS; i++){

        // faz o print do corredor do avião
        if((flgQuebraLinha+1) == 4 || (flgQuebraLinha+1) == 8) printf("|      ");
        
        // o X indica que o assento está ocupado
        if ( listaAssentos[i].ocupado == 1 ) printf("|  X  ");

        else printf("| %3d ", listaAssentos[i].numero);

        flgQuebraLinha++;
        if ( flgQuebraLinha == 10 ){
            printf("|\n");
            flgQuebraLinha = 0;
        }
    }
    printf("\n-----------------------------------------------------------------------------\n");
}

void MENU(){
    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("|               ✈️  CPL AIRLINES  ✈️                  |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("|                 __|__                             |\n");
    printf("|        --o--o--(_)--o--o--                        |\n");
    printf("|                                                   |\n");
    printf("| 1 - Cadastrar passageiros                         |\n");
    printf("| 2 - Visualizar voos disponiveis                   |\n");
    printf("| 3 - Cancelar viagem                               |\n");
    printf("| 4 - Visualizar passagens                          |\n");
    printf("| 0 - Sair                                          |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("Escolha uma opcao: ");
}