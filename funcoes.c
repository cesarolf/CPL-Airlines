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
    FILE *file = fopen("voos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo voos.txt\n");
        return NULL;
    }

    Voo *voos = (Voo*)malloc(TOTAL_VOOS * sizeof(Voo));
    if (voos == NULL) return NULL;

    for (int i = 0; i < TOTAL_VOOS; i++) {
        if (fscanf(file, "%d %s %s %lf", &voos[i].id, voos[i].destino, voos[i].origem, &voos[i].preco) != 4) {
            break;
        }
        
        // Inicializa qtd de assentos aleatoriamente
        int ocupados = rand() % 50;
        voos[i].qtdAssentosOcupados = ocupados;
        inicializarAssentos(voos[i].listaAssentos, ocupados);
    }

    fclose(file);
    return voos;
}

int qtdAssentosLivres( Voo *voo ) {
    int i, count = 0;

    for(i = 0; i<TOTAL_ASSENTOS; i++) {
        if(voo->listaAssentos[i].ocupado == 0) count++;
    }

    return count;
}

Voo *buscarVooPorId(Voo *listaVoos, int idVoo) {
    int inicio = 0;
    int fim = TOTAL_VOOS - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (listaVoos[meio].id == idVoo) {
            return &listaVoos[meio];
        } else if (listaVoos[meio].id < idVoo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
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

    printf("                      DISPOSICAO DE ASSENTOS DO AVIAO\n");
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

void removerPassagemPorAssento(Passageiro *listaPassageiros, int idVoo, int numAssento) {
    Passageiro *p = listaPassageiros;

    while (p != NULL) {
        Passagem *atual = p->passagens;
        Passagem *anterior = NULL;

        // Percorre as passagens deste passageiro
        while (atual != NULL) {
            // Se encontrou a passagem correspondente ao voo e assento cancelado
            if (atual->idVoo == idVoo && atual->numAssento == numAssento) {
                
                if (anterior == NULL) {
                    p->passagens = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                
                free(atual);
                return;
            }
            anterior = atual;
            atual = atual->prox;
        }
        p = p->prox;
    }
}

void menuCancelamento(Voo *voos, Passageiro *listaPassageiros){
    int idVoo, numAssento;

    printf("=====================================================\n");
    printf("|                                                   |\n");
    printf("|              CANCELAR ASSENTO                     |\n");
    printf("|                                                   |\n");
    printf("=====================================================\n");
    
    printf("ID do voo: ");
    scanf("%d", &idVoo);

    Voo *voo = buscarVooPorId(voos, idVoo);
    if (voo == NULL) return;

    printf("Numero do assento: ");
    scanf("%d", &numAssento);

    int resultado = liberarAssento(voo, numAssento);

    if (resultado == 1) {
        printf("Assento liberado com sucesso!\n");
        removerPassagemPorAssento(listaPassageiros, idVoo, numAssento);
    } 
    else if (resultado == 0) {
        printf("O assento %d ja estava vazio.\n", numAssento);
    } 
    else {
        printf("Assento invalido.\n");
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

void menuCompra(Voo *voos, Passageiro *listaPassageiros, Passagem **listaPassagens) {
    int idVoo, numAssento, op;
    
    printf("ID do voo: ");
    scanf("%d", &idVoo);

    Voo *voo = buscarVooPorId(voos, idVoo);
    if (voo == NULL) return;

    printf("O valor da passagem para este voo é: R$ %.2lf\n", voo->preco);
    printf("Deseja confirmar a compra? (1-Sim / 0-Não): ");
    scanf("%d", &op);

    if (op != 1) {
        printf("Compra cancelada.\n");
        return;
    }

    printf("\nQual o número do assento (1 a %d)?\n", TOTAL_ASSENTOS);
    scanf("%d", &numAssento);

    int ocup = reservarAssento(numAssento, voo);
    while(ocup <= 0) {
        printf("Assento ocupado ou inválido! Escolha outro: ");
        scanf("%d", &numAssento);
        ocup = reservarAssento(numAssento, voo);
    }

    criarPassagem(listaPassageiros, voo, numAssento);
}

void menuVisualizacao(Voo *voos, Passagem *passagens, Passageiro *listaPassageiros){
    int op;
    int idPassageiro;

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

Passagem* criarPassagem(Passageiro *passageiros, Voo *voo, int numAssento) {
    int id;
    Passageiro *p = passageiros;

    if (p == NULL) {
        printf("Nenhum passageiro cadastrado no sistema.\n");
        liberarAssento(voo, numAssento); 
        return NULL;
    }

    printf("Informe o ID do passageiro que irá viajar: ");
    scanf("%d", &id);

    while (p != NULL && p->id != id) {
        p = p->prox;
    }

    if (p == NULL) {
        printf("Passageiro não encontrado!\n");
        liberarAssento(voo, numAssento);
        return NULL;
    }

    Passagem *nova = malloc(sizeof(Passagem));
    if (nova == NULL) return NULL;

    strcpy(nova->nomePassageiro, p->nome);
    nova->idVoo = voo->id;
    nova->numAssento = numAssento;
    nova->preco = voo->preco;
    nova->prox = p->passagens;
    p->passagens = nova;

    printf("Passagem emitida com sucesso para %s!\n", p->nome);
    return nova;
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
