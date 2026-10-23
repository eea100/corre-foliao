#include "jogo.h"
#include "fase.h"

static float Velocidade(int fase, int linha)
{
    float velocidade = 110 + 30 * fase;
    return linha % 2 == 0 ? velocidade : -velocidade;
}

static void CarregarFase(Jogo *jogo)
{
    LiberarObstaculos(&jogo->obstaculos);

    for (int linha = 0; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            if (CaractereDaFase(jogo->fase, linha, coluna) == 'c') {
                AdicionarObstaculo(&jogo->obstaculos, CriarObstaculo(CARRO, linha, coluna, Velocidade(jogo->fase, linha)));
            }
        }
    }

    IniciarJogador(&jogo->jogador);
}

void IniciarJogo(Jogo *jogo)
{
    jogo->fase = 0;
    CarregarFase(jogo);
}

void FinalizarJogo(Jogo *jogo)
{
    LiberarObstaculos(&jogo->obstaculos);
}

void AtualizarJogo(Jogo *jogo)
{
    MoverJogador(&jogo->jogador, jogo->fase);
    MoverObstaculos(jogo->obstaculos);
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
    DesenharObstaculos(jogo->obstaculos);
    DesenharJogador(jogo->jogador);
    EndMode2D();

    DesenharHUD(jogo);
}
