#include <stdio.h>
#include "mapa.h"

void exportarJSON(
    Posicao inicio,
    Posicao fim,
    Posicao caminho[],
    int total
);

typedef struct {
    int distancia;

    int visitado;

    Posicao anterior;

} No;

int dx[4] = {-1, 1, 0, 0};

int dy[4] = {0, 0, -1, 1};

int CUSTO_PADRAO = 1;
int CUSTO_ESCADA = 5;

Posicao encontrarMenorDistancia(No nos[ANDARES][LINHAS][COLUNAS]) {
    int menor = 9999;
    int i, j, k;

    Posicao menorPosicao = {-1, -1, -1};

    for (i = 0; i < ANDARES; i++) {
        for (j = 0; j < LINHAS; j++) {
            for (k = 0; k < COLUNAS; k++) {
                if (!nos[i][j][k].visitado && nos[i][j][k].distancia < menor) {
                    menor = nos[i][j][k].distancia;
                    menorPosicao.andar = i;
                    menorPosicao.x = j;
                    menorPosicao.y = k;
                }
            }
        }
    }

    return menorPosicao;
}

void dijkstra(Posicao inicio, Posicao fim) {
    No nos[ANDARES][LINHAS][COLUNAS];

    int i, j, k;

    // aqui é zerado todos os valores, como os visitados, andar dos anteriores (no caso os predecessors) e também é settado uma distância alta para todos os nós, assim temos certeza que não visitamos esse nó ainda. Bem como a posição inicial.

    for (i = 0; i < ANDARES; i++) {
        for (j = 0; j < LINHAS; j++) {
            for (k = 0; k < COLUNAS; k++) {
                nos[i][j][k].distancia = 9999;

                nos[i][j][k].visitado = 0;

                nos[i][j][k].anterior.andar = -1;

                nos[i][j][k].anterior.x = -1;

                nos[i][j][k].anterior.y = -1;
            }
        }
    }

    nos[inicio.andar][inicio.x][inicio.y].distancia = 0;

    while (1) {
        Posicao atual = encontrarMenorDistancia(nos); // aqui encontramos o nó com a menor distância, aquele que "estamos" atualmente

        int i, j, k;

        if (atual.andar == -1) { break; }

        if (atual.andar == fim.andar && atual.x == fim.x && atual.y == fim.y) { break; }

        nos[atual.andar][atual.x][atual.y].visitado = 1; // aqui marcamos o nó atual como visitado

        for (i = 0; i < 4; i++) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if(!caminhavel(atual.andar, nx, ny)) { continue; } // aqui verificamos se a posição é caminhável, ou seja, se não é uma parede

            int novaDist = nos[atual.andar][atual.x][atual.y].distancia + CUSTO_PADRAO;

            if (novaDist < nos[atual.andar][nx][ny].distancia) {
                nos[atual.andar][nx][ny].distancia = novaDist;
                nos[atual.andar][nx][ny].anterior = atual;
            }
        }

        for (k = 0; k < totalConexoes; k++) {

            Conexao c = conexoes[k];

            if (atual.andar == c.origem.andar && atual.x == c.origem.x && atual.y == c.origem.y) {

                Posicao destino = c.destino;

                int novaDistancia = nos[atual.andar][atual.x][atual.y].distancia + CUSTO_ESCADA; // detalhe, só somamos custo_escada se usarmos a escada, diferentemente de cima onde usamos custo_padrao para um andar qualquer

                if (novaDistancia < nos[destino.andar][destino.x][destino.y].distancia) {

                    nos[destino.andar][destino.x][destino.y].distancia = novaDistancia;

                    nos[destino.andar][destino.x][destino.y].anterior = atual;
                }
            }
        }
    }

    if (nos[fim.andar][fim.x][fim.y].distancia == 9999) {
        printf("Caminho não encontrado.\n");
        return;
    }

    printf("Caminho encontrado com custo %d:\n", nos[fim.andar][fim.x][fim.y].distancia);

    // aqui é onde iremos reconstruir o caminho do zero, observe que começamos pelo fim, e vamos através de uma condição no while reconstruindo o caminho até chegar no inicio (até o andar ser -1)

    Posicao caminho[1000];

    int total = 0;

    Posicao atual = fim;

    while (atual.andar != -1) {

        caminho[total++] = atual;

        atual = nos[atual.andar][atual.x][atual.y].anterior;
    }

    exportarJSON(inicio, fim, caminho, total);
}

int main() {
    
    Posicao inicio;
    Posicao fim;

    printf("=== POSICAO INICIAL ===\n");

    printf("Andar: ");
    scanf("%d", &inicio.andar);

    printf("X: ");
    scanf("%d", &inicio.x);

    printf("Y: ");
    scanf("%d", &inicio.y);

    printf("\n=== POSICAO FINAL ===\n");

    printf("Andar: ");
    scanf("%d", &fim.andar);

    printf("X: ");
    scanf("%d", &fim.x);

    printf("Y: ");
    scanf("%d", &fim.y);

    printf("\n");

    dijkstra(inicio, fim); 

    return 0;
}