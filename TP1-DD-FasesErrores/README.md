# 7 Fases de la Traducción y Errores

7.1. Objetivos
Este trabajo tiene como objetivo identificar las fases del proceso de traducción o
Build y los posibles errores asociados a cada fase.
Para lograr esa identificación se ejecutan las fases de traducción una a una, se
detectan y corrigen errores, y se registran las conclusiones en readme.md.
No es un trabajo de desarrollo; es más, el programa que usamos como ejemplo es
simple, similar a hello.c pero con errores que se deben corregir. La complejidad
está en la identificación y comprensión de las etapas y sus productos.

7.2. Temas
• Fases de traducción.
• Preprocesamiento.
• Compilación.
• Ensamblado.
• Vinculación (Link).
• Errores en cada fase.
• Compilación separada.

7.3. Tareas
    1. La primera tarea es investigar las funcionalidades y opciones que su implementación, es decir su compilador, presenta para limitar el inicio y fin de las fases de traducción.
    2. La siguiente tarea es poner en práctica lo que se investigó. Para eso se debe transcribir al readme.md cada comando ejecutado y su resultado o error correspondiente a la siguiente secuencia de pasos. También en readme.md se vuelcan las conclusiones y se resuelven los puntos solicitados. Para claridad, mantener en readme.md la misma numeración de la secuencia de pasos.
7.3.1. Secuencia de Pasos
    Se parte de un archivo fuente que es corregido y refinado en sucesivos pasos. Es importante no saltearse pasos para mantener la correlación, ya que el estado dejado por el paso anterior es necesario para el siguiente.
    1. Preprocesador:
        a. Escribir hello2.c, que es una variante de hello.c
        b. Preprocesar hello2.c, no compilar, y generar hello2.i. Analizar su contenido. ¿Qué conclusiones saca?
        c. Escribir hello3.c, una nueva variante
        d. Investigar e indicar la semántica de la primera línea.
        e. Preprocesar hello3.c, no compilar, y generar hello3.i. Buscar diferencias entre hello3.c y hello3.i.
    2. Compilación
        a. Compilar el resultado y generar hello3.s, no ensamblar.
        b. Corregir solo los errores, no los warnings, en el nuevo archivo hello4.c y empezar de nuevo, generar hello4.s, no ensamblar.
        c. Leer hello4.s, investigar sobre lenguaje ensamblador, e indicar de formar sintética cual es el objetivo de ese código.
        d. Ensamblar hello4.s en hello4.o, no vincular.
    3. Vinculación
        a. Vincular hello4.o con la biblioteca estándar y generar el ejecutable.
        b. Corregir en hello5.c y generar el ejecutable. Solo corregir lo necesario para que vincule.
        c. Ejecutar y analizar el resultado.
    4. Corrección de Bug
        a. Corregir en hello6.c y empezar de nuevo; verificar que funciona como se espera.
    5. Remoción de prototipo
        a. Escribir hello7.c, una nueva variante:
        b. Explicar porqué funciona; para eso, considerar las siguientes preguntas:
            i. ¿Arroja error o warning?
            ii. ¿Qué es un prototipo y de qué maneras se puede generar?
            iii. ¿Qué es una declaración implícita de una función?
            iv. ¿Qué indica la especificación?
            v. ¿Cómo se comportan las principales implementaciones?
            vi. ¿Qué es una función built-in?
            vii.¿Conjeture la razón por la cual gcc se comporta como se comporta? ¿Va realmente contra la especificación?
    6. Compilación Separada: Contratos y Módulos
        a. Escribir studio1.c (sí, studio1, no stdio) y hello8.c.
        b. Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción (i.e., archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.
        c. Responder ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf? Justifique.
        d. Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.
            i. Escribir el contrato en studio.h.
            ii. Escribir hello9.c, un cliente que sí incluye el contrato.
            iii. Escribir studio2.c, el proveedor que sí incluye el contrato.
            iv. Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor.

    Crédito extra:
    Investigue sobre bibliotecas. ¿Qué son? ¿Se pueden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas Desarrolle y utilice la biblioteca studio.


# RESPUESTA PREPROCESADO: 
7.3.1
## b.Al preprocesar el hello2.c, los resultados que tira la terminal son:
        . Se pudo ver el contenido de la biblioteca stdio.h por terminal.
        . Tambien muestra el codigo del archivo hello2.c pero con modificaciones:
        . Elimino el comentario /*medio*/ y tambien el #include <stdio.h> (este lo reemplaza con el contenido del archivo)
        . No se encarga de errores de sintaxis como "prontf" o la falta de "}" para cerrar, ya que el preprocesador no sabe de eso.

 ##    d.La primera linea "int printf(const char *restrict s, ...);" en cuanto a lo semantico de esta linea, se puede desglosar en partes:
        ."int printf": es la declaracion de una funcion que implica que el tipo de dato es "int" y el nombre de esta función es "printf".
        ."const": esto significa que el dato "char" va a llegar al puntero *restrict s, pero no se permite modificar.
        ."restrict": es una keyword (palabra clave) que significa que s es el único puntero que accede a ese bloque de memoria durante la función. Y "s" indica el formato de printf.
        . Esta funcion tiene una cantidad indefinida de argumentos. O sea que es una función variádica.

##     e. hello3.i es: " # 0 "hello3.c" # 0 "<built-in>"  # 0 "<command-line>" # 1 "hello3.c"
        int printf(const char *restrict s, ...);
        int main(void)
        {
            int i = 42;
            prontf("La respuesta es %d\n"); "
        Las diferencias que se encuentran entre el hello3.c y el hello3.i son:
            . La inclusion de numerales como " # 0 "hello3.c" " las cuales son directivas de control del preprocesador (le dicen al compilador de dónde viene cada línea). No cambian el comportamiento del programa, pero sirven para que el compilador sepa qué archivo está leyendo ("hello3.c"), desde qué línea lo esta leyendo y cuándo cambia de archivo.Estas directivas se usan internamente, por ejemplo, para mostrar errores con la línea correcta en el archivo correcto.
            . En cuanto al codigo, no hay modificación en este porque no hay macros ni includes. El contenido real no cambia nada (más allá de esas líneas # de tracking).
            . Sigue sin modificar la sintaxis.

### Crédito extra:
#### Investigue sobre bibliotecas. ¿Qué son? ¿Se pueden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas Desarrolle y utilice la biblioteca studio.
