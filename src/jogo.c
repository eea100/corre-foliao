#include "jogo.h"
#include "fase.h"

static Texture2D coracao;

static float Velocidade(TipoObstaculo tipo, int fase, int linha)
{
    float base = tipo == CARRO ? 110 : tipo == TRIO ? 70 : 50;
    float velocidade = base + 30 * fase;
    return linha % 2 == 0 ? velocidade : -velocidade;
}

static void CarregarFase(Jogo *jogo)
{
    LiberarObstaculos(&jogo->obstaculos);

    for (int linha = 0; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            char c = CaractereDaFase(jogo->fase, linha, coluna);
            TipoObstaculo tipo;

            if (c == 'c') tipo = CARRO;
            else if (c == 't') tipo = TRIO;
            else if (c == 'g') tipo = BONECO;
            else continue;

            AdicionarObstaculo(&jogo->obstaculos, CriarObstaculo(tipo, linha, coluna, Velocidade(tipo, jogo->fase, linha)));
        }
    }

    IniciarJogador(&jogo->jogador);
}

void IniciarJogo(Jogo *jogo)
{
    if (coracao.id == 0) {
        coracao = LoadTexture("assets/cenario/coracao.png");
    }

    jogo->fase = 0;
    jogo->vidas = VIDAS_INICIAIS;
    jogo->fim = false;
    CarregarFase(jogo);
}

void FinalizarJogo(Jogo *jogo)
{
    LiberarObstaculos(&jogo->obstaculos);
    UnloadTexture(coracao);
}

void AtualizarJogo(Jogo *jogo)
{
    Jogador *jogador = &jogo->jogador;

    if (jogo->fim) {
        return;
    }

    MoverJogador(jogador, jogo->fase);
    MoverObstaculos(jogo->obstaculos);

    if (BateuEmObstaculo(jogo->obstaculos, CorpoJogador(*jogador))) {
        jogo->vidas--;

        if (jogo->vidas == 0) {
            jogo->fim = true;
        } else {
            IniciarJogador(jogador);
        }
    }
}

static void TextoCentro(const char *texto, int y, int tamanho, Color cor)
{
    DrawText(texto, (LARGURA_TELA - MeasureText(texto, tamanho)) / 2, y, tamanho, cor);
}

static void DesenharHUD(Jogo *jogo)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_HUD, (Color){42, 18, 64, 255});
    DrawText(TextFormat("Fase %d/%d", jogo->fase + 1, TOTAL_FASES), 12, 10, 20, GOLD);

    for (int i = 0; i < jogo->vidas; i++) {
        DrawTexturePro(coracao, (Rectangle){0, 0, coracao.width, coracao.height},
                       (Rectangle){LARGURA_TELA - 40 - i * 34, 7, 27, 24}, (Vector2){0, 0}, 0, WHITE);
    }
}

static void DesenharFim(void)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.6f));
    DrawRectangle(220, 240, 360, 160, RAYWHITE);
    TextoCentro("FIM DE JOGO", 270, 32, RED);
    TextoCentro("ENTER para voltar", 340, 20, DARKGRAY);
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

    if (jogo->fim) {
        DesenharFim();
    }
}
