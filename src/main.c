#include "raylib.h"
#include "config.h"
#include "menu.h"
#include "fase.h"

int main(void)
{
    bool jogando = false;
    Camera2D camera = {.offset = {0, ALTURA_HUD}, .zoom = 1};

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Corre, Foliao!");
    SetTargetFPS(60);
    ChangeDirectory(GetApplicationDirectory());
    CarregarMenu();
    CarregarTexturasFase();

    while (!WindowShouldClose()) {
        if (!jogando && IsKeyPressed(KEY_ENTER)) {
            jogando = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (jogando) {
            BeginMode2D(camera);
            DesenharFase(0);
            EndMode2D();
            DrawRectangle(0, 0, LARGURA_TELA, ALTURA_HUD, (Color){42, 18, 64, 255});
        } else {
            DesenharMenu();
        }

        EndDrawing();
    }

    DescarregarTexturasFase();
    DescarregarMenu();
    CloseWindow();
    return 0;
}
