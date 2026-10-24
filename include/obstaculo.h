#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <stdbool.h>
#include "raylib.h"

typedef enum {
    CARRO,
    TRIO,
    BONECO
} TipoObstaculo;

typedef struct Obstaculo {
    TipoObstaculo tipo;
    Rectangle corpo;
    float velocidade;
    int cor;
    struct Obstaculo *proximo;
} Obstaculo;

void CarregarTexturasObstaculo(void);
void DescarregarTexturasObstaculo(void);
Obstaculo *CriarObstaculo(TipoObstaculo tipo, int linha, int coluna, float velocidade);
void AdicionarObstaculo(Obstaculo **lista, Obstaculo *novo);
void LiberarObstaculos(Obstaculo **lista);
void MoverObstaculos(Obstaculo *lista);
void DesenharObstaculos(Obstaculo *lista);
bool BateuEmObstaculo(Obstaculo *lista, Rectangle area);

#endif
