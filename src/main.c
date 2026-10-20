   #include "raylib.h"
   #include "config.h"
   #include "menu.h"

   int main(void)
   {
       InitWindow(LARGURA_TELA, ALTURA_TELA, "Corre, Foliao!");
       SetTargetFPS(60);
       ChangeDirectory(GetApplicationDirectory());
       CarregarMenu();

       while (!WindowShouldClose()) {
           BeginDrawing();
           ClearBackground(BLACK);
           DesenharMenu();
           EndDrawing();
       }

       DescarregarMenu();
       CloseWindow();
       return 0;
   }