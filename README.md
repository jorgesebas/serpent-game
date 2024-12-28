# serpent-game

Serpent es un juego de serpiente clásico desarrollado en C++ utilizando la biblioteca `ncurses` para crear una experiencia interactiva en la terminal. El juego incluye características como colores (si son soportados por el terminal), detección de colisiones, y un marcador dinámico.

## Características

- Movimiento fluido con controles de teclado.
- Colores para la serpiente, los bordes y la comida (si el terminal los soporta).
- Detección de colisiones con la cola y los bordes.
- Incremento del marcador al comer comida.

## Controles

- **Flechas del teclado** o **WASD**: Controlan la dirección de la serpiente.
- **Q o Esc**: Salir del juego.

## Requisitos previos

Para compilar y ejecutar este juego necesitas:

- Un compilador de C++ compatible con C++11 o superior (e.g., `g++`).
- La biblioteca `ncurses` instalada en tu sistema.

En sistemas basados en Debian/Ubuntu, puedes instalar `ncurses` con:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Compilación y ejecución

El proyecto incluye un `Makefile` para facilitar la compilación y ejecución.

### Instrucciones

1. Clona este repositorio en tu máquina local:

   ```bash
   git clone https://github.com/jorgesebas/serpent-game.git
   cd serpent-game
   ```

2. Compila el proyecto utilizando `make`:

   ```bash
   make
   ```

   Esto generará un ejecutable llamado `serpent`.

3. Para ejecutar el juego, usa:

   ```bash
   make run # o ./bin/serpent
   ```

4. Para limpiar los archivos generados (como el ejecutable), usa:

   ```bash
   make clean
   ```

## Opciones de línea de comandos

El juego incluye las siguientes opciones al ejecutarse desde la terminal:

- `-h` o `--help`: Muestra el mensaje de ayuda.

  ```bash
  ./bin/serpent --help
  ```

- `-v` o `--version`: Muestra la versión del juego.

  ```bash
  ./bin/serpent -v
  ```

## Estructura del proyecto

- `serpent.cpp`: Código fuente principal del juego.
- `Makefile`: Archivo de configuración para la compilación del proyecto.

## Ejemplo de ejecución

Al iniciar el juego, verás una interfaz como esta:

```
#######################
#                     #
#                 2   #
#        oO           #
#                     #
#######################
Puntuación: 2
```

¡Usa las teclas para controlar la serpiente y evita chocar contigo mismo o los bordes!

## Licencia

Usar, copiar y/o distribuir de la manera que desee.

---

¡Disfruta jugando Serpent! 🐍

