#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include "grafo_matrizadj.h"

void inicializarGrafo(GRAFO *grafo, int numVertices)
{
    int i;
    grafo->numVertices = numVertices;
    grafo->numArestas = 0;

    grafo->mat = (float **)malloc(numVertices * sizeof(float *));
    for (i = 0; i < numVertices; i++)
    {
        grafo->mat[i] = (float *)calloc(numVertices, sizeof(float));
    }
}

void inserirAresta(GRAFO *grafo, int origem, int destino, float peso)
{
    grafo->mat[origem][destino] = peso;
    grafo->mat[destino][origem] = peso;
    grafo->numArestas++;
}

float calcularPesoMinimoAtual(GRAFO *grafo, int *caminho, int index)
{
    float minPeso = FLT_MAX;
    for (int i = 0; i < index; i++)
    {
        int u = caminho[i];
        int v = caminho[i + 1];

        if (grafo->mat[u][v] < minPeso)
        {
            minPeso = grafo->mat[u][v];
        }
    }
    return minPeso;
}

void buscaCaminho(GRAFO* grafo, int origem, int destino, int *visitado, int *caminho, int index, float *pesoMinimo, int *caminhoMinimo)
{
    for (int i = 0; i < grafo->numVertices; i++)
    {
        if (grafo->mat[origem][i] > 0 && !visitado[i])
        {
            buscaCaminhos(grafo, i, destino, visitado, caminho, index + 1, pesoMinimo, caminhoMinimo);
        }
    }
}

