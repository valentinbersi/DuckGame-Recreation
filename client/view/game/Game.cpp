#include "Game.hpp"

#define SCALE 2.5f

#define DEF_WINDOW_WIDTH 1040
#define DEF_WINDOW_HEIGHT 680

#define WINDOW_TITLE "DuckGame"

#define greySheet "assets/player/greyDuck.png"
#define orangeSheet "assets/player/orangeDuck.png"
#define whiteSheet "assets/player/whiteDuck.png"
#define yellowSheet "assets/player/yellowDuck.png"

#define greyFeathers "assets/player/greyDuckFeathers.png"
#define orangeFeathers "assets/player/orangeDuckFeathers.png"
#define whiteFeathers "assets/player/whiteDuckFeathers.png"
#define yellowFeathers "assets/player/yellowDuckFeathers.png"

#define ROCK "assets/enviroment/rock.png"

using SDL2pp::NullOpt;
using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::Surface;
using SDL2pp::Texture;

Game::Game(Communicator& communicator, bool& twoPlayersLocal):
        running(true),
        window_width(DEF_WINDOW_WIDTH),
        window_height(DEF_WINDOW_HEIGHT),
        communicator(communicator),
        window(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
               window_height, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        twoPlayersLocal(twoPlayersLocal),
        camera(window_width, window_height) {}

void Game::init() {
    // VOLVERLOS ATRIBUTOS DE LA CLASE
    TextureManager textureManager(renderer);
    EnviromentRenderer enviromentRenderer(renderer, textureManager);
    //  VOLVERLOS ATRIBUTOS DE LA CLASE

    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping =
            createSpritesMapping(textureManager);
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    camera.loadBackgroundSize(backgroundTexture);
    EventHandler handler(window, window_width, window_height, twoPlayersLocal, communicator, ducks,
                         camera, running);

    while (running) {
        timer.iterationStartMilliseconds();
        getSnapshot();
        renderer.Clear();

        camera.update(ducks);
        float currentScale = camera.getScale();

        showBackground(backgroundTexture, currentScale);
        updatePlayers(spritesMapping, currentScale);
        updateBlocks(currentScale, enviromentRenderer);
        //  updateMap(snapshot);                        //acá updateo objetos, armas, equipo... etc
        renderer.Present();

        handler.handleEvents();

        timer.iterationEnd(30);
        //SDL_Delay(33);  // 33ms = 30fps
    }

    IMG_Quit();
}

Texture Game::startBackground() {
    SDL_Surface* rawBackgroundSurface = IMG_Load("assets/background/forest-night.png");
    Surface backgroundSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);
    return backgroundTexture;
}

void Game::getSnapshot() {
    std::optional<GameStatus> snapshot = communicator.tryRecvLast();
    if (!snapshot.has_value())
        return;

    clearObjects();
    for (auto& duck: snapshot->ducks) {
        duck.position *= 8;
        ducks.push_back(std::make_unique<DuckData>(duck));
    }
    for (const auto& blockPosition: snapshot->blockPositions) {
        blocks.push_back(std::make_unique<Vector2>(blockPosition * 8));
    }
}

void Game::updatePlayers(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping,
                         float currentScale) {
    for (auto& duck: ducks) {
        DuckID duckID = duck->duckID;
        Vector2 coords = duck->position;

        DuckState state = {duck->extraData[DuckData::PLAYING_DEAD_INDEX],
                           duck->extraData[DuckData::CROUCHING_INDEX],
                           duck->extraData[DuckData::IN_AIR_INDEX],
                           duck->extraData[DuckData::FLAPPING_INDEX],
                           duck->extraData[DuckData::BEING_DAMAGED_INDEX],
                           duck->extraData[DuckData::MOVING_RIGHT_INDEX],
                           duck->extraData[DuckData::MOVING_LEFT_INDEX],
                           /*duck->extraData[DuckData::HELMET]*/ true,
                           /*duck->extraData[DuckData::ARMOR]*/ true,
                           /*duck->extraData[DuckData::IS_SHOOTING]*/ true,
                           /*duck->gun->gunID*/ ItemID::CowboyPistol};
        // if (state.isShooting) soundManager.playSound(/*duck->gun->gunID*/ GunID::CowboyPistol);
        // falta dibujar el fire

        spritesMapping.at(duckID)->updateEquipment(state.hasHelmet,
                                                   state.hasChestplate /*, duck->gun->gunID*/);
        spritesMapping.at(duckID)->updatePosition((coords.x() - camera.getViewRect().x),
                                                  (coords.y() - camera.getViewRect().y));
        spritesMapping.at(duckID)->setScale(currentScale);
        spritesMapping.at(duckID)->update(state);
    }
}

void Game::updateBlocks(float currentScale, EnviromentRenderer& enviromentRenderer) {
    for (auto& block: blocks) {
        SDL2pp::Rect position(
            static_cast<int>((block->x()) - camera.getViewRect().x),
            static_cast<int>((block->y()) - camera.getViewRect().y),
            static_cast<int>(4 * currentScale),
            static_cast<int>(4 * currentScale)
        );
        enviromentRenderer.drawEnviroment(position, ROCK);
    }
}

void Game::showBackground(Texture& backgroundTexture, float currentScale) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    dstRect.w = static_cast<int>(window_width * currentScale);
    dstRect.h = static_cast<int>(window_height * currentScale);

    renderer.Copy(backgroundTexture, NullOpt, dstRect);
}

std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> Game::createSpritesMapping(
        TextureManager& textureManager) {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(
            DuckID::White,
            std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer,
                                            textureManager /*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Orange,
            std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer,
                                            textureManager /*, window_width, window_height*/));
    /*spritesMapping.emplace(
            DuckID::Yellow,
            std::make_unique<SpriteManager>(yellowSheet, yellowFeathers, renderer,
                                            textureManager));
    spritesMapping.emplace(DuckID::Grey, std::make_unique<SpriteManager>(
                                                 greySheet, greyFeathers, renderer,
                                                 textureManager));*/

    return spritesMapping;
}

void Game::clearObjects() {
    ducks.clear();
    // no hay que hacer blocks
}

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    SDL_Quit();
}
