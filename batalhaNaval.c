#include <stdio.h>
#include <string.h>

#define TAM 10

// Função para inicializar o tabuleiro
void inicializarMatriz(int matriz[TAM][TAM], int valor) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            matriz[i][j] = valor;
}

// Função para exibir o tabuleiro com legenda
void exibirMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Posiciona um navio horizontal ou vertical
int posicionarNavio(int matriz[TAM][TAM], int x, int y, int tamanho, char direcao) {
    if (direcao == 'h') {
        if (y + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (matriz[x][y + i] != 0) return 0;
            matriz[x][y + i] = 3;
        }
    } else if (direcao == 'v') {
        if (x + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (matriz[x + i][y] != 0) return 0;
            matriz[x + i][y] = 3;
        }
    }
    return 1;
}

// Posiciona navio diagonal
int posicionarNavioDiagonal(int matriz[TAM][TAM], int x, int y, int tamanho, int direcao) {
    for (int i = 0; i < tamanho; i++) {
        int xi = (direcao == 0) ? x + i : x + i;
        int yi = (direcao == 0) ? y + i : y - i;
        if (xi >= TAM || yi < 0 || yi >= TAM || matriz[xi][yi] != 0)
            return 0;
    }
    for (int i = 0; i < tamanho; i++) {
        int xi = (direcao == 0) ? x + i : x + i;
        int yi = (direcao == 0) ? y + i : y - i;
        matriz[xi][yi] = 3;
    }
    return 1;
}

// Aplica habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matrizHab[5][5], int centroX, int centroY) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            int x = centroX - 2 + i;
            int y = centroY - 2 + j;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM && matrizHab[i][j] == 1 && tabuleiro[x][y] != 3)
                tabuleiro[x][y] = 5;
        }
}

// Preenche matriz de cone
void criarCone(int matriz[5][5]) {
    inicializarMatriz(matriz, 0);
    matriz[0][2] = 1;
    matriz[1][1] = matriz[1][2] = matriz[1][3] = 1;
    for (int i = 0; i < 5; i++)
        matriz[2][i] = 1;
}

// Preenche matriz de cruz
void criarCruz(int matriz[5][5]) {
    inicializarMatriz(matriz, 0);
    for (int i = 0; i < 5; i++) {
        matriz[2][i] = 1;
        matriz[i][2] = 1;
    }
}

// Preenche matriz de octaedro (losango)
void criarOctaedro(int matriz[5][5]) {
    inicializarMatriz(matriz, 0);
    matriz[0][2] = 1;
    matriz[1][1] = matriz[1][3] = 1;
    matriz[2][0] = matriz[2][4] = 1;
    matriz[3][1] = matriz[3][3] = 1;
    matriz[4][2] = 1;
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarMatriz(tabuleiro, 0);

    // Posicionar navios
    posicionarNavio(tabuleiro, 1, 1, 3, 'h');
    posicionarNavio(tabuleiro, 4, 5, 3, 'v');
    posicionarNavioDiagonal(tabuleiro, 0, 0, 3, 0); // diagonal principal
    posicionarNavioDiagonal(tabuleiro, 0, 9, 3, 1); // diagonal secundária

    // Matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades
    aplicarHabilidade(tabuleiro, cone, 5, 5);
    aplicarHabilidade(tabuleiro, cruz, 2, 2);
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);

    // Exibir tabuleiro
    exibirMatriz(tabuleiro);

    return 0;
}

