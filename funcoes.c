#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

void inicializarAssentos( Assento *listaAssentos, int qtdAssentosOcupados ) {
    int i, ocupado = 0;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        listaAssentos[i].numero = i+1;
        listaAssentos[i].ocupado = 0;
    }
    while(ocupado<qtdAssentosOcupados) {
        i = rand()%TOTAL_ASSENTOS;
        if(listaAssentos[i].ocupado == 0) {
            listaAssentos[i].ocupado = 1;
            ocupado++;
        }
    }
}

int reservarAssento( int numAssento, Voo *voo ) {

    if ( numAssento > TOTAL_ASSENTOS || numAssento < 1 ) return 0;   // Não existe assento com esse número
    else if ( voo->listaAssentos[numAssento-1].ocupado == 1 ) return -1;  // Falha ao reservar assento, assento ocupado
    else  {
        voo->listaAssentos[numAssento-1].ocupado = 1;
        return 1;// Assento reservado com sucesso
    }

    return 0; // Não existe assento com esse número
}

int liberarAssento( Voo *voo, int numAssento ) {
    
    if ( numAssento > TOTAL_ASSENTOS || numAssento < 1 ) return -1; // Não existe
    if ( voo->listaAssentos[numAssento-1].ocupado == 0 ) return 0;
    
    voo->listaAssentos[numAssento-1].ocupado = 0; // Liberado com sucesso
    return 1;
}

