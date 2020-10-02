#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL){
        return NULL;
    }

    pila->datos = malloc(4 * sizeof(void*));
    pila->cantidad = 0;
    pila->capacidad = 4;
    if (pila->datos == NULL) {
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_redimensionar(pila_t *pila, size_t nueva_capacidad) {
    void* datos_nuevo = realloc(pila->datos,  nueva_capacidad * sizeof(void*));
    if (datos_nuevo == NULL) {
        return false;
    }
    pila->datos = datos_nuevo;  
    pila->capacidad = nueva_capacidad;
    return true;
} 

bool pila_apilar(pila_t *pila, void* valor){
    if(pila->capacidad == pila->cantidad){
        pila_redimensionar(pila, pila->capacidad * 2);  
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    if(pila->capacidad > 4 && pila->cantidad*4 <= pila->capacidad){
        pila_redimensionar(pila, pila->capacidad / 2);
        }
    
    void* ultimo_elemento = pila->datos[pila->cantidad - 1];
    pila->cantidad--;
    
    return ultimo_elemento;
}

  


