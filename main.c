#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    
    Voo *voosDisponiveis;
    voosDisponiveis = carregarVoos("voos.txt");

    Passageiro *passageiros = NULL;
    Passagem *passagens = NULL;
    
    int op;
    do {

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
                printf("0 - Sair\n");
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
        }
    } while(op != 0);
    
    return 0;
}
