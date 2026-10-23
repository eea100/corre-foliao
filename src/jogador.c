#include "config.h"
#include "jogador.h"
#include "fase.h"

static const char *nomes[] = {"frente", "costas", "esquerda", "direita"};
static Texture2D sprites[4][2];

void CarregarTexturasJogador(void)
{
    for (int d = 0; d < 4; d++) {
        for (int q = 0; q < 2; q++) {
            sprites[d][q] = LoadTexture(TextFormat("assets/foliao/%s_%d.png", nomes[d], q));
        }
    }
}

void DescarregarTexturasJogador(void)
{
    for (int d = 0; d < 4; d++) {
        for (int q = 0; q < 2; q++) {
            UnloadTexture(sprites[d][q]);
        }
    }
}

void IniciarJogador(Jogador *jogador)
{
    jogador->linha = LINHAS - 1;
    jogador->coluna = COLUNAS / 2;
    jogador->direcao = COSTAS;
    jogador->ultimoPasso = 0;
}

void MoverJogador(Jogador *jogador, int fase)
{
    int linha = jogador->linha;
    int coluna = jogador->coluna;

    if (IsKeyPressed(KEY_UP)) {
        linha--;
        jogador->direcao = COSTAS;
    } else if (IsKeyPressed(KEY_DOWN)) {
        linha++;
        jogador->direcao = FRENTE;
    } else if (IsKeyPressed(KEY_LEFT)) {
        coluna--;
        jogador->direcao = ESQUERDA;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        coluna++;
        jogador->direcao = DIREITA;
    } else {
        return;
    }

    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS || PosicaoBloqueada(fase, linha, coluna)) {
        return;
    }

    jogador->linha = linha;
    jogador->coluna = coluna;
    jogador->ultimoPasso = GetTime();
}

Rectangle CorpoJogador(Jogador jogador)
{
    return (Rectangle){jogador.coluna * TAM_BLOCO + 8, jogador.linha * TAM_BLOCO + 8, TAM_BLOCO - 16, TAM_BLOCO - 16};
}

void DesenharJogador(Jogador jogador)
{
    int quadro = GetTime() - jogador.ultimoPasso < 0.15 ? 1 : 0;
    Texture2D sprite = sprites[jogador.direcao][quadro];
    Rectangle origem = {0, 0, sprite.width, sprite.height};
    Rectangle destino = {jogador.coluna * TAM_BLOCO + 4, jogador.linha * TAM_BLOCO - 12, 33, 48};

    DrawTexturePro(sprite, origem, destino, (Vector2){0, 0}, 0, WHITE);
}
