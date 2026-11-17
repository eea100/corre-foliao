# Corre, Folião!

Casual game em C com Raylib ambientado no Carnaval de Olinda. Projeto da disciplina Programação Imperativa e Funcional (PIF) — CESAR School, 2026.2.

<p align="center">
  <img src="docs/menu.png" width="32%">
  <img src="docs/jogo.png" width="32%">
  <img src="docs/fim.png" width="32%">
</p>

## Vídeo

[![Vídeo do jogo rodando](https://img.youtube.com/vi/9uHPenxZqtA/hqdefault.jpg)](https://youtu.be/9uHPenxZqtA)

Assista no YouTube: https://youtu.be/9uHPenxZqtA

## O jogo

O folião precisa atravessar quatro pontos do Carnaval de Olinda para chegar no bloco:

1. Rua do Amparo
2. Ladeira da Misericórdia
3. Alto da Sé
4. Quatro Cantos

Cada fase é uma tela com ruas e ladeiras. Carros e trios elétricos passam nas ruas, bonecos gigantes passam nas ladeiras, e coqueiros, postes e estandartes bloqueiam o caminho. Chegando na faixa colorida do topo, o folião passa para a próxima fase, com mais obstáculos e mais rápidos.

- O folião começa com **3 vidas**. Bateu em um obstáculo, perde uma vida e volta ao começo da fase.
- **+10 pontos** a cada linha nova alcançada e **+100** a cada fase completada.
- Os **5 melhores placares** ficam salvos no arquivo `scores.txt`.

## Controles

| Tecla | Ação |
|---|---|
| Setas | Andar |
| ENTER | Começar / voltar ao menu |
| P | Pausar |
| ESC | Sair |

## Como compilar e rodar

É preciso ter a [Raylib](https://www.raylib.com/) instalada. O projeto foi feito com a Raylib 5.5.

### Linux

**1. Instalar a Raylib** (só na primeira vez)

Ubuntu / Debian, instalar as dependências:

```
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
```

Fedora, instalar as dependências:

```
sudo dnf install gcc make git alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel
```

Depois, em qualquer distribuição, compilar e instalar a Raylib:

```
git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

No Arch Linux basta `sudo pacman -S raylib`.

**2. Baixar e rodar o jogo**

```
git clone https://github.com/eea100/corre-foliao.git
cd corre-foliao
make run
```

### Windows

1. Instale a Raylib pelo instalador oficial (raylib.itch.io/raylib), na pasta padrão `C:\raylib`.
2. Na pasta do projeto, rode:

```
C:\raylib\w64devkit\bin\make.exe run
```

## Estrutura

```
corre-foliao/
├── Makefile
├── include/          cabeçalhos (.h)
├── src/
│   ├── main.c        janela, loop principal e troca menu/jogo
│   ├── menu.c        tela de título
│   ├── fase.c        matriz das fases e desenho do cenário
│   ├── jogador.c     movimento e animação do folião
│   ├── obstaculo.c   lista encadeada de carros, trios e bonecos
│   ├── jogo.c        regras: vidas, pontos, fases, pausa e fim
│   └── recordes.c    top 5 salvo em arquivo
└── assets/           imagens do cenário, folião, veículos e bonecos
```

## Requisitos da disciplina

| Requisito | Onde está |
|---|---|
| Structs | `struct Jogador`, `struct Node` e `struct Jogo` |
| Ponteiros | Funções recebem `struct Jogo *` e `struct Jogador *`; `struct Node **head` |
| Alocação dinâmica | `malloc` em `CriarNo` e `free` em `LiberarLista` (`obstaculo.c`) |
| Lista encadeada | Obstáculos da fase em uma lista de `struct Node` ligada por `next` |
| Matrizes | `fases[4][15][21]` com o mapa das fases; matrizes de sprites |
| Arquivo | Top 5 lido e salvo em `scores.txt` (`recordes.c`) |

## Equipe

- Eduardo Esteves De Albuquerque
- Guilherme Melo Caldas de Lira
