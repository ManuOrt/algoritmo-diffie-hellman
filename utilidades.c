//
// Created by Arnau Erta on 29/5/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"

void esperaUsuario() {
    printf("Presiona ENTER para continuar...");
    while (getchar() != '\n');
    getchar();
}