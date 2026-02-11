#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    
    srand(time(NULL));
    printf("Programa iniciado\n");
    Voo *voosDisponiveis;
    voosDisponiveis = carregarVoos();


    Passageiro *passageiros = NULL;
    Passagem *passagens = NULL;
    
    int op;
    /*
    do {

        MENU();
        scanf("%d", &op);

        switch(op) {
            case 1:
                passageiros = cadastrarPassageiro(passageiros);
                printf("\nPassageiro cadastrado com sucesso!\n");                
                break;
            case 2:
                int op2;
                exibirVoos(voosDisponiveis);
                
                printf("1 - Comprar passagem\n");
                printf("0 - Voltar\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &op2);
                switch(op2) {
                    case 1:
                        Voo *voo;
                        int id;
                        int resultado, numAssento;
                        printf("Digite o id do voo: ");
                        scanf("%d", &id);
                        printf("\nInforme o numero do assento que deseja reservar: ");
                        scanf("%d", &numAssento);
                        voo = buscarVooPorId(voosDisponiveis, id);
                        if (voo == NULL) {
                            printf("Voo invalido!\n");         // Correção do segmentation fault
                            break;
                        }
                        resultado = reservarAssento(numAssento, voo);
                        if(resultado == 1) printf("\nAssento reservado com sucesso!");
                        else printf("\nO assento informado esta ocupado!");
                        // função criar passagem
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 3:
                //função cancelar passagem e dentro dela a de liberar assento
                break;
            case 4:
                break;
            default:
                printf("Opção inválida, por favor selecione outra.\n");
                break;
        }
    } while(op != 0);
    */

    // Rascunho novo menu:
    do {

        MENU();
        scanf("%d", &op);

        switch(op) {
            case 1:
                menuCadastro(&passageiros);
                break;
            case 2:
                menuCancelamento(voosDisponiveis, &passagens);
                break;
            case 3:
                menuVisualizacao(voosDisponiveis, passagens, passageiros);
                break;
            case 4:
                menuCompra(voosDisponiveis, passageiros, &passagens);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida, por favor selecione outra.\n");
                break;
        }
    } while(op != 0);

    return 0;
}