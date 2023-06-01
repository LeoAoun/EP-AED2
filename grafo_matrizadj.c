#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "grafo_matrizadj.h"

void inicializarGrafo(GRAFO *grafo, int numVertices) {
    int i;
    grafo->numVertices = numVertices;
    grafo->numArestas = 0;

    grafo->mat = (float **)malloc(numVertices * sizeof(float*));
    for (i = 0; i < numVertices; i++) {
        grafo->mat[i] = (float*)calloc(numVertices, sizeof(float));
    }
}

void inserirAresta(GRAFO *grafo, int origem, int destino, float peso) {
    grafo->mat[origem][destino] = peso;
    grafo->mat[destino][origem] = peso;
    grafo->numArestas++;
}

void buscaCaminhos(GRAFO* grafo, int origem, int destino, int* visitado, int* caminho, int index, float* pesoMinimo, int* caminhoMinimo) {
    visitado[origem] = 1;
    caminho[index] = origem;

    if (origem == destino) {
        // Calcular peso minimo do caminho atual
        float minPeso = FLT_MAX;
        for (int i = 0; i < index; i++) {
            int u = caminho[i];
            int v = caminho[i + 1];
            if (grafo->mat[u][v] < minPeso) {
                minPeso = grafo->mat[u][v];
            }
        }

        // Atualizar o caminho minimo se o peso minimo for maior
        if (minPeso > *pesoMinimo) {
            *pesoMinimo = minPeso;
            memcpy(caminhoMinimo, caminho, (index + 1) * sizeof(int));
        }
    }
    else {
        for (int i = 0; i < grafo->numVertices; i++) {
            if (grafo->mat[origem][i] > 0 && !visitado[i]) {
                buscaCaminhos(grafo, i, destino, visitado, caminho, index + 1, pesoMinimo, caminhoMinimo);
            }
        }
    }

    visitado[origem] = 0;
}

float encontrarCaminhoMaiorPesoMinimo(GRAFO* grafo, int origem, int destino) {
    int* visitado = (int*)calloc(grafo->numVertices, sizeof(int));
    int* caminho = (int*)malloc(grafo->numVertices * sizeof(int));
    int* caminhoMinimo = (int*)malloc(grafo->numVertices * sizeof(int));
    float pesoMinimo = -FLT_MAX;

    buscaCaminhos(grafo, origem, destino, visitado, caminho, 0, &pesoMinimo, caminhoMinimo);

//  printf("Caminho com maior peso minimo entre %d e %d:\n", origem, destino);
//   for (int i = 0; i < grafo->numVertices; i++) {
//        printf("%d ", caminhoMinimo[i] + 1); // Soma 1 para exibir o indice do vertice corretamente
//   }

    free(visitado);
    free(caminho);
    free(caminhoMinimo);

    if(pesoMinimo >= 4.5) pesoMinimo = 4.5;
    else if(pesoMinimo < 4.5 && pesoMinimo >= 4.0) pesoMinimo = 4.0;
    else if(pesoMinimo < 4.0 && pesoMinimo >= 3.5) pesoMinimo = 3.5;
    else if(pesoMinimo < 3.5 && pesoMinimo >= 3.0) pesoMinimo = 3.0;
    else if(pesoMinimo < 3.0 && pesoMinimo >= 2.5) pesoMinimo = 2.5;

    //printf("Peso minimo do caminho: %.1f\n", pesoMinimo);

    return(pesoMinimo);
}

