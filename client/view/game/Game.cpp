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
    EnviromentRenderer enviromentRenderer(renderer);
    //  VOLVERLOS ATRIBUTOS DE LA CLASE

    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping =
            createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    //camera.loadBackgroundSize(backgroundTexture);
    EventHandler handler(window, window_width, window_height, twoPlayersLocal, communicator, ducks,
                         camera, running);

    while (running) {
        timer.iterationStartMilliseconds();
        getSnapshot();
        renderer.Clear();

        camera.update(ducks);
        filterObjectsToRender();

        float currentScale = camera.getScale();

        showBackground(backgroundTexture, currentScale);
        updatePlayers(spritesMapping);
        updateBlocks(enviromentRenderer);
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
    // SDL_FreeSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);
    return backgroundTexture;
}

void Game::getSnapshot() {
    std::optional<GameStatus> snapshot = communicator.tryRecvLast();
    if (!snapshot.has_value())
        return;

    clearObjects();
    for (auto& duck: snapshot->ducks) ducks.push_back(std::move(duck));
    for (const auto& block: snapshot->blockPositions) blocks.push_back(std::move(block));

}

void Game::filterObjectsToRender() {
    Rectangle& viewRect = camera.getViewRect();

    for (auto duck = ducks.begin(); duck != ducks.end(); ++duck)
        if (viewRect.overlaps(duck->rectangle))
            ducksToRender.splice(ducksToRender.end(), ducks, duck);

    for (auto block = blocks.begin(); block != blocks.end(); ++block)
        if (viewRect.overlaps(block->rectangle))
            blocksToRender.splice(blocksToRender.end(), blocks, block);
}

#define DUCK_WIDTH 2

void Game::updatePlayers(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping) {
    float objectCameraSize = camera.getViewRect().size().x() / DUCK_WIDTH;
    float scale = static_cast<float>(window_width) / objectCameraSize;

    for (auto& duck: ducks) {
        DuckID duckID = duck.duckID;
        Vector2 coords = duck.rectangle.position();

        DuckState state = {duck.extraData[DuckData::PLAYING_DEAD_INDEX],
                           duck.extraData[DuckData::CROUCHING_INDEX],
                           duck.extraData[DuckData::IN_AIR_INDEX],
                           duck.extraData[DuckData::FLAPPING_INDEX],
                           duck.extraData[DuckData::BEING_DAMAGED_INDEX],
                           duck.extraData[DuckData::MOVING_RIGHT_INDEX],
                           duck.extraData[DuckData::MOVING_LEFT_INDEX],
                           /*duck.extraData[DuckData::HELMET]*/ true,
                           /*duck.extraData[DuckData::ARMOR]*/ true,
                           /*duck.extraData[DuckData::IS_SHOOTING]*/ true,
                           /*duck.gun->gunID*/ GunID::CowboyPistol};
        // if (state.isShooting) soundManager.playSound(/*duck.gun->gunID*/ GunID::CowboyPistol);
        // falta dibujar el fire

        spritesMapping.at(duckID)->updateEquipment(state.hasHelmet,
                                                   state.hasChestplate /*, duck->gun->gunID*/);
        spritesMapping.at(duckID)->updatePosition(coords.x() - camera.getViewRect().position().x(),
                                                  coords.y() - camera.getViewRect().position().y());
        spritesMapping.at(duckID)->setScale(scale);
        spritesMapping.at(duckID)->update(state);
    }
}

void Game::updateBlocks(EnviromentRenderer& enviromentRenderer) {
    float objectCameraSize = camera.getViewRect().size().x() / 2;
    float scale = static_cast<float>(window_width) / objectCameraSize;

    for (auto& block: blocks) {

        SDL2pp::Rect position(static_cast<int>(block.rectangle.position().x() - camera.getViewRect().position().x()),
                              static_cast<int>(block.rectangle.position().y() - camera.getViewRect().position().y()),
                              static_cast<int>(2 * scale), static_cast<int>(2 * scale));
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

std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> Game::createSpritesMapping() {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(
            DuckID::White,
            std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer/*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Orange,
            std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer/*, window_width, window_height*/));
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
