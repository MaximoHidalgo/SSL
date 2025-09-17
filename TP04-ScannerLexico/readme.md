<p align="center">
  <span style="color:gold; font-size:35px; font-weight:bold;">
    🔍𝓣𝓟𝟜 𝓔𝓼𝓬𝓪𝓷𝓮𝓻 𝓛𝓮𝔁𝓲𝓬𝓸🔎
  </span>
</p>

  --- ---

<p align="center">
<img src="https://cdn.dribbble.com/userupload/25126157/file/original-b4e375e11656bdb2c9aec5333f82acaa.gif" alt="Escáner animado" width="300"/>
</p>

### Equipo Nº 2: *"Sintax Error"*

## 👥 Autores de la resolución: 

| Nombre completo                | Legajo     | GitHub                                      |
|-------------------------------|------------|---------------------------------------------|
| Máximo Juan Manuel Hidalgo    | 176.585-1  | [MaximoHidalgo](https://github.com/MaximoHidalgo) |
| Matias Pretzsch               | 214.029-9  | [MatiasPretzsch](https://github.com/MatiasPretzsch) |
| Juliana Pansowy Furno         | 222.575-0  | [JulianaPansowyFurno](https://github.com/JulianaPansowyFurno) |
| María Florencia Bengoechea    | 213.505-0  | [mbengoechea](https://github.com/mbengoechea) |
| Dylan Oriel Rechusky          | 203.301-0  | [DylanOriel](https://github.com/DylanOriel) |
| Jeremías Boutet               | 208.705-4  | [Jereboutet](https://github.com/Jereboutet) |
| Liam Karol Trepat             | 209.624-9  | [liamkaroltrepat](https://github.com/liamkaroltrepat) |

--- ---


## 📌 Objetivos

- Diseñar un **Escáner Léxico** que se encargue de identificar diferentes tipos de tokens.  
- Hacer la implementación de **Scanner.c Scanner.h y ScannerTest.c** del escáner léxico.  
- Describir las especificaciones en **LR ER AF GL**.
- Realizar un **archivo de texto** que se utilice como una prueba de que el escáner funciona.

--- ---

## 📚 Implementación de la solución

**Distribución de Archivos**

| Archivo                   | Descripción                                     |
|---------------------------|-------------------------------------------------|
| `automataFinitoScanner.gv`| Diagrama DOT del autómata finito (AF)           |
| `codigo.txt`              | Código que contiene un codigo para escanear     |
| `scanner.c`               | Archivo con las funciones lógicas del scanner   |
| `scanner.h`               | Interfaz y definición de tipos                  |
| `scannerTest.c`           | Archivo que contiene la función main            |
| `ScannerTest.exe`         | Programa/demuestra que el codigo funciona       |
| `README.md      `         | Es este mismo archivo de lectura sobre el TP    |


--- ---


## 📄 Especificación del Escáner Léxico en Lenguaje Natural

Este escáner léxico reconoce una serie de **tokens** básicos y asocia cada uno con su **lexema** correspondiente, con el objetivo de proveer la entrada necesaria para el análisis sintáctico.


### 🔑 Definiciones de Tokens

- **Token Type**: categoría que identifica a qué tipo de token pertenece un lexema.  
  Los tipos posibles son:
  - **KEYWORD** (palabras reservadas)  
  - **IDENTIFICADOR**  
  - **ESPACIO**  
  - **LITERAL_NUMERICO**  
  - **OPERADORES**  
  - **PUNCTUATOR**  
  - **ENDFILE_TOKEN** (fin del archivo)

### 🔍 Descripción de cada token

- **Identificador**  
  Una **letra** seguida de cero o más **alfanuméricos**.  

- **Literal numérico**  
  Un **número** seguido de cero o más **números** adicionales.  

- **Alfanumérico**  
  Puede ser una **letra** o un **número**.  

- **Letra**  
  Cualquier carácter entre `'a'–'z'`, `'A'–'Z'` o el guion bajo `_`.  

- **Número**  
  Cualquier carácter entre `'0'–'9'`.  

- **Keyword**  
  Una cadena que coincide exactamente con alguna de las siguientes palabras reservadas:  
  ```
  int, char, void, double, float
  ```

- **Operadores**  
  Uno de los siguientes caracteres:  
  ```
  (  )  [  ]  *
  ```

- **Punctuator**  
  El carácter `;`.  

- **Endfile_Token**  
  Representa el final del archivo de entrada.  

---

## 🧮 Especificaciones del Autómata Finito (AF)

- **Q: Conjunto finito de estados**  

- **q₀: Estado inicial**  
`PRINCIPIO`

- **Σ: Alfabeto de entrada**  
  Todos los caracteres ASCII, pero relevantes para el scanner:
  - Letras `[a-zA-Z]`
  - Números `[0-9]`
  - Guion bajo (`_`)
  - Operadores (`*`, `+`, `-`, `{`, `}`, `(`, `)`)
  - Punctuator (`;`)
  - Otros (*dan error*)

- **T: Función de transición**  
  - Tq : Q × Σ → Q  
  - Dado un estado y un símbolo de entrada, devuelve el próximo estado.

---

### 📋 Tabla de Transiciones

| Estado actual      | Símbolo leído                       | Estado siguiente   |
|--------------------|-------------------------------------|--------------------|
| **PRINCIPIO**      | **S** (espacio/tab/nl)              | PRINCIPIO          |
| PRINCIPIO          | **EOF**                             | EMIT_EOF           |
| PRINCIPIO          | **L** (letra)                       | IDENT              |
| PRINCIPIO          | **D** (dígito)                      | NUM                |
| PRINCIPIO          | **OP1** (`*` `+` `-` `{` `}` `(` `)`) | EMIT_OP          |
| PRINCIPIO          | `;`                                 | EMIT_PUNCT         |
| PRINCIPIO          | **OC** (otro carácter)              | EMIT_PUNCT         |
| **IDENT**          | **A** (letra/dígito/`_`)            | IDENT              |
| IDENT              | **OC** o **EOF**                    | EMIT_IDENT         |
| **NUM**            | **D** (dígito)                      | NUM                |
| NUM                | **OC** o **EOF**                    | EMIT_NUM           |
| **EMIT_IDENT**     | **ε** (emitir y seguir)             | PRINCIPIO          |
| **EMIT_NUM**       | **ε** (emitir y seguir)             | PRINCIPIO          |
| **EMIT_OP**        | **ε** (emitir y seguir)             | PRINCIPIO          |
| **EMIT_PUNCT**     | **ε** (emitir y seguir)             | PRINCIPIO          |
| **EMIT_EOF**       | **ε**                               | EMIT_EOF           |

**Leyenda de símbolos**  
- **S**: espacio, tab o salto de línea (se “consume”)  
- **L**: letra `[a–zA–Z]`  
- **D**: dígito `[0–9]`  
- **A**: alfanumérico + guion bajo (`[a–zA–Z0–9_]`)  
- **OP1**: operador de un carácter (`* + - { } ( )`)  
- **OC**: cualquier otro carácter (por defecto se tokeniza como **PUNCTUATOR**)  
- **ε**: transición inmediata sin consumir más entrada (emite token y vuelve a `PRINCIPIO`; `EMIT_EOF` es terminal)


---

### 💻 Diagrama de la Maquina de Estados

El diseño de la Máquina de Estados está en el archivo  
`automataScanner.gv`

Enlace directo para ver el grafo DOT e interactuar con él:  
👉 [Visualizar el Grafo DOT](./assets/automataFinitoScanner.svg)


## 🧮 Especificación en Expresiones Regulares (RegEx)

```
KEYWORD         →  "int" | "char" | "void" | "double" | "float"
IDENTIFICADOR   →  [A-Za-z_][A-Za-z0-9_]*
NUMEROS         →  [0-9]+
OPERADORES      →  [ () | [] | * ]
PUNCTUATOR      →  [;]
ESPACIOS        →  [\t\n\v\f\r]+
```

## 🧮 Especificacion en Gramática Léxica:

```
<token> -> uno de <KEYWORD> <IDENTIFICADOR> <ESPACIO> <LITERAL_NUMERICO> 

<OPERADORES> <PUNCTUATOR> <ENDFILE_TOKEN>

<IDENTIFICADOR> -> <letra> {<alfanumerico>}

<LITERAL_NUMERICO> -> <numero> {<numero>}

<alfanumerico> -> uno de <letra> <numero>

<letra> -> una de a-z A-Z o el "_"

<numero> -> uno de 0-9

<KEYWORD> -> una de estos "int" "char" "void" "double" "float"

<OPERADORES> -> uno de "(" | ")" | "*" | "[" | "]"

<PUNCTUATOR> -> uno de ";"

<ENDFILE_TOKEN> -> representa el final del archivo
```
