int printf(const char *restrict s, ...);
//tanto este archivo como el anterior pueden compilar, ensamblar y vincular, generando el ejecutable.
//Ya que el compilador no permitia hacer nada de eso si no estaba printf bien declarado y la llave final "}".
int main(void)
{
    int i = 42;
    printf("La respuesta es %d\n");
}