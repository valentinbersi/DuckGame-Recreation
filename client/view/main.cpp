#include <QApplication>
#include "menu/mainwindow.h"

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT(build/namespaces)

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    bool startSDL = false;

    QObject::connect(&w, &MainWindow::initSDL, [&]() {
        startSDL = true;
        a.quit();
    });

    a.exec();

    if (startSDL) {
        try {
            SDL sdl(SDL_INIT_VIDEO);
            Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
            Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

            bool running = true;
            SDL_Event event;

            // Bucle principal de SDL.
            while (running) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        running = false;
                    }
                }

                renderer.Clear();
                renderer.Present();
                SDL_Delay(16);
            }

        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}

/*
#include <exception>
#include <iostream>

// Here we should just declare the classes that are use in this file. But for now a NOLINT is fine.
using namespace SDL2pp;  // NOLINT(build/namespaces)

int main() try {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Clear screen
    renderer.Clear();

    // Show rendered frame
    renderer.Present();

    // 5 second delay
    SDL_Delay(5000);

    // Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}*/
