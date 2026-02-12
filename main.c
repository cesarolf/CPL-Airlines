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

    do {
        MENU();
        scanf("%d", &op);

        switch(op) {
            case 1:
                menuCadastro(&passageiros);
                break;
            case 2:
                menuCancelamento(voosDisponiveis, passageiros); 
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
