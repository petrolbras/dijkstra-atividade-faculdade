#ifndef MAPA_H
#define MAPA_H

#define ANDARES 2
#define LINHAS 23
#define COLUNAS 11

#define PAREDE 1
#define CORREDOR 0
#define SALA 4
#define ESCADA 5
#define BIBLIOTECA 3
#define CAPELA 2
#define CAMINHO 9;

typedef struct {

    int andar;
    int x;
    int y;

} Posicao;

typedef struct {

    Posicao origem;
    Posicao destino;

} Conexao;

int caminhavel(int andar, int x, int y);

extern int mapa[ANDARES][LINHAS][COLUNAS];

extern Conexao conexoes[];

extern const int totalConexoes;

#endif