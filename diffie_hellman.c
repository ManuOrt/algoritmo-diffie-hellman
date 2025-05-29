#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diffie_hellman.h"
#include "utilidades.h"

int mod_exp(int base, int exponente, int modulo) {
    int resultado = 1;
    base = base % modulo;
    while (exponente > 0) {
        if (exponente % 2 == 1) {
            resultado = (resultado * base) % modulo;
        }
        exponente = exponente >> 1;
        base = (base * base) % modulo;
    }
    return resultado;
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

void intercambioClavesDiffieHellman(int p, int r) {
    int x, X, Y, K;
    x = rand() % (p - 2) + 1;
    X = mod_exp(r, x, p);

    printf("Enviar el número: %d a tu compañero.\n", X);

    do {
        printf("Introduce el número que te ha compartido tu compañero (entre 1 y %d): ", p - 1);
        scanf("%d", &Y);
        if (Y <= 0 || Y >= p) {
            printf(" Valor inválido. Debe estar entre 1 y %d.\n", p - 1);
        }
    } while (Y <= 0 || Y >= p);

    K = mod_exp(Y, x, p);
    printf("La clave privada es: %d\n", K);

    esperaUsuario();
}

void realizarIntercambioClave() {
    int p = getNumeroPrimo();
    int r = getRaizPrimitiva(p);


    int x, X, Y, K;

    intercambioClavesDiffieHellman(p, r);
}


void realizarIntercambioClaveEstatico() {
    // Número primo estático
    int p = 23;
    // Raíz primitiva estática
    int r = 5;
    int x, X, Y, K;

    intercambioClavesDiffieHellman(p, r);
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

