   #include "raylib.h"
   #include "config.h"
   #include "menu.h"

   static Texture2D fundo;

   void CarregarMenu(void)
   {
       fundo = LoadTexture("assets/cenario/fundo_menu.png");
   }

   void DescarregarMenu(void)
   {
       UnloadTexture(fundo);
   }

   static void TextoCentro(const char *texto, int y, int tamanho, Color cor)
   {
       int x = (LARGURA_TELA - MeasureText(texto, tamanho)) / 2;
       DrawText(texto, x + 2, y + 2, tamanho, BLACK);
       DrawText(texto, x, y, tamanho, cor);
   }

   void DesenharMenu(void)
   {
       Rectangle origem = {0, 0, fundo.width, fundo.height};
       DrawTexturePro(fundo, origem, (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA}, (Vector2){0, 0}, 0, WHITE);
       DrawRectangle(0, 285, LARGURA_TELA, 100, Fade(BLACK, 0.55f));

       if ((int)(GetTime() * 2) % 2 == 0) {
           TextoCentro("ENTER para jogar", 300, 30, GOLD);
       }

       TextoCentro("Setas: andar   ESC: sair", 345, 20, RAYWHITE);
   }