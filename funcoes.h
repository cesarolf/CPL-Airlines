#ifndef FUNCOES_H
#define FUNCOES_H

#define TOTAL_ASSENTOS 180
#define TOTAL_VOOS 10

typedef struct Passagem {
    char nomePassageiro[50]; 
    double preco;            
    int idVoo;
    int numAssento;
    struct Passagem *prox;
} Passagem;

typedef struct Assento { 
    int numero;
    int ocupado; 
} Assento;

typedef struct Voo {
    int id;
    char destino[50];
    char origem[50];
    int qtdAssentosOcupados;
    double preco;
    Assento listaAssentos[TOTAL_ASSENTOS];
} Voo;

typedef struct Passageiro {
    int id;
    char nome[50];
    int idade;
    Passagem *passagens;
    struct Passageiro *prox;
} Passageiro;

void inicializarAssentos( Assento *listaAssentos, int qtdAssentosOcupados );

int reservarAssento( int numAssento, Voo *voo );

int liberarAssento( Voo *voo, int numAssento );

void mostrarAssentos( Assento *listaAssentos );

int qtdAssentosLivres( Voo *voo );

Voo *carregarVoos();

Voo *buscarVooPorId( Voo *listaVoos, int idVoo );

void exibirVoos( Voo *listaVoos );

Passageiro* cadastrarPassageiro( Passageiro *lista );

Passageiro *buscarPassageiroPorId(Passageiro *listaPassageiros, int idPassageiro);

void MENU();

void menuVoos(Voo *voos);

void menuCompra(Voo *voos, Passageiro *listaPassageiros, Passagem **listaPassagens);

void menuCadastro( Passageiro ** passageiros );

void menuCancelamento( Voo *voos, Passageiro *listaPassageiros );

void menuVisualizacao(Voo *voos, Passagem *passagens, Passageiro *listaPassageiros);

Passagem* criarPassagem( Passageiro *passageiros, Voo *voo, int numAssento );

void removerPassagemPorAssento(Passageiro *listaPassageiros, int idVoo, int numAssento);

void listarPassagens(Passagem *lista);

#endif
