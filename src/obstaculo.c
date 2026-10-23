#include <stdlib.h>
#include "config.h"
#include "obstaculo.h"

static const float larguras[] = {[CARRO] = 72};

static Texture2D carros[4][2];

void CarregarTexturasObstaculo(void)
{
    for (int i = 0; i < 4; i++) {
        carros[i][0] = LoadTexture(TextFormat("assets/veiculos/carro_%d_esquerda.png", i));
        carros[i][1] = LoadTexture(TextFormat("assets/veiculos/carro_%d_direita.png", i));
    }
}

void DescarregarTexturasObstaculo(void)
{
    for (int i = 0; i < 4; i++) {
        for (int lado = 0; lado < 2; lado++) {
            UnloadTexture(carros[i][lado]);
        }
    }
}

Obstaculo *CriarObstaculo(TipoObstaculo tipo, int linha, int coluna, float velocidade)
{
    Obstaculo *novo = malloc(sizeof(Obstaculo));

    if (novo == NULL) {
        return NULL;
    }

    novo->tipo = tipo;
    novo->corpo = (Rectangle){coluna * TAM_BLOCO, linha * TAM_BLOCO + 6, larguras[tipo], TAM_BLOCO - 12};
    novo->velocidade = velocidade;
    novo->cor = (linha + coluna) % 4;
    novo->proximo = NULL;
    return novo;
}

void AdicionarObstaculo(Obstaculo **lista, Obstaculo *novo)
{
    if (novo != NULL) {
        novo->proximo = *lista;
        *lista = novo;
    }
}

void LiberarObstaculos(Obstaculo **lista)
{
    while (*lista != NULL) {
        Obstaculo *proximo = (*lista)->proximo;
        free(*lista);
        *lista = proximo;
    }
}

void MoverObstaculos(Obstaculo *lista)
{
    for (Obstaculo *o = lista; o != NULL; o = o->proximo) {
        o->corpo.x += o->velocidade * GetFrameTime();

        if (o->corpo.x > LARGURA_TELA) {
            o->corpo.x = -o->corpo.width;
        } else if (o->corpo.x < -o->corpo.width) {
            o->corpo.x = LARGURA_TELA;
        }
    }
}

static void DesenharImagem(Texture2D textura, float x, float y, float largura, float altura)
{
    Rectangle origem = {0, 0, textura.width, textura.height};
    DrawTexturePro(textura, origem, (Rectangle){x, y, largura, altura}, (Vector2){0, 0}, 0, WHITE);
}

void DesenharObstaculos(Obstaculo *lista)
{
    for (Obstaculo *o = lista; o != NULL; o = o->proximo) {
        int lado = o->velocidade > 0 ? 1 : 0;
        Rectangle c = o->corpo;

        DesenharImagem(carros[o->cor][lado], c.x, c.y - 6, c.width, c.height + 8);
    }
}
