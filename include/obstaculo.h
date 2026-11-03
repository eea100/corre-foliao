#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <stdbool.h>
#include "raylib.h"

enum TipoObstaculo {
    CARRO,
    TRIO,
    BONECO
};

struct Node {
    enum TipoObstaculo tipo;
    Rectangle corpo;
    float velocidade;
    int cor;
    struct Node *next;
};

void CarregarTexturasObstaculo(void);
void DescarregarTexturasObstaculo(void);
struct Node *CriarNo(enum TipoObstaculo tipo, int linha, int coluna, float velocidade);
void InserirNo(struct Node **head, struct Node *novo);
void LiberarLista(struct Node **head);
void MoverObstaculos(struct Node *head);
void DesenharObstaculos(struct Node *head);
bool BateuEmObstaculo(struct Node *head, Rectangle area);

#endif
