#include <stdio.h>
#include "config.h"
#include "recordes.h"

#define ARQUIVO "scores.txt"

void CarregarRecordes(int recordes[])
{
    FILE *arquivo = fopen(ARQUIVO, "r");
    int i = 0;

    for (int j = 0; j < TOTAL_RECORDES; j++) {
        recordes[j] = 0;
    }

    if (arquivo == NULL) {
        return;
    }

    while (i < TOTAL_RECORDES && fscanf(arquivo, "%d", &recordes[i]) == 1) {
        i++;
    }

    fclose(arquivo);
}

void SalvarRecordes(const int recordes[])
{
    FILE *arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        return;
    }

    for (int i = 0; i < TOTAL_RECORDES; i++) {
        fprintf(arquivo, "%d\n", recordes[i]);
    }

    fclose(arquivo);
}

bool InserirRecorde(int recordes[], int pontos)
{
    int i = TOTAL_RECORDES - 1;

    if (pontos <= recordes[i]) {
        return false;
    }

    while (i > 0 && recordes[i - 1] < pontos) {
        recordes[i] = recordes[i - 1];
        i--;
    }

    recordes[i] = pontos;
    return true;
}
