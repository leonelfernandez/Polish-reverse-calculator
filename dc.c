#include "dc.h"


cola_t* agregar_a_cola(char** linea) {
    
    cola_t* cola = cola_crear();
    int i = 0;
    
    while(linea[i]) {
        if (strcmp(linea[i], " ") == 0 || strcmp(linea[i],"\0") == 0){
            i ++;
            continue;

        } else {
            cola_encolar(cola, linea[i]);
        }
        i ++;

    }

    return cola;
}
size_t cantidad_campos(cola_t* cola) {
    cola_t* cola_aux = cola_crear();
    size_t longitud = 0;
    while(!cola_esta_vacia(cola)) {
        cola_encolar(cola_aux, cola_desencolar(cola));
        longitud++;
    }
    while(!cola_esta_vacia(cola_aux)) {
        cola_encolar(cola, cola_desencolar(cola_aux));
    }
    cola_destruir(cola_aux, NULL);
    return longitud;
}


void free_pila(pila_t* pila) {
    
    while (!pila_esta_vacia(pila)) {
        long* var = (long*)pila_desapilar(pila);
        free(var);
    }
    pila_destruir(pila);
}


bool operatorias(long* ptr_valor_1, long* ptr_valor_2, char* actual, pila_t* pila, long* res_1) {
    long valor_1 = *ptr_valor_1;
    long valor_2 = *ptr_valor_2;
    if (strcmp(actual, "+") == 0) {
        *res_1 = valor_2 + valor_1;
    } else if (strcmp(actual, "-") == 0){ 
        *res_1 = valor_2 - valor_1;
    } else if (strcmp(actual, "*") == 0){
        *res_1 = valor_2 * valor_1;
    } else if (strcmp(actual, "/") == 0) { 
        if (valor_1 != 0) *res_1 = valor_2 / valor_1;
         else {
            return false;
        }
    } else if (strcmp(actual, "^") == 0){ 
        if (valor_1 >= 0) *res_1 = pow(valor_2, valor_1);
        else {
            return false;
        }
                
    } else if (strcmp(actual, "log") == 0) {
        if (valor_1 >= 2) *res_1 = (long)((log(valor_2) / log(valor_1)));
        else {
            return false;
        }
    }
    return true;
}


void operador_ternario(long* ptr_valor_falso, long* ptr_valor_verdadero, long* ptr_valor_booleano, long* res_2) {
    long valor_falso = *ptr_valor_falso;
    long valor_verdadero = *ptr_valor_verdadero;
    long valor_booleano = *ptr_valor_booleano;
    *res_2 = valor_booleano ? valor_verdadero : valor_falso;    
}

void apilar_numeros_iniciales(char* actual, pila_t* pila, char* ptr) {
    long* numero_a_apilar_1 = calloc(sizeof(long*), 1);
    *numero_a_apilar_1 = strtol(actual, &ptr, 10);
    pila_apilar(pila, numero_a_apilar_1);
}

bool casos_error(pila_t* pila, char* actual, int n_apilados) {
    if (!es_operador(actual) && n_apilados < 2) {
        return true;
    } else if (es_operador(actual) && n_apilados < 3 && !strcmp(actual, "?")) {
        return true;
    } else if (es_operador(actual) && n_apilados < 1 && !strcmp(actual, "sqrt")) {
        return true;
    } else if (es_operador(actual) && n_apilados < 2 && (strcmp(actual, "+") || strcmp(actual, "-") ||
        strcmp(actual, "*") || strcmp(actual, "/") || strcmp(actual, "^"))) {
        return true;
    } else if (!es_operador(actual)) {
        return true;
    }
    
    return false;          
}


