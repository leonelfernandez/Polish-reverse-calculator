#include "operador.h"

bool es_operador(char* string) {
    bool operador;
    if (strcmp(string, "+") == 0) operador =  true;
    else if (strcmp(string, "-") == 0) operador = true;
    else if (strcmp(string, "*") == 0) operador =  true;
    else if (strcmp(string, "/") == 0) operador =  true;
    else if (strcmp(string, "^") == 0) operador =  true;
    else if (strcmp(string, "sqrt") == 0) operador = true;  
    else if (strcmp(string, "log") == 0) operador = true;
    else if (strcmp(string, "?") == 0) operador = true;
    else {
        operador = false;
    }
    return operador;
}

int es_digito(char* string) {
    
    if (es_operador(string)) return 0;

    for (int i = 0; string[i]; i++) {
        if (isdigit(string[i]) || string[i] == '-') {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}    

void substr_index(char s[], char sub[], int p, int l) {
   int c = 0;
    while (c < l) {
      sub[c] = s[p+c];
      c++;
   }
   sub[c] = '\0';
}

char* remover_salto(char* string) {
    char* res = calloc(sizeof(char) ,2 * strlen(string) + 1);
    if(strstr(string, "\n") != NULL) {
        substr_index(string, res, 0, (int)strlen(string) - 1);
        res[strlen(string) - 1] = '\0';
        return res;
    } else {
        return strcpy(res, string);
    }

}
