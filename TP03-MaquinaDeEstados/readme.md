# 🤖𝓣𝓟𝟛 - 𝓜𝓪𝓺𝓾𝓲𝓷𝓪𝓼 𝓭𝓮 𝓔𝓼𝓽𝓪𝓭𝓸 — 𝓢𝓲𝓷 𝓒𝓸𝓶𝓮𝓷𝓽𝓪𝓻𝓲𝓸𝓼🤖

<p align="center">
<img src="https://miro.medium.com/v2/resize:fit:640/1*41LSikhXWH13HPCv3isiqA.png" width="300"/>
</p>

### Equipo Nº 2: *"Sintax Error"*

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

--- ---


## 📌 14.1.1 Objetivos

- Diseñar una **máquina de estados** que remueva comentarios de código.  
- Implementar **dos versiones** de la máquina de estados.  
- Realizar un **benchmark** para determinar cuál implementación es más eficiente.  


## 📚 14.1.2 Temas

- Máquinas de estado (SM)  
- Lenguaje **DOT** para dibujar grafos dirigidos  
- Eliminación de comentarios en código fuente   
- Entrada/salida estándar (`<`, `>`)  
- **Makefile** con múltiples targets  
- `enum` para representar estados  
- Benchmarks y comparación de rendimiento  


## ⛔ 14.2 Restricciones

- Primero diseñar y especificar la máquina de estado y luego derivar dos implementaciones.
- Utilizar el lenguaje **DOT** para dibujar los digrafos.
- Incluir comentarios de una sola línea (//).
- Considerar las variantes no comunes de literales carácter y de literales cadenas que son parte del estándar de C.
- Diseñar el programa para que pueda invocarse de la siguiente manera:
  ```bash
  RemoveComments < Test.c > NoComments.c
  ```
- Ninguna de las implementaciones debe ser la "Implementación #1: estado como variable y transiciones con selección estructurada."
- Indicar para la implementación cómo se representan los estados y cómo las transiciones.
- Respetar la máquina de estado especificada, en cada implementación utilizar los mismos nombres de estado y cantidad de transiciones.
- En el caso que sea necesario, utilizar `enum` , y no `define`.
- Diseñar el archivo **Makefile** para que construya una, otra o ambas implementaciones, y para que ejecute las pruebas.


## 📦 14.3 Productos

```
DD-SinComentarios
│-- readme.md
│-- RemoveComments.gv
│-- RemoveComments.c
└-- Makefile
```
## 📖 Diccionario
Σ_i: ASCII \
Σ_0: {emitir, ignorar, ε, emitir / + caracter} \
Q: INICIAL, BARRA, COMENTARIO_SIMPLE, COMENTARIO_MULTIPLE, FIN_COMENTARIO_MULTIPLE, CADENA, ESCAPE_EN_CADENA, CARACTER, ESCAPE_EN_CARACTER \

B: / \
BI: \\ \
A: * \
CS: ' \
CD: " \
\n: Nueva linea \
OC: Otro caracter 

## 📅 Tabla de transicion

| TT                   | B                  | BI                     | A                      | CS        | CD        | \n        | OC        |
|-----------------------|--------------------|------------------------|------------------------|-----------|-----------|-----------|-----------|
| INICIAL              | BARRA              | INICIAL                | INICIAL                | CARÁCTER  | CADENA    | INICIAL   | INICIAL   |
| BARRA                | COMENTARIO_SIMPLE  | INICIAL                | COMENTARIO_MULTIPLE    | INICIAL   | INICIAL   | INICIAL   | INICIAL   |
| COMENTARIO_SIMPLE    | COMENTARIO_SIMPLE  | COMENTARIO_SIMPLE      | COMENTARIO_SIMPLE      | COMENTARIO_SIMPLE | COMENTARIO_SIMPLE | INICIAL   | COMENTARIO_SIMPLE |
| COMENTARIO_MULTIPLE  | COMENTARIO_MULTIPLE| COMENTARIO_MULTIPLE    | FIN_COMENTARIO_MULTIPLE| COMENTARIO_MULTIPLE | COMENTARIO_MULTIPLE | COMENTARIO_MULTIPLE | COMENTARIO_MULTIPLE |
| FIN_COMENTARIO_MULTIPLE | INICIAL          | FIN_COMENTARIO_MULTIPLE| FIN_COMENTARIO_MULTIPLE| FIN_COMENTARIO_MULTIPLE | FIN_COMENTARIO_MULTIPLE | FIN_COMENTARIO_MULTIPLE | FIN_COMENTARIO_MULTIPLE |
| CADENA               | CADENA             | ESCAPE_EN_CADENA       | CADENA                 | CADENA    | INICIAL   | CADENA    | CADENA    |
| ESCAPE_EN_CADENA     | CADENA             | CADENA                 | CADENA                 | CADENA    | CADENA    | CADENA    | CADENA    |
| CARÁCTER             | CARÁCTER           | ESCAPE_EN_CARACTER     | CARÁCTER               | INICIAL   | CARÁCTER  | CARÁCTER  | CARÁCTER  |
| ESCAPE_EN_CARACTER   | CARÁCTER           | CARÁCTER               | CARÁCTER               | CARÁCTER  | CARÁCTER  | CARÁCTER  | CARÁCTER  |

     
## 📅 Tabla de acciones

| TA                   | B       | BI      | A       | CS      | CD      | \n     | OC                  |
|-----------------------|---------|---------|---------|---------|---------|--------|---------------------|
| INICIAL              | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | emitir              |
| BARRA                | ε       | emitir  | emitir  | emitir  | emitir  | emitir | emitir B + carácter |
| COMENTARIO_SIMPLE    | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | ε                   |
| COMENTARIO_MULTIPLE  | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | ε                   |
| FIN_COMENTARIO_MULTIPLE | ε     | emitir  | emitir  | emitir  | emitir  | emitir | ε                   |
| CADENA               | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | emitir              |
| ESCAPE_EN_CADENA     | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | emitir              |
| CARÁCTER             | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | emitir              |
| ESCAPE_EN_CARACTER   | emitir  | emitir  | emitir  | emitir  | emitir  | emitir | emitir              |







