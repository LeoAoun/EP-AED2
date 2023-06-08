#ifndef GRAFO_LISTAADJ_H
#define GRAFO_LISTAADJ_H

typedef struct str_aresta {
    int vertice_destino;
    float peso;
    struct str_aresta* prox;
} ARESTA;

typedef struct {
    ARESTA** listaAdj;
    int numVertices;
    int numArestas;
} GRAFO;

void inicializarGrafo(GRAFO* grafo, int numVertices);
void inserirAresta(GRAFO* grafo, int origem, int destino, float peso);
float calcularPesoMinimoAtual(GRAFO *grafo, int *caminho, int index);
void buscaCaminho(GRAFO* grafo, int origem, int destino, int *visitado, int *caminho, int index, float *pesoMinimo, int *caminhoMinimo);
void buscaCaminhos(GRAFO* grafo, int origem, int destino, int* visitado, int* caminho, int index, float* pesoMinimo, int* caminhoMinimo);
float encontrarCaminhoMaiorPesoMinimo(GRAFO* grafo, int origem, int destino);

#endif // GRAFO_LISTAADJ_H
