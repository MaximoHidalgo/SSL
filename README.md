<div align="center">

# ⚙️ Sintaxis y Semántica de los Lenguajes (SSL)

**Fundamentos de Compiladores, Autómatas Finitos y Análisis Léxico en C**

*UTN - Facultad Regional Buenos Aires | Cursada 2025*

[![Language: C](https://img.shields.io/badge/Language-C11%20%2F%20ANSI%20C-blue.svg?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler: GCC](https://img.shields.io/badge/Compiler-GCC%2011%2B-orange.svg?logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Build: Make](https://img.shields.io/badge/Build-Makefile-lightgrey.svg?logo=gnu-bash&logoColor=white)](https://www.gnu.org/software/make/)
[![Platform: Linux/POSIX](https://img.shields.io/badge/Platform-Linux%20%7C%20POSIX-black.svg?logo=linux&logoColor=white)](https://www.kernel.org/)
[![Status: Completed](https://img.shields.io/badge/Status-Completed%20%26%20Approved-success.svg)](#)

</div>

---

## 📌 Descripción General

Este repositorio contiene la suite completa de trabajos prácticos de la materia **Sintaxis y Semántica de los Lenguajes (K2002)** de la Universidad Tecnológica Nacional (UTN-FRBA). 

El objetivo del proyecto fue profundizar en las etapas tempranas de un compilador, implementando en **C puro** desde el análisis de las fases de traducción hasta el diseño de **Autómatas Finitos Deterministas (DFA)** y **Analizadores Léxicos (Scanners)** con tablas de transición de estados y procesamiento de flujos de texto.

---

## 📂 Estructura de Módulos y Trabajos Prácticos

| Módulo | Nombre | Foco Técnico | Conceptos Clave |
| :--- | :--- | :--- | :--- |
| **`TP00`** | **CHelloWorld** | Toolchain y Entorno | Configuración del compilador GCC, flags de advertencia estricta (`-Wall -Wextra -pedantic`). |
| **`TP01`** | **Fases y Errores** | Pipeline de Compilación | Preprocesamiento (`-E`), compilación a ensamblador (`-S`), ensamblado (`-c`) y vinculación (Linker). Diagnóstico de errores sintácticos vs semánticos. |
| **`TP02`** | **Interfaces y Módulos** | Arquitectura en C | Diseño modular, separación estricta de interfaces públicas (`.h`) e implementación (`.c`), encapsulamiento de datos. |
| **`TP03`** | **Máquina de Estados** | Autómatas Finitos (DFA) | Implementación de autómatas deterministas mediante matrices de transición de estados (`transition_table`) para validación de constantes enteras (decimales, octales, hexadecimales). |
| **`TP04`** | **Escáner Léxico** | Tokenizador / Scanner | Analizador léxico completo para reconocimiento y categorización de tokens (identificadores, palabras reservadas, literales y operadores) con reporte de coordenadas de error. |

---

## 🧠 Competencias Técnicas Demostradas

* **Programación en C de Bajo Nivel**: Manejo riguroso de punteros, aritmética de direcciones, structs y buffers de caracteres sin fugas de memoria.
* **Teoría de Autómatas y Lenguajes Formales**: Modelado formal de expresiones regulares (RegEx) transformadas en grafos de estados y tablas de decisión matriciales.
* **Ingeniería de Compiladores**: Comprensión profunda de la separación entre Frontend (Léxico / Sintáctico) y Backend del compilador.
* **Automatización de Builds**: Uso de `Makefiles` modulares para compilación incremental y targets de limpieza (`clean`, `all`).

---

## 🛠️ Requisitos y Compilación

### Dependencias
* Compilador **GCC** (compatible con estándar C99/C11).
* **GNU Make**.

### Compilación y Ejecución
Cada trabajo práctico cuenta con su respectiva estructura independiente. Para compilar cualquiera de los módulos (por ejemplo, el Escáner Léxico):

```bash
# Navegar al directorio del TP
cd TP04-ScannerLexico

# Compilar mediante Make
make

# Ejecutar el binario generado
./scanner
