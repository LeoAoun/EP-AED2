#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "grafo_matrizadj.h"
//#include "grafo_listaadj.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Argumentos incorretos\n");
        return 1;
    }

    FILE* entrada = fopen(argv[1], "r");
    if (!entrada){
         printf("Arquivo de entrada nao encontrado\n");
         return 1;
    }

    int numVertices, numArestas, numConsultas;
    if (fscanf(entrada, "%d %d %d", &numVertices, &numArestas, &numConsultas) != 3) {
        printf("Argumentos incorretos na primeira linha do arquivo de entrada\n");
        fclose(entrada);
        return 1;
    }

    GRAFO grafo;
    inicializarGrafo(&grafo, numVertices);

    int origem, destino;
    float peso;
    for(int i = 0; i < numArestas; i++){
        if(fscanf(entrada, "%d %d %f", &origem, &destino, &peso) != 3){
            printf("Erro ao ler aresta no arquivo de entrada\n");
            fclose(entrada);
            return 1;
        }
        inserirAresta(&grafo, origem, destino, peso);
    }

    FILE* saida = fopen("saida.txt", "w");

    for(int i = 0; i < numConsultas; i++){
        if (fscanf(entrada, "%d %d", &origem, &destino) != 2) {
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
