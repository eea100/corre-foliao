#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

typedef enum {
    FRENTE,
    COSTAS,
    ESQUERDA,
    DIREITA
} Direcao;

typedef struct {
    int linha;
    int coluna;
    Direcao direcao;
    double ultimoPasso;
} Jogador;

void CarregarTexturasJogador(void);
void DescarregarTexturasJogador(void);
void IniciarJogador(Jogador *jogador);
void MoverJogador(Jogador *jogador, int fase);
Rectangle CorpoJogador(Jogador jogador);
void DesenharJogador(Jogador jogador);

#endif
