#include "jogo.h"
#include "fase.h"
#include "recordes.h"

static Texture2D coracao;

static float Velocidade(enum TipoObstaculo tipo, int fase, int linha)
{
    float base = tipo == CARRO ? 110 : tipo == TRIO ? 70 : 50;
    float velocidade = base + 30 * fase;
    return linha % 2 == 0 ? velocidade : -velocidade;
}

static void CarregarFase(struct Jogo *jogo)
{
    LiberarLista(&jogo->head);

    for (int linha = 0; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            char c = CaractereDaFase(jogo->fase, linha, coluna);
            enum TipoObstaculo tipo;

            if (c == 'c') tipo = CARRO;
            else if (c == 't') tipo = TRIO;
            else if (c == 'g') tipo = BONECO;
            else continue;

            InserirNo(&jogo->head, CriarNo(tipo, linha, coluna, Velocidade(tipo, jogo->fase, linha)));
        }
    }

    IniciarJogador(&jogo->jogador);
    jogo->melhorLinha = LINHAS - 1;
}

void IniciarJogo(struct Jogo *jogo)
{
    if (coracao.id == 0) {
        coracao = LoadTexture("assets/cenario/coracao.png");
    }

    CarregarRecordes(jogo->recordes);
    jogo->fase = 0;
    jogo->vidas = VIDAS_INICIAIS;
    jogo->pontos = 0;
    jogo->fim = false;
    jogo->venceu = false;
    CarregarFase(jogo);
}

void FinalizarJogo(struct Jogo *jogo)
{
    LiberarLista(&jogo->head);
    UnloadTexture(coracao);
}

static void TerminarJogo(struct Jogo *jogo, bool venceu)
{
    jogo->fim = true;
    jogo->venceu = venceu;

    if (InserirRecorde(jogo->recordes, jogo->pontos)) {
        SalvarRecordes(jogo->recordes);
    }
}

void AtualizarJogo(struct Jogo *jogo)
{
    struct Jogador *jogador = &jogo->jogador;

    if (jogo->fim) {
        return;
    }

    MoverJogador(jogador, jogo->fase);
    MoverObstaculos(jogo->head);

    if (jogador->linha < jogo->melhorLinha) {
        jogo->pontos += 10;
        jogo->melhorLinha = jogador->linha;
    }

    if (BateuEmObstaculo(jogo->head, CorpoJogador(*jogador))) {
        jogo->vidas--;

        if (jogo->vidas == 0) {
            TerminarJogo(jogo, false);
        } else {
            IniciarJogador(jogador);
        }
    } else if (jogador->linha == 0) {
        jogo->pontos += 100;
        jogo->fase++;

        if (jogo->fase == TOTAL_FASES) {
            jogo->fase = TOTAL_FASES - 1;
            TerminarJogo(jogo, true);
        } else {
            CarregarFase(jogo);
        }
    }
}

static void TextoCentro(const char *texto, int y, int tamanho, Color cor)
{
    DrawText(texto, (LARGURA_TELA - MeasureText(texto, tamanho)) / 2, y, tamanho, cor);
}

static void DesenharHUD(struct Jogo *jogo)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_HUD, (Color){42, 18, 64, 255});
    DrawText(TextFormat("Fase %d/%d", jogo->fase + 1, TOTAL_FASES), 12, 10, 20, GOLD);
    DrawText(TextFormat("Pontos: %d", jogo->pontos), 160, 10, 20, RAYWHITE);
    DrawText(TextFormat("Recorde: %d", jogo->recordes[0]), 340, 10, 20, RAYWHITE);

    for (int i = 0; i < jogo->vidas; i++) {
        DrawTexturePro(coracao, (Rectangle){0, 0, coracao.width, coracao.height},
                       (Rectangle){LARGURA_TELA - 40 - i * 34, 7, 27, 24}, (Vector2){0, 0}, 0, WHITE);
    }
}

static void DesenharFim(struct Jogo *jogo)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.6f));
    DrawRectangle(220, 140, 360, 360, RAYWHITE);
    TextoCentro(jogo->venceu ? "CHEGOU NO BLOCO!" : "FIM DE JOGO", 160, 32, jogo->venceu ? GOLD : RED);
    TextoCentro(TextFormat("Pontos: %d", jogo->pontos), 210, 24, DARKBLUE);
    TextoCentro("TOP 5", 255, 22, DARKGRAY);

    for (int i = 0; i < TOTAL_RECORDES; i++) {
        TextoCentro(TextFormat("%d. %d", i + 1, jogo->recordes[i]), 285 + i * 28, 22, DARKBLUE);
    }

    TextoCentro("ENTER para voltar", 450, 20, DARKGRAY);
}

void DesenharJogo(struct Jogo *jogo)
{
    Camera2D camera = {.offset = {0, ALTURA_HUD}, .zoom = 1};

    BeginMode2D(camera);
    DesenharFase(jogo->fase);
    DesenharObstaculos(jogo->head);
    DesenharJogador(jogo->jogador);
    EndMode2D();

    DesenharHUD(jogo);

    if (jogo->fim) {
        DesenharFim(jogo);
    }
}
