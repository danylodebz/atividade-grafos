#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_VERTICES 100

// Nó para a lista de adjacência
typedef struct node {
    int vertex;
    struct node *next;
} Node;

// Grafo representado por matriz de adjacência
typedef struct {
    int numVertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} GraphMatrix;

// Grafo representado por lista de adjacência
typedef struct {
    int numVertices;
    Node *adjList[MAX_VERTICES];
} GraphList;

// Função para criar um novo nó
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void readGraphMatrix(GraphMatrix *graph, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fscanf(fp, "%d", &graph->numVertices);
    int i, j;
    for (i = 0; i < graph->numVertices; ++i) {
        for (j = 0; j < graph->numVertices; ++j) {
            fscanf(fp, "%d", &graph->matrix[i][j]);
        }
    }

    fclose(fp);
}

void readGraphList(GraphList *graph, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fscanf(fp, "%d", &graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    int i, j;
    while (fscanf(fp, "%d %d", &i, &j) != EOF) {
        Node *newNode = createNode(j);
        newNode->next = graph->adjList[i];
        graph->adjList[i] = newNode;

        newNode = createNode(i);
        newNode->next = graph->adjList[j];
        graph->adjList[j] = newNode;
    }

    fclose(fp);
}

void DFSRecursive(GraphMatrix *graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->matrix[v][i] && !visited[i]) {
            DFSRecursive(graph, i, visited);
        }
    }
}

void DFSIterative(GraphMatrix *graph, int start) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES];
    int top = -1;

    stack[++top] = start;

    while (top >= 0) {
        int v = stack[top--];

        if (!visited[v]) {
            printf("%d ", v);
            visited[v] = true;
        }

        for (int i = graph->numVertices - 1; i >= 0; i--) {
            if (graph->matrix[v][i] && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Modo de uso: %s [matrix|list]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "matrix") == 0) {
        // Teste com matriz de adjacência
        GraphMatrix graphMatrix;
        readGraphMatrix(&graphMatrix, "graph_matrix.txt");

        printf("DFS Recursiva iniciando no vértice 0:\n");
        bool visited[MAX_VERTICES] = {false};
        DFSRecursive(&graphMatrix, 0, visited);

        printf("\nDFS Iterativa iniciando no vértice 0:\n");
        DFSIterative(&graphMatrix, 0);
    } else if (strcmp(argv[1], "list") == 0) {
        // Teste com lista de adjacência
        GraphList graphList;
        readGraphList(&graphList, "graph_list.txt");

        printf("A leitura do grafo com lista de adjacência foi realizada com sucesso.\n");
        // Aqui você poderia adicionar a DFS para listas de adjacência, se necessário
    } else {
        printf("Opção inválida. Use 'matrix' ou 'list'.\n");
        return 1;
    }

    return 0;
}
