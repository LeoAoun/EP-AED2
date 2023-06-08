#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "grafo_matrizadj.h"
//#include "grafo_listaadj.h"

void buscaCaminhos(GRAFO *grafo, int origem, int destino, int *visitado, int *caminho, int index, float *pesoMinimo, int *caminhoMinimo)
{
    visitado[origem] = 1;
    caminho[index] = origem;

    if (origem == destino)
    {
        // Calcular peso minimo do caminho atual
        float minPeso = calcularPesoMinimoAtual(grafo, caminho, index);

        // Atualizar o caminho minimo se o peso minimo for maior
        if (minPeso > *pesoMinimo)
        {
            *pesoMinimo = minPeso;
            memcpy(caminhoMinimo, caminho, (index + 1) * sizeof(int));
        }
    }
    else
    {
        buscaCaminho(grafo, origem, destino, visitado, caminho, index, pesoMinimo, caminhoMinimo);
    }

    visitado[origem] = 0;
}

float encontrarCaminhoMaiorPesoMinimo(GRAFO *grafo, int origem, int destino)
{
    int *visitado = (int *)calloc(grafo->numVertices + 1, sizeof(int));
    int *caminho = (int *)malloc((grafo->numVertices + 1) * sizeof(int));
    int *caminhoMinimo = (int *)malloc((grafo->numVertices + 1) * sizeof(int));
    float pesoMinimo = -FLT_MAX;

    buscaCaminhos(grafo, origem, destino, visitado, caminho, 0, &pesoMinimo, caminhoMinimo);

    free(visitado);
    free(caminho);

    // Ajustar o peso minimo
    if (pesoMinimo >= 4.5)
        pesoMinimo = 4.5;
    else if (pesoMinimo < 4.5 && pesoMinimo >= 4.0)
        pesoMinimo = 4.0;
    else if (pesoMinimo < 4.0 && pesoMinimo >= 3.5)
        pesoMinimo = 3.5;
    else if (pesoMinimo < 3.5 && pesoMinimo >= 3.0)
        pesoMinimo = 3.0;
    else if (pesoMinimo < 3.0 && pesoMinimo >= 2.5)
        pesoMinimo = 2.5;

    //    Imprimir caminho e peso minimo
    //    printf("Caminho com maior peso minimo entre %d e %d:\n", origem+1, destino+1);
    //    for (int i = 0; i < tamanhoCaminhoMinimo; i++) {
    //        printf("%d ", caminhoMinimoAjustado[i]+1);
    //    }
    //    printf("\nPeso minimo do caminho: %.1f\n", pesoMinimo);

    // free(caminhoMinimoAjustado);

    return pesoMinimo;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Argumentos incorretos\n");
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada)
    {
        printf("Arquivo de entrada nao encontrado\n");
        return 1;
    }

    int numVertices, numArestas, numConsultas;
    if (fscanf(entrada, "%d %d %d", &numVertices, &numArestas, &numConsultas) != 3)
    {
        printf("Argumentos incorretos na primeira linha do arquivo de entrada\n");
        fclose(entrada);
        return 1;
    }

    GRAFO grafo;
    inicializarGrafo(&grafo, numVertices);

    int origem, destino;
    float peso;
    for (int i = 0; i < numArestas; i++)
    {
        if (fscanf(entrada, "%d %d %f", &origem, &destino, &peso) != 3)
        {
            printf("Erro ao ler aresta no arquivo de entrada\n");
            fclose(entrada);
            return 1;
        }
        inserirAresta(&grafo, origem, destino, peso);
    }

    FILE *saida = fopen("saida.txt", "w");

    for (int i = 0; i < numConsultas; i++)
    {
        if (fscanf(entrada, "%d %d", &origem, &destino) != 2)
        {
            printf("Erro ao ler consulta no arquivo de entrada\n");
            fclose(entrada);
            fclose(saida);
            return 1;
        }
        float resposta = encontrarCaminhoMaiorPesoMinimo(&grafo, origem, destino);
        fprintf(saida, "%.1f\n", resposta);
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
