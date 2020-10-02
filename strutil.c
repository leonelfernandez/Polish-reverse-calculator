#include "strutil.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

char *substr(const char *str, size_t n) {
    char* resultado = malloc(n * sizeof(char) + 1); // + 1 por el '\0'
    if (resultado == NULL) return NULL;
    strncpy(resultado, str, n);
    resultado[n] = '\0';
    return resultado;
}

//funcion aux para conocer la longitud de la una palabra a partir de un inicio

size_t long_palabra(const char* string, size_t inicio, char sep) {
    size_t len = 0, i = inicio;
    while (string[i] != sep && string[i] != '\0') {
        len++;
        i++;
    }
    return len;
}

char **split(const char *str, char sep) {
    size_t len = strlen(str);
    size_t cantidad_palabras = 1;
    size_t contador = 0;
    
    for (int i = 0; i < len; i++) {
        if (str[i] == sep) cantidad_palabras ++;
    }
    size_t* inicios = malloc(sizeof(size_t) * cantidad_palabras);
    if (inicios == NULL) return NULL;
    inicios[0] = 0; //EL primero va a tener que ser 0 ya que ahi arranca la primera cadena
    for (size_t i = 0; i < len; i++) {        
        if (str[i] == sep) {
            contador++;
            inicios[contador] = i + 1;    
        }    
    }
    char** res = malloc(sizeof(char*) * (cantidad_palabras + 1));
    if (res == NULL) return NULL;
    for (size_t i = 0; i < cantidad_palabras; i++){
        contador = long_palabra(str, inicios[i], sep);
        res[i] = substr(&str[inicios[i]], contador);
    }
    free(inicios);
    res[cantidad_palabras] = NULL;
    return res;
}

char* concatenar(char* dest, char* src) {
    while (*dest) dest++;
    while ((*dest++ = *src++));
    return --dest;
}

char *join(char **strv, char sep) {
    size_t len_total = 0;
    int j = 0;
    size_t cant_palabras= 0;
    size_t cant_sep = 0;
    char* res;
    if (!strv) {
        res = calloc(sizeof(char), 1);
        res[0] = '\0';
        return res;
    }
    while (strv[j]) {
        len_total += strlen(strv[j]);
        j++;
        cant_palabras ++;
    }
    if (cant_palabras > 0) {
    cant_sep = cant_palabras - 1;
    }
    res = calloc(sizeof(char) , len_total + cant_sep + 1);
    
    if (res == NULL) return NULL;
    char* separador = calloc(sizeof(char), 2);
    separador[0] = sep;
    separador[1] = '\0';
    char* res_actual = res;
    for (int i = 0; i < cant_palabras; i++) {
        if (i == cant_palabras - 1) {
            concatenar(res_actual, strv[i]);
            res_actual += strlen(strv[i]);
        } else {
            concatenar(res_actual, strv[i]);
            res_actual += strlen(strv[i]);
            
            if (sep != '\0'){
                concatenar(res_actual, separador);
                res_actual ++;
            }
            
        }
        
    }
    free(separador);
    return res;
}

void free_strv(char *strv[]) {
    int i = 0;
    while (strv[i]) {
        free(strv[i]);
        i++;
    }
    free(strv);
}



