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

const HashMap<ItemID, cppstring> Game::weaponSprites = {
        {ItemID::Magnum, "assets/weapons/Magnum.png"},
        {ItemID::CowboyPistol, "assets/weapons/CowboyPistol.png"}};

Game::Game(Communicator& communicator, bool& twoPlayersLocal):
        running(true),
        roundFinished(false),
        setFinished(false),
        gameFinished(false),
        transition(false),
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
    HudManager hudManager(window_width, window_height, renderer, transition, roundFinished,
                          setFinished, gameFinished);

    const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>> spritesMapping =
            createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    EventHandler handler(window, window_width, window_height, twoPlayersLocal, communicator, ducks,
                         camera, running);

    while (running) {
        const float deltaTime = timer.iterationStartSeconds().count();
        getSnapshot();

        renderer.Clear();

        camera.update(ducks, deltaTime);
        filterObjectsToRender();

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping);
        updateBlocks(enviromentRenderer);
        updateItemSpawns(enviromentRenderer);
        updateItems(enviromentRenderer);

        roundFinished = true;
        hudManager.check(ducks, ducksToRender, spritesMapping);
        if (transition) {
            transition = false;
            auto message = std::make_unique<GameMessage>(InputAction::NEXT_ROUND, 1);
            communicator.trysend(std::move(message));

        } else {
            renderer.Present();
        }  // the renderer is presented inside the hudManager if the round/set/game is finished. in
           // other case...

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
    //roundFinished = snapshot->roundOver;
    //setFinished = snapshot->setOver;
    // gameFinished = snapshot->gameOver;

    for (auto& duck: snapshot->ducks) ducks.push_back(std::move(duck));
    for (auto& duck: snapshot->ducks) {
        if (!duck.extraData[DuckData::Flag::Index::IsDead]) {
            ducksToRender.push_back(std::move(duck));
        }
    }
    for (const auto& block: snapshot->blockPositions) blocks.push_back(block);
    for (const auto& itemSpawner: snapshot->itemSpawnerPositions) itemSpawns.push_back(itemSpawner);
    for (const auto& item: snapshot->itemPositions) items.push_back(item);
}

void Game::filterObjectsToRender() {
    const Rectangle& viewRect = camera.getViewRect();

    for (SizedObjectData& block: blocks)
        if (viewRect.overlaps(block.rectangle))
            blocksToRender.push_back(std::move(block));

    for (SizedObjectData& itemSpawn: itemSpawns)
        if (viewRect.overlaps(itemSpawn.rectangle))
            itemSpawnsToRender.push_back(std::move(itemSpawn));

    for (ItemData& item: items)
        if (viewRect.overlaps(item.rectangle))
            itemsToRender.push_back(std::move(item));
}

#define DUCK_WIDTH 2

void Game::updatePlayers(
        const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) {
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


        bool flipped = duck.direction == DuckData::Direction::Left;
        bool hasGun = duck.gunID != ItemID::NONE;
        DuckState state = {duck.extraData[DuckData::Flag::Index::PlayingDead],
                           duck.extraData[DuckData::Flag::Index::InAir],
                           duck.extraData[DuckData::Flag::Index::Flapping],
                           duck.extraData[DuckData::Flag::Index::BeingDamaged],
                           duck.extraData[DuckData::Flag::Index::IsMoving],
                           duck.extraData[DuckData::Flag::Index::Helmet],
                           duck.extraData[DuckData::Flag::Index::Armor],
                           duck.extraData[DuckData::Flag::Index::IsShooting],
                           duck.extraData[DuckData::Flag::Index::LookingUp],
                           flipped, hasGun, duck.extraData[DuckData::Flag::Index::NoMoreBullets],
                           duck.gunID, duck.direction};

        soundManager.checkSounds(state);

        spritesMapping.at(duck.duckID)->updatePosition(screenPositionX, screenPositionY);
        spritesMapping.at(duck.duckID)->setScale(scale);
        spritesMapping.at(duck.duckID)->update(state);
    }
}

void Game::updateBlocks(EnviromentRenderer& enviromentRenderer) {
    for (Rect& block: calculateObjectsPositionsAndSize(blocksToRender))
        enviromentRenderer.drawEnviroment(block, ROCK);
}

void Game::updateItemSpawns(EnviromentRenderer& enviromentRenderer) {
    for (Rect& itemSpawn: calculateObjectsPositionsAndSize(itemSpawnsToRender))
        enviromentRenderer.drawEnviroment(itemSpawn, WEAPON_SPAWNER);
}

void Game::updateItems(EnviromentRenderer& enviromentRenderer) {
    std::list<Rect> rectsToDraw = calculateObjectsPositionsAndSize(itemsToRender);
    auto rectsIt = rectsToDraw.begin();
    auto itemsIt = itemsToRender.begin();

    while (rectsIt != rectsToDraw.end() && itemsIt != itemsToRender.end()) {
        enviromentRenderer.drawEnviroment(*rectsIt, weaponSprites.at(itemsIt->id));
        ++rectsIt;
        ++itemsIt;
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

std::unordered_map<DuckData::Id, std::unique_ptr<SpriteManager>> Game::createSpritesMapping() {
    std::unordered_map<DuckData::Id, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(DuckData::Id::White,
                           std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer));
    spritesMapping.emplace(DuckData::Id::Orange,
                           std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer));
    spritesMapping.emplace(DuckData::Id::Yellow,
                           std::make_unique<SpriteManager>(yellowSheet, yellowFeathers, renderer));
    spritesMapping.emplace(DuckData::Id::Grey,
                           std::make_unique<SpriteManager>(greySheet, greyFeathers, renderer));

    return spritesMapping;
}

void Game::clearObjects() {
    ducks.clear();
    blocks.clear();
    blocksToRender.clear();
    itemSpawns.clear();
    itemSpawnsToRender.clear();
    items.clear();
    itemsToRender.clear();
}

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    IMG_Quit();
    SDL_Quit();
}
