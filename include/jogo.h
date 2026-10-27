#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "config.h"
#include "jogador.h"
#include "obstaculo.h"

typedef struct {
    Jogador jogador;
    Obstaculo *obstaculos;
    int fase;
    int vidas;
    int pontos;
    int melhorLinha;
    int recordes[TOTAL_RECORDES];
    bool fim;
    bool venceu;
} Jogo;

void IniciarJogo(Jogo *jogo);
void AtualizarJogo(Jogo *jogo);
void DesenharJogo(Jogo *jogo);
void FinalizarJogo(Jogo *jogo);

#endif
