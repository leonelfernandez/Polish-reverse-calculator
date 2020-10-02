#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cola.h"
#include "pila.h"
#include <ctype.h>
#include "dc.h"
#include <math.h>
#include "operador.h"

bool es_precedente(char* operador_1, char* operador_2);

bool igual_precedencia (char* operador, char* operador_2);

bool es_parentesis_izquierdo(char * operador);

bool es_parentesis_derecho(char* operador);

char* infix(cola_t* cola);

void imprimir_linea(char** linea);
