#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "grafo_listaadj.h"

void inicializarGrafo(GRAFO* grafo, int numVertices) {
    grafo->numVertices = numVertices;
    grafo->numArestas = 0;
    grafo->listaAdj = (ARESTA**)malloc((numVertices + 1) * sizeof(ARESTA*));

    for (int i = 0; i <= numVertices; i++) {
        grafo->listaAdj[i] = NULL;
    }
}

void inserirAresta(GRAFO* grafo, int verticeOrigem, int verticeDestino, float peso) {
    // Criar a nova aresta
    ARESTA* novaAresta = (ARESTA*)malloc(sizeof(ARESTA));
    novaAresta->vertice_destino = verticeDestino;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;

    // Adicionar a nova aresta a lista de adjacência do vértice de origem
    if (grafo->listaAdj[verticeOrigem] == NULL) {
        grafo->listaAdj[verticeOrigem] = novaAresta;
    } else {
        ARESTA* atual = grafo->listaAdj[verticeOrigem];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaAresta;
    }

    // Adicionar a nova aresta à lista de adjacência do vértice de destino
    novaAresta = (ARESTA*)malloc(sizeof(ARESTA));
    novaAresta->vertice_destino = verticeOrigem;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;

    if (grafo->listaAdj[verticeDestino] == NULL) {
        grafo->listaAdj[verticeDestino] = novaAresta;
    } else {
        ARESTA* atual = grafo->listaAdj[verticeDestino];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaAresta;
    }

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
            ARESTA* aresta = grafo->listaAdj[u];
            while (aresta != NULL) {
                if (aresta->vertice_destino == v && aresta->peso < minPeso) {
                    minPeso = aresta->peso;
                    break;
                }
                aresta = aresta->prox;
            }
        }

        // Atualizar o caminho minimo se o peso minimo for maior
        if (minPeso > *pesoMinimo) {
            *pesoMinimo = minPeso;
            memcpy(caminhoMinimo, caminho, (index + 1) * sizeof(int));
        }
    } else {
        ARESTA* aresta = grafo->listaAdj[origem];
        while (aresta != NULL) {
            int i = aresta->vertice_destino;
            if (!visitado[i]) {
                buscaCaminhos(grafo, i, destino, visitado, caminho, index + 1, pesoMinimo, caminhoMinimo);
            }
            aresta = aresta->prox;
        }
    }

    visitado[origem] = 0;
}

float encontrarCaminhoMaiorPesoMinimo(GRAFO* grafo, int origem, int destino) {
    int* visitado = (int*)calloc(grafo->numVertices + 1, sizeof(int));
    int* caminho = (int*)malloc((grafo->numVertices + 1) * sizeof(int));
    int* caminhoMinimo = (int*)malloc((grafo->numVertices + 1) * sizeof(int));
    float pesoMinimo = -FLT_MAX;

    buscaCaminhos(grafo, origem, destino, visitado, caminho, 0, &pesoMinimo, caminhoMinimo);

    free(visitado);
    free(caminho);

    // Ajustar o caminho minimo encontrado
    int tamanhoCaminhoMinimo = 0;
    while (caminhoMinimo[tamanhoCaminhoMinimo] != destino) {
        tamanhoCaminhoMinimo++;
    }
    tamanhoCaminhoMinimo++;

    int* caminhoMinimoAjustado = (int*)malloc(tamanhoCaminhoMinimo * sizeof(int));
    memcpy(caminhoMinimoAjustado, caminhoMinimo, tamanhoCaminhoMinimo * sizeof(int));

    free(caminhoMinimo);

    // Ajustar o peso minimo
    if (pesoMinimo >= 4.5) {
        pesoMinimo = 4.5;
    } else if (pesoMinimo < 4.5 && pesoMinimo >= 4.0) {
        pesoMinimo = 4.0;
    } else if (pesoMinimo < 4.0 && pesoMinimo >= 3.5) {
        pesoMinimo = 3.5;
    } else if (pesoMinimo < 3.5 && pesoMinimo >= 3.0) {
        pesoMinimo = 3.0;
    } else if (pesoMinimo < 3.0 && pesoMinimo >= 2.5) {
        pesoMinimo = 2.5;
    }

//    Imprimir caminho e peso minimo
//    printf("Caminho com maior peso minimo entre %d e %d:\n", origem+1, destino+1);
//    for (int i = 0; i < tamanhoCaminhoMinimo; i++) {
//        printf("%d ", caminhoMinimoAjustado[i]+1);
//    }
//    printf("\nPeso minimo do caminho: %.1f\n", pesoMinimo);

    free(caminhoMinimoAjustado);

    return pesoMinimo;
}