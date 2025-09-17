<p align="center">
  <span style="color:violet; font-size:35px; font-weight:bold;">
    💻𝓣𝓟𝟚 - 𝓘𝓷𝓽𝓮𝓻𝓯𝓪𝓬𝓮𝓼 & 𝓜𝓪𝓴𝓮𝓯𝓲𝓵𝓮 - 𝓣𝓮𝓶𝓹𝓮𝓻𝓪𝓽𝓾𝓻𝓪𝓼💻
  </span>
</p>

  --- ---

<p align="center">
<img src="https://images.icon-icons.com/1377/PNG/512/textxmakefile_92756.png" width="300"/>
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

## 📌 6.1 Objetivos

- Aplicar el uso de **interfaces y módulos**.  
- Construir un programa formado por más de una unidad de traducción.  
- Comprender el proceso de traducción o **Build** cuando intervienen varios archivos fuente.
- Aplicar el uso de **Makefile**.


## 📚 6.2 Temas

- Makefile  
- Archivos header (`.h`)   
- Funciones  
- Pruebas unitarias  
- `assert`  
  > ⚠️ La comparación de los tipos flotantes, como double, no es trivial ni directa debido a su representación y precisión. Debemos incorporar la comparación con tolerancia mediante una función bool que reciba dos flotantes a comparar y un flotante que represente la tolerancia y retorna verdadero si los flotantes están cerca según la tolerancia. Se propone la función AreNear, y también las soluciones presentadas en [DAWSON2012] y [ERICSON2008].  
- Interfaces e implementación
- Tipo de dato `double` 


## 🛠️ 6.3 Problema y 6.4 Solución

- Se necesita una tabla que presente las temperaturas Celsius convertidas en Fahrenheit, y otra en el sentido opuesto. 
- Desarrollar un programa que imprima estas dos tablas de conversión.


## 🛠️ 6.5 Tareas

1. Escribir `Makefile`  
2. Escribir `Conversion.h`  
3. Escribir `ConversionTest.c`  
4. Escribir `Conversion.c`  
5. Escribir `TablasDeConversion.c`


## ⛔ 6.6 Restricciones

- Las dos funciones públicas deben llamarse **`Celsius`** y **`Fahrenheit`**.  
- Utilizar `assert`.  
- Usar `const`, no `#define`.  
- Utilizar `for` con declaración (estilo **C99**)



## ⭐ Crédito Extra

### Funciones para Tablas de Conversión

Desarrollar `TablasDeConversion.c` utilizando funciones del estilo:

- `PrintTablas`
- `PrintTablaCelsius`
- `PrintTablaFahrenheit`
- `PrintFilas`
- `PrintFila`

 Los **límites inferior y superior**, y el **incremento**, deben ser **parámetros** de las funciones.


### Generalización de `PrintFilas`

Desarrollar la función `PrintFilas` de forma **genérica**:

- Debe poder invocarse desde `PrintTablaFahrenheit` y `PrintTablaCelsius`.
- `PrintFilas` debe invocar a `PrintFila`.
- Considerar el uso de **punteros a función** para lograr la reutilización.
