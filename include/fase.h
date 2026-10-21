#ifndef FASE_H
#define FASE_H

#include <stdbool.h>

void CarregarTexturasFase(void);
void DescarregarTexturasFase(void);
char CaractereDaFase(int fase, int linha, int coluna);
bool LinhaEhRua(int fase, int linha);
bool PosicaoBloqueada(int fase, int linha, int coluna);
void DesenharFase(int fase);

#endif
