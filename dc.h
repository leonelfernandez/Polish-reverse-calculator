#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "pila.h"
#include "strutil.h"
#include "cola.h"
#include "operador.h"

void substr_index(char s[], char sub[], int p, int l);

char* remover_salto(char* string);

cola_t* agregar_a_cola(char** linea);

size_t cantidad_campos(cola_t* cola);

bool es_operador(char* string);

int es_digito(char* string);

bool calculadora_polaca(cola_t* cola, size_t n, long* resultado);