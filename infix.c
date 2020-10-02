#include "infix.h"

cola_t* linea_valida(char* linea) {
    size_t contador = 0;
    size_t inicio = 0;
    cola_t* cola = cola_crear();
    for (size_t i = 0; linea[i]; i++) {
        
        if (linea[i] == ' ') {
            continue;
        } 
        if (!isdigit(linea[i]) && contador == 0) {
            cola_encolar(cola, substr(&linea[i], 1));
        } 
        if (!isdigit(linea[i]) && contador > 0) {
            cola_encolar(cola, substr(&linea[inicio], contador));               
            cola_encolar(cola, substr(&linea[i], 1));
            contador = 0;
        }
        if (isdigit(linea[i])) {
            if (contador == 0) inicio = i;
            contador++;
        }
    }
    if (contador > 0) {
            cola_encolar(cola, substr(&linea[inicio], contador));
    }
    return cola;
}


bool es_precedente(char* operador_1, char* operador_2) {
    if ((strcmp(operador_1, "^") == 0) && ((strcmp(operador_2, "/") == 0) ||
    (strcmp(operador_2, "*") == 0) || (strcmp(operador_2, "+") == 0) ||
     (strcmp(operador_2, "-") == 0))) {
        return true;
    } else if ((strcmp(operador_1, "/") == 0 || strcmp(operador_1, "*") == 0) &&
    (strcmp(operador_2, "+") == 0 || strcmp(operador_2, "-") == 0)) {
        return true;
    } else {
    return false;
    }
}

bool igual_precedencia (char* operador, char* operador_2) {
    if ((strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0) &&
     (strcmp(operador_2, "+") == 0 || strcmp(operador_2, "-") == 0)) {
        return true;
    } else if ((strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0) &&
     (strcmp(operador_2, "*") == 0 || strcmp(operador_2, "/") == 0)) {
        return true;
    } else if ((strcmp(operador, "^") == 0) && (strcmp(operador_2, "^") == 0)) {
        return true;
    } else {
        return false;
    }
    
}

bool es_parentesis_izquierdo(char * operador) {
    
    return (strcmp(operador, "(") == 0);
}

bool es_parentesis_derecho(char* operador) {
    return (strcmp(operador, ")") == 0);
}

bool asociatividad_izquierda(char* operador) {
    return (strcmp(operador, "^") != 0); 
}

size_t longitud_linea(cola_t* cola) {
    size_t longitud = 0;
    cola_t* cola_aux = cola_crear();
    while (!cola_esta_vacia(cola)) {
        char* palabra = (char*)cola_desencolar(cola);
        longitud += strlen(palabra);
        cola_encolar(cola_aux, palabra);

    }
    while (!cola_esta_vacia(cola_aux)) {
        cola_encolar(cola, cola_desencolar(cola_aux));
    }
    cola_destruir(cola_aux, NULL);
    return longitud * 2 + 1;  //Considero espacios
}


void criterio_encolado(cola_t* cola, cola_t* cola_final, pila_t* pila) {
    char* actual = (char*)cola_desencolar(cola);
        if (es_digito(actual)) {
            cola_encolar(cola_final, actual);
        } else if (es_operador(actual)) {
            while ((pila_ver_tope(pila) != NULL && es_operador((char*)pila_ver_tope(pila))) &&
            ((es_precedente((char*)pila_ver_tope(pila), actual)) ||
            (igual_precedencia((char*)pila_ver_tope(pila), actual) && 
            asociatividad_izquierda((char*)pila_ver_tope(pila)))) &&
            (!es_parentesis_izquierdo((char*)pila_ver_tope(pila)))) {
                cola_encolar(cola_final, pila_desapilar(pila));
            }
            pila_apilar(pila, actual);

        }else if (es_parentesis_izquierdo(actual)) {
            pila_apilar(pila, actual);
        } else if (es_parentesis_derecho(actual)) {
            while (!es_parentesis_izquierdo((char*)pila_ver_tope(pila))) {
                cola_encolar(cola_final, pila_desapilar(pila));
            }
            if (es_parentesis_izquierdo((char*)pila_ver_tope(pila))) {
                free(pila_desapilar(pila));
            }
            free(actual);
        }
}

char* infix(cola_t* cola) {
    cola_t* cola_final = cola_crear();
    pila_t* pila = pila_crear();
    size_t cantidad = longitud_linea(cola);
    
    while (!cola_esta_vacia(cola)) {
        criterio_encolado(cola, cola_final, pila);
    }
    if (cola_esta_vacia(cola)) {
        while (!pila_esta_vacia(pila)) {
            cola_encolar(cola_final, pila_desapilar(pila));
        }
    }
    char* resultado = (char*)calloc(sizeof(char) , cantidad);
    while (!cola_esta_vacia(cola_final)) {
        char* fragmento_linea = (char*)cola_desencolar(cola_final);
        strcat(resultado , fragmento_linea);
        strcat(resultado ," ");
        free(fragmento_linea);
    }
    pila_destruir(pila);
    cola_destruir(cola_final, NULL);
    return resultado;
 }

int main() {
    char* resultado;
    size_t n = 0;
    char* linea = NULL;
    while((getline(&linea, &n, stdin)) != EOF) {
        char* linea_s = remover_salto(linea);
        cola_t* cola = linea_valida(linea_s);
        resultado = infix(cola);
        printf("%s\n", resultado);
        free(resultado);
        cola_destruir(cola, NULL);
        free(linea_s);
    }
    
    free(linea);
    return 0;
}
