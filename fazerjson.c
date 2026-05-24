#include <stdio.h>
#include "mapa.h"

void exportarJSON(Posicao inicio, Posicao fim, Posicao caminho[], int total) {
    FILE *arquivo = fopen("caminho.json", "w");

    if (arquivo == NULL) {
        printf("não foi possível criar o arquivo JSON.\n");
        return;
    }

    fprintf(arquivo, "{\n");

    fprintf(arquivo, " \"caminho\": [\n");

    for (int i = total - 1; i >= 0; i--) {

        fprintf(arquivo,"    { \"andar\": %d, \"x\": %d, \"y\": %d }",caminho[i].andar,caminho[i].x,caminho[i].y);

        if (i > 0) { fprintf(arquivo, ","); }

        fprintf(arquivo, "\n");
    }

    fprintf(arquivo, "  ],\n");

    fprintf(arquivo,"  \"inicio\": { \"andar\": %d, \"x\": %d, \"y\": %d },\n",inicio.andar,inicio.x,inicio.y);

    fprintf(arquivo,"  \"fim\": { \"andar\": %d, \"x\": %d, \"y\": %d },\n",fim.andar,fim.x,fim.y);

    fprintf(arquivo, "  \"mapa\": [\n");

    for (int a = 0; a < ANDARES; a++) {

        fprintf(arquivo, "    [\n");

        for (int x = 0; x < LINHAS; x++) {

            fprintf(arquivo, "      [");

            for (int y = 0; y < COLUNAS; y++) {

                fprintf(
                    arquivo,
                    "%d",
                    mapa[a][x][y]
                );

                if (y < COLUNAS - 1) {
                    fprintf(arquivo, ",");
                }
            }

            fprintf(arquivo, "]");

            if (x < LINHAS - 1) {
                fprintf(arquivo, ",");
            }

            fprintf(arquivo, "\n");
        }

        fprintf(arquivo, "    ]");

        if (a < ANDARES - 1) {
            fprintf(arquivo, ",");
        }

        fprintf(arquivo, "\n");
    }

    fprintf(arquivo, "  ]\n");

    fprintf(arquivo, "}\n");

    fclose(arquivo);

    printf("deu bom fi.\n");
}