#include "Game.hpp"

#define WINDOW_WIDTH 1040
#define WINDOW_HEIGHT 680

#define DELTA_TIME (1.0/30.0)
#define SCALE 2.5f

// Here we should just declare the classes that are use in this file. But for now a NOLINT is fine.
using namespace SDL2pp;  // NOLINT(build/namespaces)

Game::Game()
    : running(true), m_key(Keybinds::NONE), window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE),
      renderer(window, -1, SDL_RENDERER_ACCELERATED) {}

void Game::init() {
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    //handlear cantidad de patos para pintar etc...

    Texture backgroundTexture = startBackground();

    Player player1("../../assets/player/greyDuck.png", 3, 6, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    player1.start();

    renderer.Present();

    while(running) {
        handleEvents();       // handle user input
        renderer.Clear();
        showBackground(backgroundTexture);
        update(player1);             //update all objects (positions, etc)
        //render();         render EVERYTHING again (outside players, that are being rendered in the player class)
        SDL_Delay(33);


        ///////////etc

    }


    IMG_Quit();
}

Keybinds Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMapping.find(scancode);
            if (it != keyMapping.end()) {
                m_key = it->second;
            }

        } else if (event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMapping.find(scancode);
            if (it != keyMapping.end() && m_key == it->second) {
                m_key = Keybinds::NONE;
            }

            //MOUSE EVENTS ETC...? MULTIPLES TECLAS?

        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    return m_key;
}

void Game::update(Player& player1) {
    player1.update(m_key);
    renderer.Present();

    // ETC...


}

/*void Game::render(Player player1) {

}*/

Texture Game::startBackground() {
    SDL_Surface* rawBackgroundSurface = IMG_Load("../../assets/background/background1.png");
    Surface backgroundSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);

    showBackground(backgroundTexture);
    return backgroundTexture;
}

void Game::showBackground(Texture& backgroundTexture) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = -1000;
    dstRect.w = WINDOW_WIDTH * SCALE;
    dstRect.h = WINDOW_HEIGHT * SCALE;

    //renderer.Clear();

    renderer.Copy(backgroundTexture, NullOpt, dstRect);
}

/*void Game::selectLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);

    int randomLevel = dis(gen);

    selectedLevel = levels[randomLevel];
}*/

Game::~Game() {
    //SDL_DestroyRenderer(renderer.Get());
    //SDL_DestroyWindow(window.Get());
    SDL_Quit();
}
