#include <stdio.h>
#include <stdlib.h>
 
// FUNCTIONS
int qsort_aux(const void *a, const void *b) 
{
    return (*(int *)b - *(int *)a);
}
 
int calculate(int N, int *sizes, int M) //funcao que calcula o minimo decaixas -- O(M * N)
{
    int *dp = (int *)malloc((N + 1) * sizeof(int));
 
    for (int i = 0; i <= N; i++) 
        dp[i] = 999999999; //sentinelas int altissimos
    
 
    dp[0] = 0; 
 
    for (int i = 0; i < M; i++) 
    {
        for (int j = sizes[i]; j <= N; j++) 
        {
            if (dp[j - sizes[i]] != 999999999) 
            {
                if (dp[j] < dp[j - sizes[i]] + 1) 
                     dp[j] = dp[j];
                else 
                    dp[j] = dp[j - sizes[i]] + 1;
            }
        }
    }
 
    int result = dp[N];
    free(dp);
 
    if (result == 999999999) return -1;
    else return result;
}
 
// MAIN FUNCTION
int main() {
    int N, M;
 
    // INPUT
    scanf("%d", &N);
    scanf("%d", &M);
    int *sizes = (int *)malloc(M * sizeof(int));
 
    for (int i = 0; i < M; i++) 
        scanf("%d", &sizes[i]);
    
 
    // PROCESS
    qsort(sizes, M, sizeof(int), qsort_aux); // O(M * log M)
 
    // OUTPUT
    printf("%d\n", calculate(N, sizes, M));
 
    free(sizes);
 
    return 0;
}