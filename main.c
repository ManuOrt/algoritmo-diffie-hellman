#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diffie_hellman.h"
#include "utilidades.h"

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
            esperaUsuario();
        }
    } while (opcion != 3);
}

int main() {
    srand(time(NULL));
    mostrarMenu();
    return 0;
}
