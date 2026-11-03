#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "config.h"
#include "jogador.h"
#include "obstaculo.h"

struct Jogo {
    struct Jogador jogador;
    struct Node *head;
    int fase;
    int vidas;
    int pontos;
    int melhorLinha;
    int recordes[TOTAL_RECORDES];
    bool fim;
    bool venceu;
};

void IniciarJogo(struct Jogo *jogo);
void AtualizarJogo(struct Jogo *jogo);
void DesenharJogo(struct Jogo *jogo);
void FinalizarJogo(struct Jogo *jogo);

#endif
