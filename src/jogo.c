#include "jogo.h"
#include "fase.h"

void IniciarJogo(Jogo *jogo)
{
    jogo->fase = 0;
    IniciarJogador(&jogo->jogador);
}

void AtualizarJogo(Jogo *jogo)
{
    MoverJogador(&jogo->jogador, jogo->fase);
}

static void DesenharHUD(Jogo *jogo)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_HUD, (Color){42, 18, 64, 255});
    DrawText(TextFormat("Fase %d/%d", jogo->fase + 1, TOTAL_FASES), 12, 10, 20, GOLD);
}

void DesenharJogo(Jogo *jogo)
{
    Camera2D camera = {.offset = {0, ALTURA_HUD}, .zoom = 1};

    BeginMode2D(camera);
    DesenharFase(jogo->fase);
    DesenharJogador(jogo->jogador);
    EndMode2D();

    DesenharHUD(jogo);
}
