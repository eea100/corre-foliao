#include "raylib.h"
#include "config.h"

int main(void)
{
    const char *titulo = "Corre, Foliao!";

    InitWindow(LARGURA_TELA, ALTURA_TELA, titulo);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){42, 18, 64, 255});
        DrawText(titulo, (LARGURA_TELA - MeasureText(titulo, 48)) / 2, 290, 48, GOLD);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}