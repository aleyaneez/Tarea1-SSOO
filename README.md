# Carrera de Autos en C++

Este programa simula una carrera de autos utilizando hebras (`threads`) en C++. Cada auto corre en una hebra separada, con avances aleatorios y pausas también aleatorias. Al finalizar la carrera, se muestra el progreso en tiempo real y el orden de llegada de los autos.

## Requisitos

Para compilar y ejecutar el programa, necesitarás:

- Un compilador de C++ compatible con C++11 o superior (como `g++` o `clang`).
- Sistema operativo compatible con la biblioteca estándar de C++ (`libstdc++` o similar).
- **make** instalado en tu sistema para compilar el programa utilizando un Makefile.

## Clonar el repositorio

Para clonar el repositorio, usa el siguiente comando en tu terminal:

```bash
git clone https://github.com/aleyaneez/Tarea1-SSOO.git
```

Esto descargará todos los archivos del repositorio en un directorio local en tu sistema.

## Compilación

Este proyecto incluye un **Makefile** para facilitar el proceso de compilación. Para compilar el programa, sigue estos pasos:

1. Abre la terminal.
2. Navega hasta el directorio donde se clonó el repositorio:

   ```bash
   cd carrera-autos
   ```

3. Ejecuta el siguiente comando para compilar el programa:

   ```bash
   make
   ```

   Este comando generará un archivo ejecutable llamado `CarreraAutos` en el mismo directorio.

## Ejecución

Una vez que el programa haya sido compilado correctamente, puedes ejecutarlo proporcionando dos parámetros:
1. **Distancia total de la carrera** (en metros).
2. **Número de autos** que participan en la carrera.

Ejemplo de cómo ejecutar el programa:

```bash
./CarreraAutos <distancia_meta> <numero_autos>
```

### Parámetros

- **`distancia_meta`**: La distancia total de la carrera (en metros). Debe ser un número entero.
- **`numero_autos`**: El número de autos que participarán en la carrera. Debe ser un número entero.

### Ejemplo de ejecución:

```bash
./CarreraAutos 100 5
```

En este ejemplo, se ejecuta una carrera de 100 metros con 5 autos.

### Resultado:

Durante la ejecución, se mostrará en la terminal el avance en tiempo real de cada auto, con los autos imprimiendo su progreso y llegando a la meta. Al final, se mostrará una tabla con el orden de llegada de los autos.

## Limpieza del proyecto

Para eliminar el archivo ejecutable y limpiar el directorio de compilación, usa el siguiente comando:

```bash
make clean
```

Este comando eliminará el archivo ejecutable `CarreraAutos`.

## Notas adicionales

- Si el programa no se ejecuta correctamente o no puedes ver los colores en la terminal, verifica que tu terminal soporte secuencias de escape ANSI.
- En caso de errores de compilación relacionados con las hebras (`thread`), asegúrate de estar usando el compilador `g++` con soporte para hebras (añadiendo la opción `-pthread`).

## Autores

- Aracelli Rivas Tapia - [GitHub Profile](https://github.com/Roussd)
- Alejandro Yáñez Oyarce - [GitHub Profile](https://github.com/aleyaneez)
