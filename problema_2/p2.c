#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct 
{
    double x, y;
} Ponto;
 
// distância euclidiana entre dois pontos
double distancia(Ponto p1, Ponto p2) 
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
 
int compararX(const void *a, const void *b) 
{
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}
int compararY(const void *a, const void *b) 
{
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}
 
// Função recursiva que encontra a menor distância no conjunto de pontos
double shamos_hoey(Ponto *pontos, Ponto *pontos_y, int esquerda, int direita) 
{
    if (direita - esquerda <= 3) 
    {
        double min_dist = INFINITY;
        for (int i = esquerda; i < direita; i++) 
        {
            for (int j = i + 1; j < direita; j++) 
            {
                double d = distancia(pontos[i], pontos[j]);
                if (d < min_dist) 
                    min_dist = d;
                
            }
        }
        return min_dist;
    }
 
    int meio = (esquerda + direita) / 2;
    double d_esquerda = shamos_hoey(pontos, pontos_y, esquerda, meio);
    double d_direita = shamos_hoey(pontos, pontos_y, meio, direita);
 
    double d = fmin(d_esquerda, d_direita);
 
    // copiando pra aux
    Ponto faixa[direita - esquerda];
    int k = 0;
    for (int i = esquerda; i < direita; i++) 
    {
        if (fabs(pontos[i].x - pontos[meio].x) < d) 
            faixa[k++] = pontos[i];
        
    }
 
    qsort(faixa, k, sizeof(Ponto), compararY); //ordenando
 
    // verificando se a distancia minima esta na faixa
    for (int i = 0; i < k; i++) 
    {
        for (int j = i + 1; j < k && faixa[j].y - faixa[i].y < d; j++) 
        {
            double dist = distancia(faixa[i], faixa[j]);
            if (dist < d) 
                d = dist;      
        }
    }
 
    return d;
}
 
int main() {
    int N;
    scanf("%d", &N);
 
    Ponto *pontos = (Ponto *)malloc(N * sizeof(Ponto));
    if (pontos == NULL) 
    {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
 
    for (int i = 0; i < N; i++) 
        scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
    
 
    // ordenando eixo x
    Ponto *pontos_y = (Ponto *)malloc(N * sizeof(Ponto));
    if (pontos_y == NULL) 
    {
        printf("Erro ao alocar memória!\n");
        free(pontos);
        return 1;
    }
 
    for (int i = 0; i < N; i++) 
        pontos_y[i] = pontos[i];
    
 
    qsort(pontos, N, sizeof(Ponto), compararX);
 
    // algoritmo de Shamos e Hoey
    double min_dist = shamos_hoey(pontos, pontos_y, 0, N);
 
    // -- Output --
    printf("%.10lf\n", min_dist);
 
    // liberando espaço 
    free(pontos);
    free(pontos_y);
    return 0;
}