# TP4 - Escáner Léxico

#### Equipo N.º 2: *"Sintax Error"*


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


## 📌 14.1.1 Objetivos

- Diseñar un **Escáner Léxico** que se encargue de identificar diferentes tipos de tokens.  
- Hacer la implementación de **Scanner.c Scanner.h y ScannerTest.c** del escáner léxico.  
- Describir las especificaciones en **LR ER AF GL**.
- Realizar un **archivo de texto** que se utilice como una prueba de que el escáner funciona.

--- ---


# 📄 Especificación del Escáner Léxico en Gramatica Regular

Este escáner léxico reconoce una serie de **tokens** básicos y asocia cada uno con su **lexema** correspondiente, con el objetivo de proveer la entrada necesaria para el análisis sintáctico.


## 🔑 Definiciones de Tokens

- **Token Type**: categoría que identifica a qué tipo de token pertenece un lexema.  
  Los tipos posibles son:
  - **KEYWORD** (palabras reservadas)  
  - **IDENTIFICADOR**  
  - **ESPACIO**  
  - **LITERAL_NUMERICO**  
  - **OPERADORES**  
  - **PUNCTUATOR**  
  - **ENDFILE_TOKEN** (fin del archivo)

### Descripción de cada token

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



## 🧮 Especificación en Expresiones Regulares (ER)

```regex

KEYWORD         →  "int" | "char" | "void" | "double" | "float"
IDENTIFICADOR   →  [A-Za-z_][A-Za-z0-9_]*
NUMEROS         →  [0-9]+
OPERADORES      →  [\(\)\[\]\*]
PUNCTUATOR      →  ";"
ESPACIOS        →  [ \t\n\v\f\r]+
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

<OPERADORES> -> uno de () * []

<PUNCTUATOR> -> uno de ;

<ENDFILE_TOKEN> -> representa el final del archivo
```
