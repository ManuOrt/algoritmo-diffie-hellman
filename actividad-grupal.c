#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {
    int p = 761;
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
