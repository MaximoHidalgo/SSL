#include <stdio.h>
#include <stdlib.h>

#ifdef IMPLEMENTACION_1

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

typedef struct {
    Estado proximoEstado;
    bool escribirChar;
} Transicion;

Transicion tablaDeTransiciones[NUM_ESTADOS][256];

void inicializarTabla() {
    for(int c = 0; c < 256; c++) {
        tablaDeTransicion[INICIAL][c] = (Transicion){INICIAL, true}; 
    }

    tablaDeTransicion[INICIAL]['/'] = (Transicion){BARRA, true};
    tablaDeTransicion[INICIAL]['"'] = (Transicion){CADENA, true};
    tablaDeTransicion[INICIAL]['\''] = (Transicion){CARACTER, true};
    
    tablaDeTransicion[BARRA]['/'] = (Transicion){COMENTARIO_SIMPLE, false};
    tablaDeTransicion[BARRA]['*'] = (Transicion){COMENTARIO_MULTIPLE, false};
    for(int c = 0; c < 256; c++) {
        if(c != '/' && != '*') {
            tablaDeTransicion[BARRA][c] = (Transicion){INICIAL, true};
        }
    }

    for(int c = 0; c < 256; c++){
        tablaDeTransicion[COMENTARIO_SIMPLE][C] = (Transicion){COMENTARIO_SIMPLE, false};
    }
    tablaDeTransacion[COMENTARIO_SIMPLE]['\n'] = (Transicion){INICIAL, true};

    for(int c = 0; c < 256; c++) {
        tablaDeTransicion[COMENTARIO_MULTIPLE][c] = (Transicion){COMENTARIO_MULTIPLE, false};
    }
    tablaDeTransacion[COMENTARIO_MULTIPLE]['*'] = (transicion){FIN_COMENTARIO_MULTIPLE, false};
    
    for(int c = 0; c < 256; c++) {
        tablaDeTransicion[FIN_COMENTARIO_MULTIPLE][c] = (Transicion){COMENTARIO_MULTIPLE, false};
    }
    tablaDeTransacion[FIN_COMENTARIO_MULTIPLE]['/'] = (transicion){INICIAL, false};

    for(int c = 0; c < 256; c++) {
        tablaDeTransicion[CADENA][c] = (Transicion){CADENA, true};
    }
    tablaDeTransicion[CADENA]['"'] = (Transicion){INICIAL, true};
    tablaDeTransicion[CADENA]['\\'] = (Transicion){ESCAPE_EN_CADENA, true};

    for (int c = 0; c < 256; c++) {
        tablaDeTransicion[ESCAPE_EN_CADENA][c] = (Transicion){CADENA, true};
    }
        
    for (int c = 0; c < 256; c++) {
        tablaDeTransicion[CARACTER][c] = (Transicion){CARACTER, true};
    }
    tablaDeTransicion[CARACTER]['\''] = (Transicion){INCIAL, true};
    tablaDeTransicion[CARACTER]['\\'] = (Transicion){ESCAPE_EN_CARCATER, true};
    
     for (int c = 0; c < 256; c++) {
        tablaDeTransicion[ESCAPE_EN_CARCTER][c] = (Transicion){CARCATER, true};
    }
}

int main() {
    inicializarTabla();
    Estado estadoActual = INCIAL;
    int caracter;

    while((int caracter = getchar()) != EOF) {
        unsigned char uCaracter = (unsigned char)caracter;
        Transicion trans = tablaDeTransicion[estadoActual][uCaracter];

        estadoActual = trans.proximoEstado;
        if(trans.escribirChar) {
            putchar(caracter);
        }
    }

    retur 0;
}

#else 

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
