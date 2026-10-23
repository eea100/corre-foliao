#ifndef JOGO_H
#define JOGO_H

#include "config.h"
#include "jogador.h"
#include "obstaculo.h"

typedef struct {
    Jogador jogador;
    Obstaculo *obstaculos;
    int fase;
} Jogo;

void IniciarJogo(Jogo *jogo);
void AtualizarJogo(Jogo *jogo);
void DesenharJogo(Jogo *jogo);
void FinalizarJogo(Jogo *jogo);

#endif