Voo *carregarVoos() {
    char origem[TOTAL_VOOS][50] = {
        "Goiania", "Goiania", "Brasilia", "Goiania", "Brasilia", 
        "Brasilia","Brasilia", "Goiania", "Goiania", "Brasilia"
    };
    char destino[TOTAL_VOOS][50] = {
        "Sao Paulo", "Rio De Janeiro", "Salvador", "Fortaleza", "Curitiba",
        "Recife", "Belo Horizonte", "Porto Alegre", "Manaus", "Belem"
    };
    int AssentosOcupados[TOTAL_VOOS] = {36, 96, 28, 73, 32, 44, 21, 53, 20, 19};
    Voo *voos = (Voo*)malloc(TOTAL_VOOS*sizeof(Voo));
    if (voos == NULL) {
        printf("Erro de memoria\n");
        return NULL;
    }
    int i;

    for(i=0; i<TOTAL_VOOS; i++) {
        voos[i].id = i+1;
        strcpy(voos[i].origem, origem[i]);
        strcpy(voos[i].destino, destino[i]);
        voos[i].qtdAssentosOcupados = AssentosOcupados[i];
        inicializarAssentos(voos[i].listaAssentos, AssentosOcupados[i]);
    }
                     
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
    menuVoos(listaVoos);

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

Passageiro *buscarPassageiroPorId(Passageiro *listaPassageiros, int idPassageiro) {

    while(listaPassageiros != NULL) {
        if(listaPassageiros->id == idPassageiro) {
            return listaPassageiros;
        }
        listaPassageiros = listaPassageiros->prox;
    }

    return NULL;
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
    printf("| 1 - Cadastro                                      |\n");
    printf("| 2 - Cancelamento                                  |\n");
    printf("| 3 - Menu de visualizacao                          |\n");
    printf("| 4 - Reservar assento                              |\n");
    printf("| 0 - Sair                                          |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("Escolha uma opcao: ");
}

void menuCadastro (Passageiro **passageiros){
    *passageiros = cadastrarPassageiro(*passageiros);
}

void menuCancelamento(Voo *voos, Passagem **passagens){
    int op;
    int idVoo, numAssento;

    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("|                   CANCELAMENTO                    |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("| 1 - Cancelar assento                              |\n");
    printf("| 2 - Cancelar viagem                               |\n");
    printf("| 0 - Voltar                                        |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("Opcao: ");
    scanf(" %d", &op);

    switch(op) {
        case 1:
            printf("ID do voo: ");
            scanf("%d", &idVoo);

            Voo *voo = buscarVooPorId(voos, idVoo);
            if (voo == NULL) return;

            printf("Numero do assento: ");
            scanf("%d", &numAssento);

            if (liberarAssento(voo, numAssento))
                printf("Assento liberado com sucesso!\n");
            else
                printf("Erro ao liberar assento.\n");
            break;

        case 2:
            printf("ID do voo: ");
            scanf("%d", &idVoo);

            Voo *v = buscarVooPorId(voos, idVoo);
            if (v == NULL) return;

            printf("Numero do assento: ");
            scanf("%d", &numAssento);

            *passagens = cancelarPassagem(*passagens, v, numAssento);
            printf("Viagem cancelada.\n");
            break;

        case 0:
            return;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}

void menuVoos(Voo *voos){
    int op;
    int idVoo;

    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("| Deseja visualizar os assentos de um voo?          |\n");
    printf("| (1 - Sim | 0 - Nao)                               |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("Opcao: ");
    scanf(" %d", &op);

    switch(op) {
        case 1:
            printf("ID do voo: ");
            scanf("%d", &idVoo);

            Voo *voo = buscarVooPorId(voos, idVoo);
            if (voo == NULL) return;

            mostrarAssentos(voo->listaAssentos);
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}

void menuCompra(Voo *voos, Passageiro *listaPassageiros, Passagem **listaPassagens){
    
    int idVoo, ocup;
    int numAssento, idPassageiro;
    
    printf("ID do voo: ");
    scanf("%d", &idVoo);
    printf("\nQual o número do assento que deseja reservar?\n");
    scanf("%d", &numAssento);

    Voo *voo = buscarVooPorId(voos, idVoo);
    if (voo == NULL) return;

    ocup = reservarAssento(numAssento, voo);
    while(ocup == 0 || ocup == -1) {
        printf("Assento ocupado ou invalido!\n");
        printf("Escolha um novo assento: \n");
        scanf("%d", &numAssento);
        ocup = reservarAssento(numAssento, voo);
    }
    criarPassagem(listaPassageiros, voo, numAssento);
}


void menuVisualizacao(Voo *voos, Passagem *passagens, Passageiro *listaPassageiros){
    int op;

    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("|                   VISUALIZACAO                    |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("| 1 - Voos                                          |\n");
    printf("| 2 - Suas passagens                                |\n");
    printf("| 0 - Voltar                                        |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    printf("Opcao: ");
    scanf(" %d", &op);

    switch(op) {
        case 1:
            exibirVoos(voos);
            break;
        case 2:
            int idPassageiro;
            printf("\nInforme o seu id: ");
            scanf("%d", &idPassageiro);
            Passageiro *passageiro = buscarPassageiroPorId(listaPassageiros, idPassageiro);
            listarPassagens(passageiro->passagens);
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}

Passagem* criarPassagem( Passageiro *passageiros, Voo *voo, int numAssento ){
    int id;
    Passageiro *p = passageiros;

    if (p == NULL) {
        printf("Nenhum passageiro cadastrado.\n");
        return NULL;
    }

    printf("ID do passageiro: ");
    scanf("%d", &id);

    while (p != NULL && p->id != id) {
        p = p->prox;
    }

    if (p == NULL) {
        printf("Passageiro nao encontrado.\n");
        return NULL;
    }

    Passagem *nova = malloc(sizeof(Passagem));
    if (nova == NULL) return NULL;

    strcpy(nova->nomePassageiro, p->nome);
    nova->idVoo = voo->id;
    nova->numAssento = numAssento;
    double preco;
    printf("Qual o preço da passagem: ");
    scanf("%lf", &preco);
    nova->preco = preco;

    nova->prox = NULL;

    nova->prox = p->passagens;
    p->passagens = nova;

    printf("Passagem criada com sucesso!\n");
    return nova;
}

Passagem* cancelarPassagem(Passagem *lista, Voo *voo, int numAssento) {
    Passagem *atual = lista;
    Passagem *anterior = NULL;

    while (atual != NULL) {
        if (atual->idVoo == voo->id && atual->numAssento == numAssento) {

            liberarAssento(voo, numAssento);

            if (anterior == NULL) {
                lista = atual->prox; // remove primeiro
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Passagem cancelada com sucesso.\n");
            return lista;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Passagem nao encontrada.\n");
    return lista;
}

void listarPassagens(Passagem *lista) {
    if (lista == NULL) {
        printf("Nenhuma passagem cadastrada.\n");
        return;
    }

    printf("=====================================\n");
    printf("        PASSAGENS CADASTRADAS      \n");
    printf("=====================================\n");

    while (lista != NULL) {
        printf("Voo ID: %d\n", lista->idVoo);
        printf("Assento: %d\n", lista->numAssento);
        printf("Preco: R$ %.2lf\n", lista->preco);
        printf("Passageiro: %s\n", lista->nomePassageiro);
        printf("-------------------------------------\n");
        lista = lista->prox;
    }
}