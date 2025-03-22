# Get Next Line (GNL)

Un proyecto de 42 que consiste en crear una función que lee líneas desde un descriptor de archivo.

## 📝 Descripción

`get_next_line` es una función que lee una línea desde un descriptor de archivo, terminando con un salto de línea (`\n`) o con el final del archivo. Esta función es útil para leer datos línea por línea desde un archivo, entrada estándar u otro descriptor de archivo.

### Características principales:

- Lee desde cualquier descriptor de archivo válido
- Maneja correctamente los errores
- Gestiona eficientemente la memoria
- Compatible con diferentes tamaños de buffer (definidos en tiempo de compilación)
- Versión bonus que soporta múltiples descriptores de archivo simultáneamente

## 🛠️ Funcionalidad

La función tiene el siguiente prototipo:
```c
char *get_next_line(int fd);
```

- **Parámetros**: `fd` - Descriptor de archivo del que leer
- **Valor devuelto**:
  - Si todo va bien: la línea leída (incluyendo el `\n` si existe)
  - En caso de error o fin de archivo: `NULL`

## 🧩 Archivos del proyecto

### Versión obligatoria
- `get_next_line.c`: Implementación principal de la función
- `get_next_line_utils.c`: Funciones auxiliares
- `get_next_line.h`: Archivo de cabecera con definiciones y prototipos

### Versión bonus
- `get_next_line_bonus.c`: Implementación principal con soporte multidescriptor
- `get_next_line_utils_bonus.c`: Funciones auxiliares para la versión bonus
- `get_next_line_bonus.h`: Archivo de cabecera para la versión bonus

## 💻 Uso

### Compilación

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

El parámetro `BUFFER_SIZE` determina el tamaño del buffer utilizado para las lecturas. Puede ser modificado durante la compilación para optimizar el rendimiento según el contexto.

### Ejemplo de uso

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    // Abrir archivo
    fd = open("ejemplo.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    // Leer y mostrar líneas hasta el final del archivo
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Importante liberar memoria
    }
    
    // Cerrar archivo
    close(fd);
    return (0);
}
```

## 🔍 Detalles técnicos

### Variables estáticas

El proyecto utiliza variables estáticas para preservar la información entre llamadas a la función, permitiendo continuar la lectura desde donde se quedó anteriormente.

### Gestión de memoria

- Toda la memoria asignada por la función es liberada correctamente
- El proyecto no contiene pérdidas de memoria (memory leaks)
- Se realiza una cuidadosa validación de los punteros para evitar comportamientos indefinidos

### Optimización

La implementación está optimizada para:
- Minimizar las llamadas a `read()`
- Evitar copias innecesarias de memoria
- Manejar eficientemente buffers de diferentes tamaños

## ⭐ Versión bonus

La versión bonus permite leer de múltiples descriptores de archivo simultáneamente sin perder el hilo de lectura de cada uno. Esto es posible gracias a un array de estructuras que mantienen el estado para cada descriptor.

## 📋 Normas del proyecto

- Máximo 25 líneas por función
- Máximo 5 funciones por archivo
- Uso exclusivo de las funciones autorizadas: `read`, `malloc` y `free`
- Sin fugas de memoria
- Sin errores de compilación con las flags `-Wall -Wextra -Werror`

## 📚 Aprendizaje

Este proyecto permite comprender conceptos como:
- Variables estáticas en C
- Gestión de memoria dinámica
- Manejo de descriptores de archivo
- Operaciones de entrada/salida de bajo nivel

## 🧪 Pruebas

Puedes probar la función con diferentes tamaños de buffer y tipos de archivos:
- Archivos de texto grandes y pequeños
- Diferentes tamaños de BUFFER_SIZE (1, 42, 10000000)
- Archivos sin saltos de línea
- Descriptores de archivo inválidos

## 📄 Licencia

Este proyecto forma parte del plan de estudios de [42](https://www.42.fr/).



====================================



# Get Next Line (GNL)

A 42 project that involves creating a function to read lines from a file descriptor.

## 📝 Description

`get_next_line` is a function that reads a line from a file descriptor, ending with a newline character (`\n`) or with the end of the file. This function is useful for reading data line by line from a file, standard input, or any other file descriptor.

### Main features:

- Reads from any valid file descriptor
- Handles errors correctly
- Efficiently manages memory
- Compatible with different buffer sizes (defined at compile time)
- Bonus version that supports multiple file descriptors simultaneously

## 🛠️ Functionality

The function has the following prototype:
```c
char *get_next_line(int fd);
```

- **Parameters**: `fd` - File descriptor to read from
- **Return value**:
  - If successful: the read line (including `\n` if it exists)
  - In case of error or end of file: `NULL`

## 🧩 Project Files

### Mandatory version
- `get_next_line.c`: Main function implementation
- `get_next_line_utils.c`: Helper functions
- `get_next_line.h`: Header file with definitions and prototypes

### Bonus version
- `get_next_line_bonus.c`: Main implementation with multi-descriptor support
- `get_next_line_utils_bonus.c`: Helper functions for the bonus version
- `get_next_line_bonus.h`: Header file for the bonus version

## 💻 Usage

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

The `BUFFER_SIZE` parameter determines the buffer size used for reading. It can be modified during compilation to optimize performance according to the context.

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    // Open file
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    // Read and display lines until the end of the file
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Important to free memory
    }
    
    // Close file
    close(fd);
    return (0);
}
```

## 🔍 Technical Details

### Static Variables

The project uses static variables to preserve information between function calls, allowing reading to continue from where it left off previously.

### Memory Management

- All memory allocated by the function is correctly freed
- The project contains no memory leaks
- Careful pointer validation is performed to avoid undefined behaviors

### Optimization

The implementation is optimized to:
- Minimize calls to `read()`
- Avoid unnecessary memory copies
- Efficiently handle buffers of different sizes

## ⭐ Bonus Version

The bonus version allows reading from multiple file descriptors simultaneously without losing track of each one's reading position. This is possible thanks to an array of structures that maintain the state for each descriptor.

## 📋 Project Norms

- Maximum 25 lines per function
- Maximum 5 functions per file
- Exclusive use of authorized functions: `read`, `malloc`, and `free`
- No memory leaks
- No compilation errors with flags `-Wall -Wextra -Werror`

## 📚 Learning

This project helps to understand concepts such as:
- Static variables in C
- Dynamic memory management
- File descriptor handling
- Low-level input/output operations

## 🧪 Testing

You can test the function with different buffer sizes and file types:
- Large and small text files
- Different BUFFER_SIZE values (1, 42, 10000000)
- Files without line breaks
- Invalid file descriptors

## 📄 License

This project is part of the [42](https://www.42.fr/) curriculum.
