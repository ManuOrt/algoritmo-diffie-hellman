#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de funciones en snake_case
int es_numero_primo(int numero);
int mod_exp(int b, int e, int p);
int obtener_numero_primo();
void intercambio_claves_diffie_hellman(int p, int r, int x, int X, int K, int Y);
void realizar_intercambio_clave();
void realizar_intercambio_clave_estatico();
void mostrar_menu();
void mostrar_creditos();
int es_raiz_primitiva(int numero_primo, int raiz_primitiva);
int obtener_raiz_primitiva(int numero_primo);

// Exponenciación modular eficiente
int mod_exp(int b, int e, int p) {
    int i, x, power;
    x = 1;
    // Calcula b mod p para usar como base inicial
    power = b % p;
    for (i = 0; i < 8 * sizeof(int); i++) {
        if (e & 1) {
            // Multiplica el resultado por la potencia actual y aplica el módulo
            x = (x * power) % p;
        }
        e >>= 1;
        power = (power * power) % p;
    }
    return x;
}

// Solicita al usuario un número primo mayor que 1
int obtener_numero_primo() {
    int numero_primo = 1;
    // Solicita al usuario un número primo mayor que 1
    while (numero_primo <= 1 || es_numero_primo(numero_primo) == 0) {
        printf("Introduce un número primo mayor que 1: ");
        scanf("%d", &numero_primo);
        // Verifica si el numero primo es mayor que 1
        if (numero_primo <= 1) {
            printf("El número debe ser mayor que 1.\n");
        }
    }
    return numero_primo;
}

// Verifica si un número es primo
int es_numero_primo(int numero) {
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

// Verifica si una raíz es primitiva para un número primo dado
int es_raiz_primitiva(int numero_primo, int raiz_primitiva) {
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

// Busca y devuelve la primera raíz primitiva encontrada para un número primo
int obtener_raiz_primitiva(int numero_primo) {
    for (int g = 2; g < numero_primo; g++) {
        if (es_raiz_primitiva(numero_primo, g)) {
            // Devuelve la primera raíz primitiva encontrada
            return g; 
        }
    }
    // Si no se encuentra ninguna raíz primitiva (lo cual no debería ocurrir para números primos)
    return -1;
}

// Calcula la clave privada utilizando el algoritmo de intercambio de claves Diffie-Hellman
void intercambio_claves_diffie_hellman(int p, int r, int x, int X, int K, int Y) {
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

// Solicita los parámetros y ejecuta el intercambio de claves Diffie-Hellman
void realizar_intercambio_clave() {
    int p = obtener_numero_primo();
    int r = obtener_raiz_primitiva(p);
    int x, X, Y, K;

    intercambio_claves_diffie_hellman(p, r, x, X, K, Y);
}

// Ejecuta el intercambio de claves Diffie-Hellman con valores estáticos
void realizar_intercambio_clave_estatico() {
    // Número primo estático
    int p = 23; 
    // Raíz primitiva estática
    int r = 5; 
    int x, X, Y, K;

    intercambio_claves_diffie_hellman(p, r, x, X, K, Y);
}

// Muestra los créditos del programa
void mostrar_creditos() {
    printf("\n--- Créditos ---\n");
    printf("Participantes:\n");
    printf("1. Sergio Paredes Medina\n");
    printf("2. Manuel Ortega Martí\n");
    printf("Gracias por usar este programa.\n");
}

// Muestra el menú principal y gestiona la selección del usuario
void mostrar_menu() {
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
                realizar_intercambio_clave();
                break;
            case 2:
                realizar_intercambio_clave_estatico();
                break;
            case 3:
                mostrar_creditos();
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 3);
}

// Función principal del programa
int main() {
    mostrar_menu();
    return 0;
}