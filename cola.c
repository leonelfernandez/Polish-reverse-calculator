#include "cola.h"
#include <stdlib.h>
#include <stdio.h>



//Implementacion struct cola y nodo
struct nodo {
    void* dato;
    struct nodo *siguiente;
};

struct cola {
    struct nodo* prim;
    struct nodo* ult;
};

//Primitiva para crear nodo

struct nodo* crear_nodo(void* dato){
    struct nodo* nodo = malloc(sizeof(struct nodo));
    if (nodo == NULL){
        return NULL;
    }
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return nodo;
}

//Primitivas de la cola

cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if (cola == NULL){
        return NULL;
    }
    cola->prim = NULL;
    cola->ult = NULL;
    
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){
    
    while (cola->prim != NULL){
        struct nodo* nodo_1 = cola->prim;
        if (destruir_dato != NULL){
            destruir_dato(nodo_1->dato);
        }
        
        cola->prim = (cola->prim)->siguiente;
        free(nodo_1);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
    struct nodo* nodo = crear_nodo(valor);
    if (cola_esta_vacia(cola)){
        cola->prim = nodo;
    } else {
        (cola->ult)->siguiente = nodo;
    }   
    cola->ult = nodo;
    return true;
}

void* cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    return (cola->prim)->dato;
}

void* cola_desencolar(cola_t *cola) {
    
    if (cola_esta_vacia(cola)){ //Caso borde 1: Que la cola este vacia
        return NULL;
    }
    void* dato = (cola->prim)->dato;
    struct nodo* aux = cola->prim;
    if (cola->prim == cola->ult) { //Caso borde 2: Que la cola tenga 1 elemento
        cola->prim = NULL;
        cola->ult = NULL;
        
    } else {
        cola->prim = (cola->prim)->siguiente;
    }
    
    free(aux);
    return dato;

}