#include "Game.h"

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
#define WEAPON_SPAWNER "assets/enviroment/spawner.png"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
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

#define FPS 30

void Game::init() {
    EnviromentRenderer enviromentRenderer(renderer);

    const HashMap<DuckID, std::unique_ptr<SpriteManager>> spritesMapping = createSpritesMapping();
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
        updateWeaponSpawns(enviromentRenderer);
        // updateMap(snapshot);                        //acá updateo objetos, armas, equipo... etc
        renderer.Present();

        handler.handleEvents();

        timer.iterationEnd(FPS);
    }
}

Texture Game::startBackground() {
    RandomIntGenerator random(0, backgrounds.size() - 1);
    const std::size_t randomIndex = random.generateRandomInt();
    SDL_Surface* rawBackgroundSurface = IMG_Load(backgrounds[randomIndex].c_str());
    const Surface backgroundSurface(rawBackgroundSurface);
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
    for (const auto& itemSpawner: snapshot->itemSpawnerPositions) itemSpawns.push_back(itemSpawner);
    // for (const auto& spawner: snapshot->spawnerPosition) spawners.push_back(spawner);
    // for (const auto& weapon: snapshot->weaponPosition) weapons.push_back(weapon);
}

void Game::filterObjectsToRender() {
    const Rectangle& viewRect = camera.getViewRect();

    for (SizedObjectData& block: blocks)
        if (viewRect.overlaps(block.rectangle))
            blocksToRender.push_back(std::move(block));

    for (SizedObjectData& itemSpawn: itemSpawns)
        if (viewRect.overlaps(itemSpawn.rectangle))
            itemSpawnsToRender.push_back(std::move(itemSpawn));
}

#define DUCK_WIDTH 2

void Game::updatePlayers(const HashMap<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping) {
    const float objectCameraCount = camera.getViewRect().size().x() / DUCK_WIDTH;
    const float scale = static_cast<float>(window_width) / objectCameraCount;

    for (auto& duck: ducks) {
        const float relativePositionX = duck.position.x() - camera.getViewRect().center().x();
        const float relativePositionY = duck.position.y() - camera.getViewRect().center().y();
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
                           duck.extraData[DuckData::HELMET],
                           duck.extraData[DuckData::ARMOR],
                           duck.extraData[DuckData::IS_SHOOTING],
                           duck.gunID};

        if (state.isShooting)
            soundManager.playSound(/*duck.gun->gunID*/ ItemID::CowboyPistol);

        spritesMapping.at(duck.duckID)
                ->updateEquipment(state.hasHelmet, state.hasChestplate, duck.gunID);
        spritesMapping.at(duck.duckID)->updatePosition(screenPositionX, screenPositionY);
        spritesMapping.at(duck.duckID)->setScale(scale);
        spritesMapping.at(duck.duckID)->update(state);
    }
}

#define BLOCK_WIDTH 2

void Game::updateBlocks(EnviromentRenderer& enviromentRenderer) {
    const float objectCameraSize = camera.getViewRect().size().x() / BLOCK_WIDTH;
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

        Rect position(static_cast<int>(screenPositionX - scale / 2),
                      static_cast<int>(screenPositionY - scale / 2), static_cast<int>(scale),
                      static_cast<int>(scale));
        enviromentRenderer.drawEnviroment(position, ROCK);
    }
}

#define WEAPON_SPAWN_WIDTH 3.5

void Game::updateWeaponSpawns(EnviromentRenderer& enviromentRenderer) {
    const float spawnerCameraSize = camera.getViewRect().size().x() / WEAPON_SPAWN_WIDTH;
    const float scale = static_cast<float>(window_width) / spawnerCameraSize;

    for (SizedObjectData& itemSpawn: itemSpawnsToRender) {
        const float relativePositionX = itemSpawn.position.x() - camera.getViewRect().center().x();
        const float relativePositionY = itemSpawn.position.y() - camera.getViewRect().center().y();
        const float positionScaleX =
                static_cast<float>(window_width) / camera.getViewRect().size().x();
        const float positionScaleY =
                static_cast<float>(window_height) / camera.getViewRect().size().y();
        const float screenPositionX =
                relativePositionX * positionScaleX + static_cast<float>(window_width) / 2;
        const float screenPositionY =
                relativePositionY * positionScaleY + static_cast<float>(window_height) / 2;

        Rect position(static_cast<int>(screenPositionX - scale / 2),
                      static_cast<int>(screenPositionY - scale / 2), static_cast<int>(scale),
                      static_cast<int>(scale));
        enviromentRenderer.drawEnviroment(position, WEAPON_SPAWNER);
    }
}

void Game::showBackground(Texture& backgroundTexture) {
    Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    dstRect.w = window_width;
    dstRect.h = window_height;

    renderer.Copy(backgroundTexture, NullOpt, dstRect);
}

std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> Game::createSpritesMapping() {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(DuckID::White,
                           std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer));
    spritesMapping.emplace(DuckID::Orange,
                           std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer));
    spritesMapping.emplace(DuckID::Yellow,
                           std::make_unique<SpriteManager>(yellowSheet, yellowFeathers, renderer));
    spritesMapping.emplace(DuckID::Grey,
                           std::make_unique<SpriteManager>(greySheet, greyFeathers, renderer));

    return spritesMapping;
}

void Game::clearObjects() {
    ducks.clear();
    blocks.clear();
    blocksToRender.clear();
    itemSpawns.clear();
    itemSpawnsToRender.clear();
}

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    IMG_Quit();
    SDL_Quit();
}
