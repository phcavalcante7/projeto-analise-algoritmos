#include <stdio.h>
 
long int contar_bits(long int n) // Função para contar os bits=1 de 0 até n
{ 
    long int total_bits_um = 0;
    long int val_bit_atual = 1;
 
    while (val_bit_atual <= n)  // val_bit_atual = 2 ^ posicao_bit (0,1,2,...)
    {
        long int pares = (n + 1) / (val_bit_atual * 2); // como sempre há um padrão de repetição entre os pares do bit_atual, vamos calcular quantos pares nós temos
        total_bits_um += pares * val_bit_atual;
        
        // agora precisamos incrementar os que não estão em pares
        long int resto_pares = (n + 1) % (val_bit_atual * 2); 
        
        if (resto_pares > val_bit_atual) // adiciona a diferença em 'total_bits_um' caso resto_pares > 2^bit_atual
            total_bits_um += resto_pares - val_bit_atual;
        
        
        val_bit_atual *= 2;
    }
 
    return total_bits_um;
}
 
long int diferenca_x_y(long int inicio, long int fim) // Função para contar de 0 até fim e subtrair os que não pertencem ao intervalo
{
    long int total_fim = contar_bits(fim);
    long int total_inicio = contar_bits(inicio - 1); // -1 pra não contar o do intervalo fechado
    return total_fim - total_inicio;
}
 
// ** MAIN ** 
int main() {
    // input
    long int x, y;
    scanf("%ld %ld", &x, &y);
 
    // output
    printf("%ld\n", diferenca_x_y(x, y));
 
    return 0;
}