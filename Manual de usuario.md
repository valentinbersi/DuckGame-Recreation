# Manual de usuario

### Versiones y pasos para compilar el proyecto:

SO, dependencias, versiones, pasos para compilar. ¿hay que modificar archivo con parámetros? hay que poner algun recurso (imagenes, sonidos) en algun lugar?

## Instalación:

1. Instalar git:
    1. $ sudo apt update
    2. $ sudo apt upgrade  
    3. $ sudo apt install git

2. Clonar el repo:
    1. $ git clone git@github.com:valentinbersi/TP_DuckGame_Grupo08.git
    2. $ cd TP_DuckGame_Grupo08

3. Correr el script de instalación de dependencias: $ ./pre-install.sh

#### Compilación para debug:

4. Configurar el proyecto:
    1. $ mkdir build-debug
    2. $ cd build-debug
    3. $ cmake -DCMAKE_BUILD_TYPE=Debug ..

5. Compilar version debug: $ cmake --build .

#### Ejecución debug (desde el directorio build-debug):

6. Ejecutar el server: $ ./DuckGameDedicatedServer 8080

7. Ejecutar los clients: $ ./DuckGame localhost 8080

8. Ejecutar el editor: $ ./DuckGameLevelEditor

9. Ejecutar los tests: $ ./DuckGameTests

#### Configuración para release (version a instalar):

4. Configurar el proyecto:
    1. $ mkdir build-release
    2. $ cd build-release
    3. $ cmake -DCMAKE_BUILD_TYPE=Release ..

5. Compilar version release: \$ cmake --build .

6. Instalar: \$ sudo cmake --install .

#### Ejecución release (desde cualquier directorio): (esta feature aún no es funcional porque no sabemos como resolver las rutas)
 
7. Ejecutar el server: $ DuckGameDedicatedServer 8080

8. Ejecutar los clients: $ DuckGame localhost 8080

9. Ejecutar el editor: $ DuckGameLevelEditor

10. Ejecutar los tests: $ DuckGameTests

## ¿Cómo se levanta el servidor?

## ¿Cómo se crean nuevos niveles con el editor?

## ¿Cómo se lanza el cliente?

## Dinámica del Juego

La jugabilidad es simple: El juego consta de diversas rondas donde los jugadores batallaran entre sí con diversas armas tomadas del mapa. Las rondas se complementan con **sets**, los cuales duran 5 rondas.
Cada finalización de **set** mostrará la cantidad de rondas ganadas por cada jugador, y el que llegue primero a las 10 rondas será el ganador.
Cada jugador aguantará por default un solo ataque, independientemente del arma que sea. Por eso mismo, el gameplay se volverá lo más frenético posible.

*Además, el jugador puede*:
* Hacerse el muerto
* Aumentar la altura del salto manteniendo presionada la tecla
* Moverse hacia los lados y 'aletear' en el aire presionando repetidas veces la tecla de salto
* Tomar armas y diversas armaduras para usarlas

Cada pieza de armadura (sea un helmet o chestplate) amortiguará **1** ataque extra recibido

### Controles del Juego:

* F11 para fullscreen

#### Jugador 1:
* Movimiento: `WASD`
* Salto: `ESPACIO`
* Interactuar: `E`
* Disparo: `G`

#### Jugador 2:
* Movimiento: Flechas de dirección (`←` `↑` `↓` `→`)
* Salto: `RSHIFT`
* Interactuar: `RCTRL`
* Disparo: `DELETE` (tecla superior al enter, NO supr/del)


## Controles del Editor:
* Seleccionar/Deseleccionar objeto para agregar: Se selecciona en la barra lateral derecha.
* Agregar objeto seleccionado al mapa: Click izquierdo
* Eliminar objeto del mapa: Click derecho
* Nuevo Mapa: `CTRL+N`
* Guardar Mapa: `CTRL+S`
* Cargar/Editar Mapa: `CTRL+E`
