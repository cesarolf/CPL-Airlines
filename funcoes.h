#ifndef FUNCOES_H
#define FUNCOES_H

#define TOTAL_ASSENTOS 180
#define TOTAL_VOOS 10

typedef struct Passagem {
    char nomePassageiro[50]; // Acho que a passagem n precisa do nome do passageiro não, vários
    double preco;            // passageiros podem ter uma passagem igual
    int idVoo;
    int numAssento;
    struct Passagem *prox;
} Passagem;

typedef struct Assento { // será uma lista estática
    int numero;
    int ocupado; // 0 para livre e 1 para ocupado
} Assento;

typedef struct Voo {
    int id;
    char destino[50];
    char origem[50];
    int qtdAssentosOcupados;
    Assento *listaAssentos;
} Voo;

typedef struct Passageiro {
    int id;
    char nome[50];
    int idade;
    char sexo;
    Passagem *passagens;
    struct Passageiro *prox;
} Passageiro;

void inicializarAssentos( Assento *listaAssentos, int qtdAssentosOcupados );

int reservarAssento( int numAssento, Voo *voo );

int liberarAssento( Voo *voo, int numAssento );

void mostrarAssentos( Assento *listaAssentos );

int qtdAssentosLivres( Voo *voo );

Voo *carregarVoos( char *Arquivo );

Voo *buscarVooPorId( Voo *listaVoos, int idVoo );

void exibirVoos( Voo *listaVoos );

Passageiro* cadastrarPassageiro( Passageiro *lista );

void MENU();

void MenuCadastro( Passageiro ** passageiros );

void menuCancelamento( Voo *voos, Passagem **passagens );

void menuVisualizacao( Voo *voos, Passagem *passagens );

Passagem* criarPassagem( Passageiro *passageiros, Voo *voo, int numAssento, Passagem **listaPassagens );

Passagem* cancelarPassagem( Passagem *lista, Voo *voo, int numAssento );

void listarPassagens(Passagem *lista);

#endif