#include <stdlib.h>
#include "config.h"
#include "obstaculo.h"

static const char *coresTrio[] = {"amarelo", "vermelho", "verde", "azul"};
static const float larguras[] = {[CARRO] = 72, [TRIO] = 120, [BONECO] = 30};

static Texture2D carros[4][2];
static Texture2D trios[4][2];
static Texture2D bonecos[2][4];

void CarregarTexturasObstaculo(void)
{
    for (int i = 0; i < 4; i++) {
        carros[i][0] = LoadTexture(TextFormat("assets/veiculos/carro_%d_esquerda.png", i));
        carros[i][1] = LoadTexture(TextFormat("assets/veiculos/carro_%d_direita.png", i));
        trios[i][0] = LoadTexture(TextFormat("assets/veiculos/trio_%s_esquerda.png", coresTrio[i]));
        trios[i][1] = LoadTexture(TextFormat("assets/veiculos/trio_%s_direita.png", coresTrio[i]));
        bonecos[0][i] = LoadTexture(TextFormat("assets/boneco/esquerda_%d.png", i));
        bonecos[1][i] = LoadTexture(TextFormat("assets/boneco/direita_%d.png", i));
    }
}

void DescarregarTexturasObstaculo(void)
{
    for (int i = 0; i < 4; i++) {
        for (int lado = 0; lado < 2; lado++) {
            UnloadTexture(carros[i][lado]);
            UnloadTexture(trios[i][lado]);
            UnloadTexture(bonecos[lado][i]);
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
    int quadro = (int)(GetTime() * 8) % 4;

    for (Obstaculo *o = lista; o != NULL; o = o->proximo) {
        int lado = o->velocidade > 0 ? 1 : 0;
        Rectangle c = o->corpo;

        if (o->tipo == CARRO) {
            DesenharImagem(carros[o->cor][lado], c.x, c.y - 6, c.width, c.height + 8);
        } else if (o->tipo == TRIO) {
            DesenharImagem(trios[o->cor][lado], c.x, c.y - 10, c.width, c.height + 12);
        } else {
            DesenharImagem(bonecos[lado][quadro], c.x - 8, c.y - 34, 46, 62);
        }
    }
}

bool BateuEmObstaculo(Obstaculo *lista, Rectangle area)
{
    for (Obstaculo *o = lista; o != NULL; o = o->proximo) {
        if (CheckCollisionRecs(o->corpo, area)) {
            return true;
        }
    }

    return false;
}
