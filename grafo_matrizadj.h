#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

typedef struct{
    float **mat;
    int numVertices;
    int numArestas;
}GRAFO;

void inicializarGrafo(GRAFO *grafo, int numVertices);
void inserirAresta(GRAFO *grafo, int origem, int destino, float peso);
float calcularPesoMinimoAtual(GRAFO *grafo, int *caminho, int index);
void buscaCaminho(GRAFO* grafo, int origem, int destino, int *visitado, int *caminho, int index, float *pesoMinimo, int *caminhoMinimo);
void buscaCaminhos(GRAFO* grafo, int origem, int destino, int* visitado, int* caminho, int index, float* pesoMinimo, int* caminhoMinimo);
float encontrarCaminhoMaiorPesoMinimo(GRAFO* grafo, int origem, int destino);

#endif // GRAFO_MATRIZ_H
