#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include "grafo_listaadj.h"

void inicializarGrafo(GRAFO *grafo, int numVertices)
{
    grafo->numVertices = numVertices;
    grafo->numArestas = 0;
    grafo->listaAdj = (ARESTA **)malloc((numVertices + 1) * sizeof(ARESTA *));

    for (int i = 0; i <= numVertices; i++)
    {
        grafo->listaAdj[i] = NULL;
    }
}

void inserirAresta(GRAFO *grafo, int verticeOrigem, int verticeDestino, float peso)
{
    // Criar a nova aresta
    ARESTA *novaAresta = (ARESTA *)malloc(sizeof(ARESTA));
    novaAresta->vertice_destino = verticeDestino;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;

    // Adicionar a nova aresta a lista de adjacência do vértice de origem
    if (grafo->listaAdj[verticeOrigem] == NULL)
    {
        grafo->listaAdj[verticeOrigem] = novaAresta;
    }
    else
    {
        ARESTA *atual = grafo->listaAdj[verticeOrigem];
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novaAresta;
    }

    // Adicionar a nova aresta à lista de adjacência do vértice de destino
    novaAresta = (ARESTA *)malloc(sizeof(ARESTA));
    novaAresta->vertice_destino = verticeOrigem;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;

    if (grafo->listaAdj[verticeDestino] == NULL)
    {
        grafo->listaAdj[verticeDestino] = novaAresta;
    }
    else
    {
        ARESTA *atual = grafo->listaAdj[verticeDestino];
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novaAresta;
    }

    grafo->numArestas++;
}

float calcularPesoMinimoAtual(GRAFO *grafo, int *caminho, int index)
{
    float minPeso = FLT_MAX;
    for (int i = 0; i < index; i++)
    {
        int u = caminho[i];
        int v = caminho[i + 1];

        ARESTA *aresta = grafo->listaAdj[u];
        while (aresta != NULL)
        {
            if (aresta->vertice_destino == v && aresta->peso < minPeso)
            {
                minPeso = aresta->peso;
                break;
            }
            aresta = aresta->prox;
        }
    }
    return minPeso;
}

void buscaCaminho(GRAFO *grafo, int origem, int destino, int *visitado, int *caminho, int index, float *pesoMinimo, int *caminhoMinimo)
{
    ARESTA *aresta = grafo->listaAdj[origem];
    while (aresta != NULL)
    {
        int i = aresta->vertice_destino;
        if (!visitado[i])
        {
            buscaCaminhos(grafo, i, destino, visitado, caminho, index + 1, pesoMinimo, caminhoMinimo);
        }
        aresta = aresta->prox;
    }
}