# Manual de proyecto

## Organización General de Trabajo

Como Recomendación de los Correctores a cargo del grupo, se propuso dividir el proyecto en 4
grandes bloques:

* Desarrollo de Lobby y Editor de niveles usando QT (Tomás Hevia).
* Desarrollo de la Interfaz del cliente usando SDL, manejando animaciones, cámara y eventos (Camilo Sassone).
* Desarrollo de Protocolos, Hilos y Testing (Andres Eduardo Colina Madrid)
* Desarrollo de la lógica del juego dentro del Server (Valentín Bersi)

Esta idea fue la que se intentó mantener a lo largo del proyecto. No obstante pasadas las semanas,
se necesitó que algunos integrantes ayudarán a otros en los grandes desafíos del proyecto. Eventualmente, los encargados
del Server tuvieron mayor división de responsabilidades, y ambos clientes gráficos pudieron estar un tanto más aislados.

## Herramientas/Tecnologías y Documentación Usada

* Como IDE principal se usó CLION, ya que dentro de todo, es el más completo para el desarrollo de aplicaciones en C++ y
  C. Sin embargo, también se optó por usar Visual Studio Code como otra opción viable, pues gracias a la gran cantidad
  de configuraciones y plugins disponibles resulta flexible.


* Tanto cpplint como cppcheck fueron usados mediante pre-commit, ambos resultaron útiles, pero hasta cierto punto; pues
  nos encontramos constantemente con varios falsos positivos que en vez de ayudar confunden y retrasaban el desarrollo
  del proyecto.


* Como formateador se usó Clang Format, permitiendo buena legibilidad y organización del proyecto.


* Para Debuggear, en el caso de CLION ya está integrado y listo para su uso; y para el caso de Visual Studio Code se
  configuró con base en gdb.


* La principal fuente de información usada fue proveniente de https://en.cppreference.com y https://cplusplus.com/.com,
  páginas más que necesarias, pues tienen toda la información de pertinente de las librerías de c++.
  En el caso de las librerías gráficas se extrajo información de https://doc.qt.io/
  y https://github.com/libSDL2pp/libSDL2pp-tutorial

## Dificultades

* Físicas Del Juego:
  Al no tener experiencia anterior, el desarrollo de físicas fue un eslabón grande.
  Si bien se quería tener un diseño semejante a un motor de físicas, finalmente se decidió por mantener una
  funcionalidad básica y
  funcional (colisión de rectángulos y ray casting).


* Cámara del Cliente Gráfico:
  Los prototipos iniciales fueron exitosos, pero a medida que se agregan más elementos al juego, era necesario reajustar
  la funcionalidad de la cámara de forma tal que todo objeto renderizado sea mostrado de
  forma acorde.


* Instalador:
  El primer instalador del proyecto fue exitoso, pero únicamente para versiones actuales de Ubuntu, para la
  versión pedida por la consigna no resultaba compatible, ocasionando un largo retraso en el desarrollo del juego.

## Recomendación a la cátedra

La cursada nos resultó intensa, pero disfrutable.
No obstante, los temas están un poco desactualizados, por ejemplo, en
Paradigmas de la Programación ya se obtienen nociones suficientes de Herencia Y Polimorfismo.
Dicho esto, nos hubiera gustado ver Patrones de Diseño, los cuales seguro serán de provecho a la hora de codear en
proyectos tan grandes como
este.

Por otra parte, nos resulta conveniente recomendar que para futuras entregas, la versión pedida para la instalación del
proyecto sea una un poco más actual, pues las desactualizadas suelen portar errores que escapan el scope del proyecto.
