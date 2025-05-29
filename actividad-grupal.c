#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isNumeroPrimo(int numero);
int mod_exp(int b, int e, int p);
int getNumeroPrimo();
void intercambioClavesDiffieHellman(int p, int r, int x, int X, int K, int Y);
void realizarIntercambioClave();
void realizarIntercambioClaveEstatico();
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
    // Solicita al usuario un número primo mayor que 1
    while (numero_primo <= 1 || isNumeroPrimo(numero_primo) == 0) {
        printf("Introduce un número primo mayor que 1: ");
        scanf("%d", &numero_primo);
        // Verifica si el numero primo es mayor que 1
        if (numero_primo <= 1) {
            printf("El número debe ser mayor que 1.\n");
        }
    }
    return numero_primo;
}

int isNumeroPrimo(int numero){
    // Si el número es menor que 2, no es primo
    if(numero < 2) {
        return 0;
    }
    // Verifica si el número es divisible por algún número desde 2 hasta la raíz cuadrada del número
    for (int i = 2; i * i <= numero; i++) {
        // Si el número es divisible por i, no es primo
        if (numero % i == 0) {
            printf("El número %d no es primo.\n", numero);
            return 0;
        }
    }
    printf("El número %d es primo.\n", numero);
    return 1;
}

int isRaizPrimitiva(int numero_primo, int raiz_primitiva) {
    // φ(p) = p - 1 para números primos
    int phi = numero_primo - 1; 
    int usados[phi];
    // Inicializa el array usados para marcar los valores generados
    for (int i = 0; i < phi; i++) {
        usados[i] = 0;
    }
    // Verifica si la raíz primitiva es válida
    for (int i = 1; i <= phi; i++) {
        int valor = mod_exp(raiz_primitiva, i, numero_primo);
        if (usados[valor - 1] == 1) {
            // Si se repite un valor, no es raíz primitiva
            return 0; 
        }
        usados[valor - 1] = 1;
    }
    // Si genera todos los valores únicos, es raíz primitiva
    return 1; 
}

int getRaizPrimitiva(int numero_primo) {
    for (int g = 2; g < numero_primo; g++) {
        if (isRaizPrimitiva(numero_primo, g)) {
            // Devuelve la primera raíz primitiva encontrada
            return g; 
        }
    }
    // Si no se encuentra ninguna raíz primitiva (lo cual no debería ocurrir para números primos)
    return -1;
}

void intercambioClavesDiffieHellman(int p, int r, int x, int X, int K, int Y) {
    srand(time(NULL));
    x = rand() % (p - 2) + 1;
    X = mod_exp(r, x, p);

    printf("Enviar el número: %d a tu compañero.\n", X);

    printf("Introduce el número que te ha compartido tu compañero: ");
    scanf("%d", &Y);

    K = mod_exp(Y, x, p);
    printf("La clave privada es: %d\n", K);

    printf("Presiona una tecla para volver...");
    getchar();
    getchar();
}

void realizarIntercambioClave() {
    int p = getNumeroPrimo();
    int r = getRaizPrimitiva(p);
    int x, X, Y, K;

    intercambioClavesDiffieHellman(p, r, x, X, K, Y);
}

void realizarIntercambioClaveEstatico() {
    // Número primo estático
    int p = 23; 
    // Raíz primitiva estática
    int r = 5; 
    int x, X, Y, K;

    intercambioClavesDiffieHellman(p, r, x, X, K, Y);
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
        printf("2. Realizar intercambio con valores estáticos\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                realizarIntercambioClave();
                break;
            case 2:
                realizarIntercambioClaveEstatico();
                break;
            case 3:
                mostrarCreditos();
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 3);
}

int main() {
    mostrarMenu();
    return 0;
}