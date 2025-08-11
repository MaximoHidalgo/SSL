#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef enum {
    INICIAL,
    BARRA,
    COMENTARIO_SIMPLE,
    COMENTARIO_MULTIPLE,
    FIN_COMENTARIO_MULTIPLE,
    CADENA,
    ESCAPE_EN_CADENA,
    CARACTER,
    ESCAPE_EN_CARACTER,
    NUM_ESTADOS
} Estado;

#ifdef IMPLEMENTACION_1

typedef struct {
    Estado proximoEstado;
    bool escribirChar;
} Transicion;

Transicion tablaDeTransiciones[NUM_ESTADOS][256];

void inicializarTabla() {
    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[INICIAL][c] = (Transicion){INICIAL, true};
    }

    tablaDeTransiciones[INICIAL]['/'] = (Transicion){BARRA, false};
    tablaDeTransiciones[INICIAL]['"'] = (Transicion){CADENA, true};
    tablaDeTransiciones[INICIAL]['\''] = (Transicion){CARACTER, true};

    tablaDeTransiciones[BARRA]['/'] = (Transicion){COMENTARIO_SIMPLE, false};
    tablaDeTransiciones[BARRA]['*'] = (Transicion){COMENTARIO_MULTIPLE, false};
    for(int c = 0; c < 256; c++) {
        if(c != '/' && c != '*') {
            tablaDeTransiciones[BARRA][c] = (Transicion){INICIAL, true};
        }
    }

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[COMENTARIO_SIMPLE][c] = (Transicion){COMENTARIO_SIMPLE, false};
    }
    tablaDeTransiciones[COMENTARIO_SIMPLE]['\n'] = (Transicion){INICIAL, true};

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[COMENTARIO_MULTIPLE][c] = (Transicion){COMENTARIO_MULTIPLE, false};
    }
    tablaDeTransiciones[COMENTARIO_MULTIPLE]['*'] = (Transicion){FIN_COMENTARIO_MULTIPLE, false};

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[FIN_COMENTARIO_MULTIPLE][c] = (Transicion){COMENTARIO_MULTIPLE, false};
    }
    tablaDeTransiciones[FIN_COMENTARIO_MULTIPLE]['/'] = (Transicion){INICIAL, false};

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[CADENA][c] = (Transicion){CADENA, true};
    }
    tablaDeTransiciones[CADENA]['"'] = (Transicion){INICIAL, true};
    tablaDeTransiciones[CADENA]['\\'] = (Transicion){ESCAPE_EN_CADENA, true};

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[ESCAPE_EN_CADENA][c] = (Transicion){CADENA, true};
    }

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[CARACTER][c] = (Transicion){CARACTER, true};
    }
    tablaDeTransiciones[CARACTER]['\''] = (Transicion){INICIAL, true};
    tablaDeTransiciones[CARACTER]['\\'] = (Transicion){ESCAPE_EN_CARACTER, true};

    for(int c = 0; c < 256; c++) {
        tablaDeTransiciones[ESCAPE_EN_CARACTER][c] = (Transicion){CARACTER, true};
    }
}

int main() {
    inicializarTabla();
    Estado estadoActual = INICIAL;
    int caracter;

    while((caracter = getchar()) != EOF) {
        unsigned char uCaracter = (unsigned char)caracter;

         if (estadoActual == BARRA && (caracter != '/' && caracter != '*')) {
            putchar('/');  
        }

        Transicion trans = tablaDeTransiciones[estadoActual][uCaracter];
        estadoActual = trans.proximoEstado;

        if(trans.escribirChar) {
            putchar(caracter);
        }
    }

    if (estadoActual == BARRA) {
        putchar('/');
    }

    return 0;
}

#else


int main(void){
    int c;

    goto INICIAL;

    INICIAL:
        c = getchar();
        if (c == EOF) goto END;
        if (c == '/') goto BARRA;
        if (c == '"') {
            putchar(c);
            goto CADENA;
        }
        if (c == '\'') {
            putchar(c);
            goto CARACTER;
        }
        putchar(c);
        goto INICIAL;

    BARRA:
        c = getchar();
        if (c == '/') goto COMENTARIO_SIMPLE;
        if (c == '*') goto COMENTARIO_MULTIPLE;
        putchar('/');
        if (c == EOF) goto END;
        putchar(c);
        goto INICIAL;

    COMENTARIO_SIMPLE:
        c = getchar();
        if (c == EOF) goto END;
        if (c == '\n') { putchar(c); goto INICIAL; }
        goto COMENTARIO_SIMPLE;

    COMENTARIO_MULTIPLE:
        c = getchar();
        if (c == EOF) goto END;
        if (c == '*') goto FIN_COMENTARIO_MULTIPLE;
        goto COMENTARIO_MULTIPLE;

    FIN_COMENTARIO_MULTIPLE:
        c = getchar();
        if (c == EOF) goto END;
        if (c == '/') goto INICIAL;
        if (c == '*') goto FIN_COMENTARIO_MULTIPLE;
        goto COMENTARIO_MULTIPLE;

    CADENA:
        c = getchar();
        if (c == EOF) goto END;
        putchar(c);
        if (c == '\\') goto ESCAPE_EN_CADENA;
        if (c == '"') goto INICIAL;
        goto CADENA;

    ESCAPE_EN_CADENA:
        c = getchar();
        if (c == EOF) goto END;
        putchar(c);
        goto CADENA;

    CARACTER:
        c = getchar();
        if (c == EOF) goto END;
        putchar(c);
        if (c == '\\') goto ESCAPE_EN_CARACTER;
        if (c == '\'') goto INICIAL;
        goto CARACTER;

    ESCAPE_EN_CARACTER:
        c = getchar();
        if (c == EOF) goto END;
        putchar(c);
        goto CARACTER;

    END:
        return 0;

}

#endif 