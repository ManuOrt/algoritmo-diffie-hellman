#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isNumeroPrimo(int numero);
int mod_exp(int b, int e, int p);
int getNumeroPrimo();

// Exponenciación modular eficiente
int mod_exp(int b, int e, int p) {
    int i, x, power;
    x = 1;
    power = b % p;
    for (i = 0; i < 8 * sizeof(int); i++) {
        if (e & 1) {
            x = (x * power) % p;
        }
        e >>= 1;
        power = (power * power) % p;
    }   
    return x;
}

int getNumeroPrimo(){
    int numero_primo = 1;
    while (isNumeroPrimo(numero_primo) == 0)
    {
        printf("Introduce un número primo: ");
        scanf("%d", &numero_primo);
    }

    return numero_primo;
}

/* int getRaizPrimitiva(){
   return 1;
} */

int isNumeroPrimo(int numero){
    // Comprueba si el número es primo.
    if(numero < 2) {
        return 0;
    }
    // Comprueba si el número es divisible por algún número desde 2 hasta la raíz cuadrada del número.
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            printf("El número %d no es primo.\n", numero);
            return 0; 
        }
    }
    printf("El número %d es primo.\n", numero);
    return 1;
}

/* int isRaizPrimitiva(int numero_primo, int raiz_primitiva, int modulo){
    return 1;
} */

int main() {
    int p = getNumeroPrimo();
    int r = 6;
    int x, X, Y, K;

    srand(time(NULL));
    x = rand() % (p - 2) + 1;
    X = mod_exp(r, x, p);

    printf("Send the number X: %d to your partner.\n", X);

    printf("Enter the Y number that your partner has sent you: ");
    scanf("%d", &Y);

    K = mod_exp(Y, x, p);
    printf("The shared secret key is: %d\n", K);

    // Evita que la consola se cierre de inmediato
    printf("Press ENTER to exit...");
    getchar(); // para limpiar el buffer después de scanf
    getchar(); // para esperar ENTER

    return 0;
}
