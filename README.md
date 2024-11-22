# TP_DuckGame_Grupo08

## Integrantes:

- Tomás Hevia - 110934
- Valentín Bersi - 110749
- Camilo Sassone Irrazabal - 111135
- Andrés Eduardo Colina Madrid - 110680

## Instalación:

1. Instalar git: $ sudo apt install git

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

#### Ejecución release (desde cualquier directorio):

7. Ejecutar el server: $ ./DuckGameDedicatedServer 8080

8. Ejecutar los clients: $ ./DuckGame localhost 8080

9. Ejecutar el editor: $ ./DuckGameLevelEditor

10. Ejecutar los tests: $ ./DuckGameTests
