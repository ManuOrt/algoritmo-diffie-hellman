#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isNumeroPrimo(int numero);
int mod_exp(int b, int e, int p);
int getNumeroPrimo();
void realizarIntercambioClave();
void mostrarMenu();
void mostrarCreditos();
int isNumeroPrimo(int numero);
int isRaizPrimitiva(int numero_primo, int raiz_primitiva);
int getRaizPrimitiva(int numero_primo);

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
    while (numero_primo <= 1 || isNumeroPrimo(numero_primo) == 0) {
        printf("Introduce un número primo mayor que 1: ");
        scanf("%d", &numero_primo);
        if (numero_primo <= 1) {
            printf("El número debe ser mayor que 1.\n");
        }
    }
    return numero_primo;
}

int isNumeroPrimo(int numero){
    if(numero < 2) {
        return 0;
    }
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            printf("El número %d no es primo.\n", numero);
            return 0;
        }
    }
    printf("El número %d es primo.\n", numero);
    return 1;
}

int isRaizPrimitiva(int numero_primo, int raiz_primitiva) {
    int phi = numero_primo - 1; // φ(p) = p - 1 para números primos
    int usados[phi];
    for (int i = 0; i < phi; i++) {
        usados[i] = 0;
    }

    for (int i = 1; i <= phi; i++) {
        int valor = mod_exp(raiz_primitiva, i, numero_primo);
        if (usados[valor - 1] == 1) {
            return 0; // Si se repite un valor, no es raíz primitiva
        }
        usados[valor - 1] = 1;
    }

    return 1; // Si genera todos los valores únicos, es raíz primitiva
}

int getRaizPrimitiva(int numero_primo) {
    for (int g = 2; g < numero_primo; g++) {
        if (isRaizPrimitiva(numero_primo, g)) {
            return g; // Devuelve la primera raíz primitiva encontrada
        }
    }
    return -1; // Si no se encuentra ninguna raíz primitiva (lo cual no debería ocurrir para números primos)
}

void realizarIntercambioClave() {
    int p = getNumeroPrimo();
    int r = getRaizPrimitiva(p);
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
}

void mostrarCreditos() {
    printf("\n--- Créditos ---\n");
    printf("Participantes:\n");
    printf("1. Sergio Paredes Medina\n");
    printf("2. Manuel Ortega Martí\n");
    printf("Gracias por usar este programa.\n");
}

void mostrarMenu() {
    int opcion;

    do {
        printf("\n--- Menú ---\n");
        printf("1. Realizar intercambio de claves\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                realizarIntercambioClave();
                break;
            case 2:
                mostrarCreditos();
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 2);
}

int main() {
    mostrarMenu();
    return 0;
}