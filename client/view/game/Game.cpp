#include "Game.hpp"

#include <utility>

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
    EnviromentRenderer enviromentRenderer(renderer);
    //  VOLVERLO ATRIBUTO DE LA CLASE

    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping =
            createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    // camera.loadBackgroundSize(backgroundTexture);
    EventHandler handler(window, window_width, window_height, twoPlayersLocal, communicator, ducks,
                         camera, running);

    while (running) {
        timer.iterationStartMilliseconds();
        getSnapshot();
        renderer.Clear();

        camera.update(ducks);
        filterObjectsToRender();

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping);
        updateBlocks(enviromentRenderer);
        //  updateMap(snapshot);                        //acá updateo objetos, armas, equipo... etc
        renderer.Present();

        handler.handleEvents();

        timer.iterationEnd(30);
    }

    IMG_Quit();
}

Texture Game::startBackground() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(0, backgrounds.size() - 1);

    std::size_t randomIndex = dis(gen);
    SDL_Surface* rawBackgroundSurface = IMG_Load(backgrounds[randomIndex].c_str());
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
    for (const auto& block: snapshot->blockPositions) blocks.push_back(block);
}

void Game::filterObjectsToRender() {
    const Rectangle& viewRect = camera.getViewRect();

    for (auto& duck: ducks)
        if (viewRect.overlaps(duck.rectangle))
            ducksToRender.push_back(duck);

    for (auto& block: blocks)
        if (viewRect.overlaps(block.rectangle))
            blocksToRender.push_back(block);
}

#define DUCK_WIDTH 2

void Game::updatePlayers(
        std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping) {
    const float objectCameraSize = camera.getViewRect().size().x() / DUCK_WIDTH;
    const float scale = static_cast<float>(window_width) / objectCameraSize;

    for (auto& duck: ducksToRender) {
        DuckID duckID = duck.duckID;
        Vector2 coords = duck.position;

        const float relativePositionX = coords.x() - camera.getViewRect().center().x();
        const float relativePositionY = coords.y() - camera.getViewRect().center().y();
        const float positionScaleX =
                static_cast<float>(window_width) / camera.getViewRect().size().x();
        const float positionScaleY =
                static_cast<float>(window_height) / camera.getViewRect().size().y();
        const float screenPositionX =
                relativePositionX * positionScaleX + static_cast<float>(window_width) / 2;
        const float screenPositionY =
                relativePositionY * positionScaleY + static_cast<float>(window_height) / 2;

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
                           /*duck.gun->gunID*/ ItemID::CowboyPistol};
        // if (state.isShooting) soundManager.playSound(/*duck.gun->gunID*/ GunID::CowboyPistol);
        // falta dibujar el fire

        spritesMapping.at(duckID)->updateEquipment(state.hasHelmet,
                                                   state.hasChestplate /*, duck->gun->gunID*/);
        spritesMapping.at(duckID)->updatePosition(screenPositionX, screenPositionY);
        spritesMapping.at(duckID)->setScale(scale);
        spritesMapping.at(duckID)->update(state);
    }
}

void Game::updateBlocks(EnviromentRenderer& enviromentRenderer) {
    const float objectCameraSize = camera.getViewRect().size().x() / 2;
    const float scale = static_cast<float>(window_width) / objectCameraSize;

    for (auto& block: blocksToRender) {
        const float relativePositionX = block.position.x() - camera.getViewRect().center().x();
        const float relativePositionY = block.position.y() - camera.getViewRect().center().y();
        const float positionScaleX =
                static_cast<float>(window_width) / camera.getViewRect().size().x();
        const float positionScaleY =
                static_cast<float>(window_height) / camera.getViewRect().size().y();
        const float screenPositionX =
                relativePositionX * positionScaleX + static_cast<float>(window_width) / 2;
        const float screenPositionY =
                relativePositionY * positionScaleY + static_cast<float>(window_height) / 2;

        SDL2pp::Rect position(screenPositionX - scale / 2, screenPositionY - scale / 2,
                              static_cast<int>(scale), static_cast<int>(scale));
        enviromentRenderer.drawEnviroment(position, ROCK);
    }
}

void Game::showBackground(Texture& backgroundTexture /*, float currentScale*/) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    dstRect.w = window_width;
    dstRect.h = window_height;
    // dstRect.w = static_cast<int>(window_width * currentScale);
    // dstRect.h = static_cast<int>(window_height * currentScale);

    renderer.Copy(backgroundTexture, NullOpt, dstRect);
}

std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> Game::createSpritesMapping() {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(DuckID::White,
                           std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer));
    spritesMapping.emplace(DuckID::Orange,
                           std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer));
    /*spritesMapping.emplace(
            DuckID::Yellow,
            std::make_unique<SpriteManager>(yellowSheet, yellowFeathers, renderer));
    spritesMapping.emplace(DuckID::Grey, std::make_unique<SpriteManager>(
                                                 greySheet, greyFeathers, renderer));*/

    return spritesMapping;
}

void Game::clearObjects() {
    ducks.clear();
    ducksToRender.clear();
    blocks.clear();
    blocksToRender.clear();
}

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    SDL_Quit();
}
