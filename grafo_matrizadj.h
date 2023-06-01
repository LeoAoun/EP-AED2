#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AN -1

typedef struct{
    float **mat;
    int numVertices;
    int numArestas;
}GRAFO;

void inicializarGrafo(GRAFO *grafo, int numVertices);
void inserirAresta(GRAFO *grafo, int origem, int destino, float peso);
void buscaCaminhos(GRAFO* grafo, int origem, int destino, int* visitado, int* caminho, int index, float* pesoMinimo, int* caminhoMinimo);
float encontrarCaminhoMaiorPesoMinimo(GRAFO* grafo, int origem, int destino);

#endif // GRAFO_MATRIZ_H
