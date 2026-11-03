#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

enum Direcao {
    FRENTE,
    COSTAS,
    ESQUERDA,
    DIREITA
};

struct Jogador {
    int linha;
    int coluna;
    enum Direcao direcao;
    double ultimoPasso;
};

void CarregarTexturasJogador(void);
void DescarregarTexturasJogador(void);
void IniciarJogador(struct Jogador *jogador);
void MoverJogador(struct Jogador *jogador, int fase);
Rectangle CorpoJogador(struct Jogador jogador);
void DesenharJogador(struct Jogador jogador);

#endif
