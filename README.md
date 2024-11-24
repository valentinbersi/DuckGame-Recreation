# TP_DuckGame_Grupo08

## Integrantes:

- Tomás Hevia - 110934
- Valentín Bersi - 110749
- Camilo Sassone Irrazabal - 111135
- Andrés Eduardo Colina Madrid - 110680

## Problemas Conocidos:

- Cppcheck detecta falsos positivos en todo el proyecto (por ejemplo variables no usadas que claramente estan siendo usadas) y es muy probable que falle, ademas de no poder detectar problemas reales.

## Dudas:

- Las balas deberian ser dibujadas por el cliente o solo el efecto de disparo del arma? Esto es porque al las
balas ser tan rapidas es muy probable que apenas logren a verse en pantalla, entonces talvez no es conveniente
cargar a la vista con objetos que apenas se van a ver.

- Al realizar la instación, ¿Cómo podemos acomodar las rutas para que en vez de referenciar assets o mapas en el directorio build-debug o build-release, las referencien en los distintos directorios de instalación?.

## Revisar:

- Guardado de las posiciones de los objetos y como se importan y exportan en el archivo yaml (archivos LevelEditor y MapManager en la carpeta editor)

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

## Controles del Juego:

* F11 para fullscreen

#### Jugador 1:
* Movimiento: WASD
* Salto: Espacio
* Interactuar: E
* Disparo: G

#### Jugador 2:
* Movimiento: Flechas de dirección
* Salto: RSHIFT
* Interactuar: RCTRL
* Disparo: DELETE (tecla superior al enter, NO supr/del)


## Controles del Editor:
* Seleccionar/Deseleccionar objeto para agregar: Botones de número (1, 2, 3 y 4) o click en la barra lateral derecha.
* Agregar objeto seleccionado al mapa: Click izquierdo
* Eliminar objeto del mapa: Click derecho
* Nuevo Mapa: CTRL+N
* Guardar Mapa: CTRL+S
* Cargar/Editar Mapa: CTRL+E