bool calculadora_polaca(cola_t* cola, size_t n, long* resultado) {
    pila_t* pila = pila_crear();
    if (pila == NULL) return 0;
    int n_apilados = 0;
    int operaciones = 0;
    char ptr;
    int i = 0;
    while (!cola_esta_vacia(cola)) {
       char* actual = (char*)cola_desencolar(cola);
        if (es_digito(actual)) {
            apilar_numeros_iniciales(actual, pila, &ptr);
            n_apilados++; 
        }
        else if(es_operador(actual) && strcmp(actual, "?") && n_apilados >= 2 && strcmp(actual, "sqrt") ) {
            long* ptr_valor_1 = (long*)pila_desapilar(pila);
            long* ptr_valor_2 = (long*)pila_desapilar(pila);
            n_apilados -= 2;
            long res_1 = 0;
            if (operatorias(ptr_valor_1, ptr_valor_2, actual, pila, &res_1)) {
                long* numero_a_apilar_2 = calloc(sizeof(long*), 1); //(ACA 170)
                *numero_a_apilar_2 = res_1;
                pila_apilar(pila, numero_a_apilar_2); 
                free(ptr_valor_1);
                free(ptr_valor_2);
                n_apilados ++;
                operaciones ++;
            } else {
                free(ptr_valor_1);
                free(ptr_valor_2);
                free_pila(pila);
                return false;
            }
        }
        else if(es_operador(actual) && !strcmp(actual, "?") && n_apilados >= 3){
            
            long* ptr_valor_falso = (long*)pila_desapilar(pila);
            long* ptr_valor_verdadero = (long*)pila_desapilar(pila);
            long* ptr_valor_booleano = (long*)pila_desapilar(pila);
            n_apilados -= 3;
            long res_2 = 0;
            operador_ternario(ptr_valor_falso, ptr_valor_verdadero, ptr_valor_booleano, &res_2);
            long* numero_a_apilar_3 = calloc(sizeof(long*), 1); // ACA (194)
            *numero_a_apilar_3 = res_2;
            pila_apilar(pila, numero_a_apilar_3); 
            free(ptr_valor_booleano);
            free(ptr_valor_falso);
            free(ptr_valor_verdadero);
            n_apilados ++;
            operaciones ++;
        
        } else if (es_operador(actual) && !strcmp(actual, "sqrt") && n_apilados >= 1) {
            long* ptr_valor = (long*)pila_desapilar(pila);    
            long valor = *ptr_valor;
            long res_3 = 0;
            if (valor >= 0) res_3 = sqrt(valor);
            else {
                free(ptr_valor);
                free_pila(pila);
                return false;
            }
            long* numero_a_apilar_4 = calloc(sizeof(long), 1); //(ACA 220)
            *numero_a_apilar_4 = res_3;
            pila_apilar(pila, numero_a_apilar_4); 
            free(ptr_valor);
            operaciones ++;
        }
        
        else {
            if (casos_error(pila, actual, n_apilados)) {
                free_pila(pila);
                return false;
            }
        }
        
        i++;       
    }
    
    if ((n_apilados != 1 || ((n_apilados > 1) && operaciones <= 1) || ((n_apilados == 1) && operaciones < 1))) {
        free_pila(pila);
        return false;
    }
    long* var_resultado = (long*)pila_desapilar(pila);
    *resultado = *var_resultado; //ACA ROMPE
    free(var_resultado);
    pila_destruir(pila);
    return true;
}

int main() {
    char** linea_spliteada;
    bool es_valido;
    size_t cant_campos;
    long resultado = 0;
    size_t n = 0;
    char* linea = NULL;
    
    while(getline(&linea, &n, stdin) > 0) {

        char* linea_s = remover_salto(linea); // (ACA)
        linea_spliteada = split(linea_s, ' ');
        cola_t* cola = agregar_a_cola(linea_spliteada);
        cant_campos = cantidad_campos(cola);
        es_valido = calculadora_polaca(cola, cant_campos, &resultado);
        if (es_valido) printf("%ld\n", resultado);
        else {
            printf("ERROR\n");
        }
        cola_destruir(cola, NULL);   // i++;
        free(linea_s);
        free_strv(linea_spliteada);
    }
    free(linea);
    return 0;
 }








