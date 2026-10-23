#ifndef JOGO_H
#define JOGO_H

#include "config.h"
#include "jogador.h"

typedef struct {
    Jogador jogador;
    int fase;
} Jogo;

void IniciarJogo(Jogo *jogo);
void AtualizarJogo(Jogo *jogo);
void DesenharJogo(Jogo *jogo);

#endif
