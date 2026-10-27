#include "raylib.h"
#include "config.h"
#include "fase.h"
#include "menu.h"
#include "jogo.h"
#include "recordes.h"

int main(void)
{
    Jogo jogo = {0};
    bool jogando = false;

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Corre, Foliao!");
    SetTargetFPS(60);
    ChangeDirectory(GetApplicationDirectory());

    CarregarMenu();
    CarregarTexturasFase();
    CarregarTexturasJogador();
    CarregarTexturasObstaculo();
    CarregarRecordes(jogo.recordes);

    while (!WindowShouldClose()) {
        if (!jogando && IsKeyPressed(KEY_ENTER)) {
            IniciarJogo(&jogo);
            jogando = true;
        } else if (jogando && jogo.fim && IsKeyPressed(KEY_ENTER)) {
            jogando = false;
        } else if (jogando) {
            AtualizarJogo(&jogo);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (jogando) {
            DesenharJogo(&jogo);
        } else {
            DesenharMenu(jogo.recordes[0]);
        }

        EndDrawing();
    }

    FinalizarJogo(&jogo);
    DescarregarTexturasObstaculo();
    DescarregarTexturasJogador();
    DescarregarTexturasFase();
    DescarregarMenu();
    CloseWindow();
    return 0;
}
