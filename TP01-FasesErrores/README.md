# TP1 - Fases de la Traducción y Errores
**Equipo N.º 2:** *"Sintax Error"*

---

## 👥 Autores de la resolución:

| Nombre completo                | Legajo     | GitHub                                      |
|-------------------------------|------------|---------------------------------------------|
| Máximo Juan Manuel Hidalgo    | 176.585-1  | [MaximoHidalgo](https://github.com/MaximoHidalgo) |
| Priscila Sboboda              | 215.309-9  | [psboboda](https://github.com/psboboda)     |
| Matias Pretzsch               | 214.029-9  | [MatiasPretzsch](https://github.com/MatiasPretzsch) |
| Juliana Pansowy Furno         | 222.575-0  | [JulianaPansowyFurno](https://github.com/JulianaPansowyFurno) |
| María Florencia Bengoechea    | 213.505-0  | [mbengoechea](https://github.com/mbengoechea) |
| Dylan Oriel Rechusky          | 203.301-0  | [DylanOriel](https://github.com/DylanOriel) |
| Jeremías Boutet               | 208.705-4  | [Jereboutet](https://github.com/Jereboutet) |
| Liam Karol Trepat             | 209.624-9  | [liamkaroltrepat](https://github.com/liamkaroltrepat) |

### 7.1. Objetivos
    Este trabajo tiene como objetivo identificar las fases del proceso de traducción o Build y los posibles 
    errores asociados a cada fase. Para lograr esa identificación se ejecutan las fases de traducción una a una, 
    se detectan y corrigen errores, y se registran las conclusiones en readme.md. No es un trabajo de desarrollo; 
    es más, el programa que usamos como ejemplo es simple, similar a hello.c pero con errores que se deben corregir. 
    La complejidad está en la identificación y comprensión de las etapas y sus productos.

### 7.2. Temas "Fases de traducción":
    1. Preprocesamiento.
    2. Compilación.
    3. Ensamblado.
    4. Vinculación (Link).
    5- Errores en cada fase.
    6. Compilación separada.

### 7.3. Tareas
    1. La primera tarea es investigar las funcionalidades y opciones que su implementación, es decir su compilador, presenta para 
    limitar el inicio y fin de las fases de traducción.
    2. La siguiente tarea es poner en práctica lo que se investigó. Para eso se debe transcribir al readme.md cada comando ejecutado 
    y su resultado o error correspondiente a la siguiente secuencia de pasos. También en readme.md se vuelcan las conclusiones y se 
    resuelven los puntos solicitados. Para claridad, mantener en readme.md la misma numeración de la secuencia de pasos.

### 7.3.1. Secuencia de Pasos
    Se parte de un archivo fuente que es corregido y refinado en sucesivos pasos. Es importante no saltearse pasos para mantener
    la correlación, ya que el estado dejado por el paso anterior es necesario para el siguiente.
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
        b. Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de
        traducción (i.e., archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.
        c. Responder ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf? Justifique.
        d. Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.
            i. Escribir el contrato en studio.h.
            ii. Escribir hello9.c, un cliente que sí incluye el contrato.
            iii. Escribir studio2.c, el proveedor que sí incluye el contrato.
            iv. Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor.
    Crédito extra:
    Investigue sobre bibliotecas. ¿Qué son? ¿Se pueden distribuir? ¿Son portables? 
    ¿Cuáles son sus ventajas y desventajas Desarrolle y utilice la biblioteca studio.


### Respuestas preprocesado: 
7.3.1.

- 1.b. Analizar su contenido. ¿Qué conclusiones saca?:
    Al preprocesar el hello2.c, los resultados que tira la terminal son:
    - Se pudo ver el contenido de la biblioteca stdio.h por terminal.
    - Tambien muestra el codigo del archivo hello2.c pero con modificaciones:
    - Elimino el comentario /*medio*/ y tambien el #include <stdio.h> (este lo reemplaza con el contenido del archivo)
    - No se encarga de errores de sintaxis como "prontf" o la falta de "}" para cerrar, ya que el preprocesador no sabe de eso.

- 1.d.Investigar e indicar la semántica de la primera línea: 
   La primera linea "int printf(const char *restrict s, ...);" en cuanto a lo semantico de esta linea, se puede desglosar en partes:
    - "int printf": es la declaracion de una funcion que implica que el tipo de dato es "int" y el nombre de esta función es "printf".
    - "const": esto significa que el dato "char" va a llegar al puntero *restrict s, pero no se permite modificar.
    - "restrict": es una keyword (palabra clave) que significa que s es el único puntero que accede a ese bloque de memoria durante la función. Y "s" indica el formato de printf.
    - Esta funcion tiene una cantidad indefinida de argumentos. O sea que es una función variádica.

- 1 e. Buscar diferencias entre hello3.c y hello3.i: </p> 
  hello3.i es:
  ```c
  # 0 "hello3.c" # 0 "<built-in>"
  # 0 "<command-line>"
  # 1 "hello3.c"</p> 
        int printf(const char *restrict s, ...); </p> 
        int main(void) </p> 
        {  </p> 
            int i = 42;  </p> 
            prontf("La respuesta es %d\n"); " </p>
  ```
  -   Las diferencias que se encuentran entre el hello3.c y el hello3.i son:
        - La inclusion de numerales como " # 0 "hello3.c" " las cuales son directivas de control del preprocesador (le dicen al compilador de dónde viene cada línea). No cambian el comportamiento               del programa, pero sirven para que el compilador sepa qué archivo está leyendo ("hello3.c"), desde qué línea lo esta leyendo y cuándo cambia de archivo. Estas directivas se usan                        internamente, por ejemplo, para mostrar errores con la línea correcta en el archivo correcto.
        - En cuanto al codigo, no hay modificación en este porque no hay macros ni includes. El contenido real no cambia nada (más allá de esas líneas # de tracking).
        - Sigue sin modificar la sintaxis.

### Respuestas Compilación: 
- 2 c.investigar sobre lenguaje ensamblador, e indicar de formar sintética cual es el objetivo de ese código:
    - El objetivo del código assembler de este programa es declarar e inicializar una variable int i = 42, analiza la función main, llamar a printf("La respuesta es %d\n") y terminar el programa. Imprime "La respuesta es %d\n" sin pasar el valor de %d, pero igual prepara un valor de retorno 0 (return 0) sin que este en el programa.

### Respuestas Vinculación: 
- 3 c. Ejecutar y analizar el resultado: 
    - Tuvimos que generar un hello4.c y un hello5.c corrigiendo del hello3.c los errores de sintaxis de prontf que el compilador pedia que fuera printf y la falta de la llave "}" para finalizar la función. Estos dos errores no permitian a hello3.c (que se corrigen en hello4.c) compilar. Esto sucede por la version del compilador que utilizamos (MSYS2 14.2.0) no permitia compilar hello3.c sin corregir esos 2 errores, pero una vez que se corrigen, hello4.c y hello5.c pueden compilar-emsamblar-vincular, generando desde el hello4.c -> hello4.s -> hello4.o -> hello4.exe; sin tener problemas para generar el programa ejecutable (aunque imprima por pantalla "La respuesta es 770619520" lo cual es incorrecto pragmaticamente). Por esta caracteristica en el compilador hello4.c y hello5.c son iguales.

### Respuestas Corrección de Bug: 
- 4 a. Verificar que funciona como se espera: 
    - Corregimos el problema pragmatico en "printf("La respuesta es %d\n", );" de manera que esta vez si imprima el valor que buscamos, el cual esta en la variable i. El codigo queda: printf("La respuesta es %d\n", i) y se imprime por consola "La respuesta es 42".

### Respuestas Remoción de prototipo: 
- 5.b Explicar porqué funciona; para eso, considerar las siguientes preguntas:
    - i. ¿Arroja error o warning?
       - Si, nos arroja error pero si se presentan los siguientes warnings: 
        "incompatible implicit declaration of built-in function 'printf'"
        "note: include '<stdio.h>' or provide a declaration of 'printf'"
    Nos aclara que aunque el programa se ejecute correctamente, no incluir '<stdio.h>' puede generar inconvenientes.
    - ii. ¿Qué es un prototipo y de qué maneras se puede generar? 
       - Un prototipo en C es una declaración anticipada de una función que indica su nombre, tipo de retorno y argumentos. Permite al compilador verificar que las llamadas a la función sean correctas antes de su definición. Se puede escribir manualmente o generar a partir de la definición de la función. Por lo tanto, podemos decir que un prototipo es la llamada a una función. 
  -  iii. ¿Qué es una declaración implícita de una función?
        - Ocurre cuando llamás a una función sin haber declarado su prototipo previamente. En C, esto era permitido en versiones antiguas del lenguaje (anteriores a C99), donde el compilador asumía automáticamente que la función devolvía un int y que los parámetros no se verificaban. Lo probamos en dos compiladores con versiones diferentes y en la de version MinGw 6.3.0 compilo pero se generaron muchos warnings, en cambio, en la de la version MSYS2 14.2.0 aprecio un error y no se pudo compilar.
   - iv. ¿Qué indica la especificación?
       - La especificación del lenguaje C indica que, antes de llamar a una función, debe conocerse su prototipo, es decir, su tipo de retorno y los tipos de sus parámetros. Esto permite al compilador verificar que la llamada a la función sea válida. Desde el estándar C99, se eliminó la posibilidad de usar declaraciones implícitas: ya no se permite asumir automáticamente que una función no declarada retorna int.
   - v. ¿Cómo se comportan las principales implementaciones?
       - Las principales implementaciones actuales (como GCC y Clang) siguen el estándar moderno (C99 o posterior), y por lo tanto no permiten la declaración implícita de funciones sin producir advertencias o errores. Se espera que todas las funciones usadas estén declaradas previamente mediante prototipos.
  - vi. ¿Qué es una función built-in?
       - Una función built-in es una función proporcionada directamente por el compilador, no como parte de una biblioteca externa, sino integrada internamente para optimizar el rendimiento o permitir capacidades especiales. Une jemplo seria __builtin_popcount(x) que cuenta cuántos bits en 1 hay en un entero. 
   - vii. ¿Conjeture la razón por la cual gcc se comporta como se comporta? ¿Va realmente contra la especificación?
       - GCC se comporta como se comporta para mantener compatibilidad hacia atrás con código legado escrito en C89, donde se permitían declaraciones implícitas de funciones. Sin embargo, desde C99 la declaración implícita está explícitamente prohibida, por lo que ese comportamiento va contra la especificación moderna. Cuando GGC se utiliza con estandares actuales, cumple la especificacion y lanza un error.

### Compilación Separada
 - 6.b Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción 
    - Creamos el archivo de cada uno por separado y luego generamos el objeto de cada uno con los comandos.
    Por último creamos el ejecutable hello8.exe, que vincula a los dos archivos objetos studio1.c y hello8.c 
    Aunque el compilador MINGW64 enviaban warnings, como "implicit declaration of function 'prontf' [-Wimplicit-function-declaration]
     prontf("La respuesta es %d\n", i);" permitió crear el ejecutable que vincula los dos archivos objeto

- 6.c ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf?
   - Si eliminamos o agregamos argumentos a la invocación de la función prontf, el programa presentará comportamiento indefinido. Esto significa que puede compilar con advertencias (warnings) o incluso sin errores (sin ningun aviso al compilador), pero al ejecutarse puede producir resultados incorrectos, imprimir basura, o directamente fallar (por ejemplo, con un error de segmentación).
    Esto ocurre porque en C, las funciones deben ser llamadas con la cantidad y tipo de argumentos exactos que se definieron. Si se pasa un argumento de menos, la función intentará acceder a un valor que no fue proporcionado. Si se pasa un argumento de más, ese valor quedará sin usar y puede afectar el estado de la pila o del programa.
    Además, si no se declaró previamente la función (por ejemplo, sin incluir un header), el compilador no puede verificar la cantidad de argumentos, lo que agrava el riesgo de errores.

- 6.d.
    - iv Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor?
       - Incluir el contrato (es decir, la declaración de funciones y estructuras compartidas, generalmente en un archivo .h) tanto en los clientes como en el proveedor permite garantizar que ambas partes tienen una visión coherente y sincronizada de cómo deben interactuar.
            - Ventajas:
               - Asegura que los clientes utilicen correctamente las funciones expuestas por el proveedor (con la misma cantidad y tipo de parámetros).
               - Previene errores por mal uso de funciones, como pasar argumentos incorrectos.
               - El compilador puede detectar errores de uso si un cliente llama mal una función o accede incorrectamente a una estructura.
               - Esto permite encontrar errores temprano, antes de la ejecución.
               - Si se actualiza una función en el proveedor, los clientes que incluyan el mismo contrato van a compilar con error si no se adaptan, lo que obliga a mantener sincronización entre módulos.
               - Permite separar el desarrollo en módulos independientes (cliente y proveedor) que pueden compilarse por separado, siempre que respeten el contrato común.

### Crédito extra Investigue sobre bibliotecas.
- ¿Qué son? ¿Se pueden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas? Desarrolle y utilice la biblioteca studio.
    - ¿Qué son?
      Una biblioteca (library) en C es un conjunto de funciones, estructuras, macros u otros recursos que pueden ser reutilizados por múltiples programas sin necesidad de reescribir el código fuente. Se pueden presentar en dos formas: Bibliotecas estáticas (.a en Linux / .lib en Windows): Se incluyen dentro del ejecutable al compilar. Bibliotecas dinámicas o compartidas (.so en Linux / .dll en Windows): Se cargan en tiempo de ejecución.
    - ¿Se pueden distribuir?
      Sí. Las bibliotecas se pueden distribuir fácilmente, ya sea como archivos binarios (.dll, .so, .a) o junto con sus headers (.h) para que otros desarrolladores puedan usarlas en sus propios programas.
    - ¿Son portables?
      Depende. El código fuente de una biblioteca puede ser portable si se evita usar funciones específicas de un sistema operativo. Sin embargo, los archivos compilados no son necesariamente portables entre diferentes sistemas o arquitecturas (por ejemplo, una .dll de Windows no funciona en Linux).
    - Ventajas de su uso:
      - Reutilización de código.
      - Modularidad, o sea separar funcionalidades en componentes bien definidos.
      - Facilita el mantenimiento.
      - Reducción del tamaño del código.
      - Permite que múltiples programas compartan la misma lógica, sin duplicación.
    - Desventajas de su uso:
      - Compatibilidad: Bibliotecas mal diseñadas pueden ser difíciles de usar o portar.
      - Versionado: Si cambian las interfaces, pueden romper programas que las usan.
      - Las bibliotecas dinámicas requieren que el archivo .dll o .so esté presente en el sistema.
  
    - Desarrollo paso a paso de que hace la biblioteca studio.h y studio2.c:
    - studio.h:

    - ```c
      #ifndef _STUDIO_H_INCULDED_
      #define _STUDIO_H_INCULDED_
      void prontf(const char*, int);
      #endif
      ```
      Explicación: Este archivo es el contrato de interfaz entre el proveedor y el cliente y permite garantizar que ambas partes tienen una visión de cómo deben interactuar. Las primeras lineas de "#ifndef _STUDIO_H_INCULDED_" y "#define _STUDIO_H_INCULDED_" son las inclusiones y definiciones del archivo, la linea "void prontf(const char*, int);" es la declaracion de la funcion incluida y "#endif" es el cierre del archivo.

    - studio2.c:

    - ```c
      #include "studio.h" // Interfaz que exporta
      #include <stdio.h> // Interfaz que importa
      void prontf(const char* s, int i){
      printf("La respuesta es %d\n", i);
      }
      ```
      Explicación: Este archivo es la biblioteca con su/s funcion/es y tiene la posibilidad de ser compartida y portable. Lo que hace linea por linea es: -"#include "studio.h""  Incluye el archivo de cabecera "studio.h" y actua como la interfaz pública -"#include <stdio.h>"  Incluye la biblioteca estándar <stdio.h> para poder usar funciones de entrada/salida como printf. Es una interfaz externa. -"void prontf(const char* s, int i){"  define la función prontf. -"printf("La respuesta es %d\n", i);" llama a printf para imprimir el texto "La respuesta es" seguido del valor entero i, con un salto de línea. "}" cierra la función prontf y termina el archivo.
