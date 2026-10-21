#include "raylib.h"
#include "config.h"
#include "fase.h"

static const char fases[TOTAL_FASES][LINHAS][COLUNAS + 1] = {
    {
        "....................",
        ".C......E......C....",
        "--c--------c--------",
        "--------c--------c--",
        "....P.........P.....",
        "......g.............",
        "-c--------c---------",
        ".E.....C......E.....",
        "-----c--------c-----",
        "....................",
        "-t-----------c------",
        "..C.....P.....C.....",
        "--------c--------c--",
        "....................",
        "....................",
    },
};

static const char *nomes[TOTAL_FASES] = {"Rua do Amparo"};

static Texture2D rua;
static Texture2D ladeira;
static Texture2D coqueiro;
static Texture2D poste;
static Texture2D estandarte;

void CarregarTexturasFase(void)
{
    rua = LoadTexture("assets/cenario/rua.png");
    ladeira = LoadTexture("assets/cenario/ladeira.png");
    coqueiro = LoadTexture("assets/cenario/coqueiro.png");
    poste = LoadTexture("assets/cenario/poste.png");
    estandarte = LoadTexture("assets/cenario/estandarte.png");
}

void DescarregarTexturasFase(void)
{
    UnloadTexture(rua);
    UnloadTexture(ladeira);
    UnloadTexture(coqueiro);
    UnloadTexture(poste);
    UnloadTexture(estandarte);
}

char CaractereDaFase(int fase, int linha, int coluna)
{
    return fases[fase][linha][coluna];
}

bool LinhaEhRua(int fase, int linha)
{
    char c = fases[fase][linha][0];
    return c == '-' || c == 'c' || c == 't';
}

bool PosicaoBloqueada(int fase, int linha, int coluna)
{
    char c = fases[fase][linha][coluna];
    return c == 'C' || c == 'P' || c == 'E';
}

static void DesenharImagem(Texture2D textura, float x, float y, float largura, float altura)
{
    Rectangle origem = {0, 0, textura.width, textura.height};
    DrawTexturePro(textura, origem, (Rectangle){x, y, largura, altura}, (Vector2){0, 0}, 0, WHITE);
}

static void DesenharChegada(int fase)
{
    Color cores[] = {GOLD, RED, DARKGREEN, BLUE};

    for (int coluna = 0; coluna < COLUNAS; coluna++) {
        DrawRectangle(coluna * TAM_BLOCO, 0, TAM_BLOCO, TAM_BLOCO, cores[coluna % 4]);
    }

    int x = (LARGURA_TELA - MeasureText(nomes[fase], 24)) / 2;

    DrawRectangle(x - 10, 4, MeasureText(nomes[fase], 24) + 20, 32, Fade(BLACK, 0.6f));
    DrawText(nomes[fase], x, 8, 24, WHITE);
}

void DesenharFase(int fase)
{
    DesenharChegada(fase);

    for (int linha = 1; linha < LINHAS; linha++) {
        DesenharImagem(LinhaEhRua(fase, linha) ? rua : ladeira, 0, linha * TAM_BLOCO, LARGURA_TELA, TAM_BLOCO);
    }

    for (int linha = 1; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            float x = coluna * TAM_BLOCO;
            float y = linha * TAM_BLOCO;

            switch (fases[fase][linha][coluna]) {
                case 'C': DesenharImagem(coqueiro, x - 10, y - 50, 60, 90); break;
                case 'P': DesenharImagem(poste, x + 5, y - 50, 30, 90); break;
                case 'E': DesenharImagem(estandarte, x, y - 4, 40, 42); break;
            }
        }
    }
}
