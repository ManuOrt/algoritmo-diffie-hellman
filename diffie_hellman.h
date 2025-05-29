#ifndef DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_H

int isNumeroPrimo(int numero);
int mod_exp(int base, int exponente, int modulo);
int getNumeroPrimo();
int isRaizPrimitiva(int numero_primo, int raiz_primitiva);
int getRaizPrimitiva(int numero_primo);

void intercambioClavesDiffieHellman(int p, int r);
void realizarIntercambioClave();
void realizarIntercambioClaveEstatico();

#endif // DIFFIE_HELLMAN_H
