#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
// STRUCTS
typedef struct No {
    int destino;
    struct No *proximo;
} No;
 
typedef struct {
    int numVertices;
    No **listaAdj;
    int *grauEntrada;
} Grafo;
 
// FUNCTIONS
No* criarNo(int destino) 
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}
 
Grafo* criarGrafo(int vertices) 
{
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->listaAdj = (No**)malloc((vertices + 1) * sizeof(No*));
    grafo->grauEntrada = (int*)calloc(vertices + 1, sizeof(int));
    for (int i = 0; i <= vertices; i++) 
        grafo->listaAdj[i] = NULL;
    
    return grafo;
}
 
void adicionarAresta(Grafo* grafo, int origem, int destino) 
{
    No* novoNo = criarNo(destino);
    novoNo->proximo = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNo;
    grafo->grauEntrada[destino]++;
}
 
void processarUsuarios(Grafo* grafo) 
{
    int fila[grafo->numVertices + 1];
    int inicio = 0, fim = 0;
    bool removido[grafo->numVertices + 1];
 
    for (int i = 0; i <= grafo->numVertices; i++) 
        removido[i] = false;
    
    
    for (int i = 1; i <= grafo->numVertices; i++) 
    {
        if (grafo->grauEntrada[i] == 0) {
            fila[fim++] = i;
            removido[i] = true;
        }
    }
    
    while (inicio < fim) 
    {
        int usuario = fila[inicio++];
        No* atual = grafo->listaAdj[usuario];
        
        while (atual) 
        {
            int v = atual->destino;
            grafo->grauEntrada[v]--;
            if (grafo->grauEntrada[v] == 0 && !removido[v]) {
                removido[v] = true;
                fila[fim++] = v;
            }
            atual = atual->proximo;
        }
    }
    
    int resultado[grafo->numVertices];
    int contador = 0;
 
    for (int i = 1; i <= grafo->numVertices; i++) 
    {
        if (!removido[i]) 
            resultado[contador++] = i;
    }
    
    // Ordenando usuários restantes
    for (int i = 0; i < contador - 1; i++) 
    {
        for (int j = i + 1; j < contador; j++) 
        {
            if (resultado[i] > resultado[j]) {
                int temp = resultado[i];
                resultado[i] = resultado[j];
                resultado[j] = temp;
            }
        }
    }
    
    // -- Output --
    for (int i = 0; i < contador; i++) 
    {
        printf("%d", resultado[i]);
        if (i < contador - 1) printf(" ");
    }
}
 
// MAIN FUNCTION
int main() {
    // -- Input N --
    int N;
    scanf("%d", &N);
    
    Grafo* grafo = criarGrafo(N);
    
    // -- Input Lines -- 
    int a, b;
    for (int i = 0; i < N; i++) 
    {
        if (scanf("%d %d", &a, &b) != 2) return 1;
        adicionarAresta(grafo, a, b);
    }
    
    processarUsuarios(grafo);
    
    return 0;
}