#include "Game.h"

#include <algorithm>
#include <utility>

#define DEF_WINDOW_WIDTH 1040
#define DEF_WINDOW_HEIGHT 680

#define WINDOW_TITLE "DuckGame"

#define greySheet "player/greyDuck.png"
#define orangeSheet "player/orangeDuck.png"
#define whiteSheet "player/whiteDuck.png"
#define yellowSheet "player/yellowDuck.png"

#define greyFeathers "player/greyDuckFeathers.png"
#define orangeFeathers "player/orangeDuckFeathers.png"
#define whiteFeathers "player/whiteDuckFeathers.png"
#define yellowFeathers "player/yellowDuckFeathers.png"

#define ROCK "enviroment/rock.png"
#define WEAPON_SPAWNER "enviroment/spawner.png"
#define BOX "enviroment/box.png"
#define EXPLOSION "particles/Explosion.png"

#define WIN_PATH "sounds/end-effect.mp3"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::Surface;
using SDL2pp::Texture;

const HashMap<ItemID, std::string> Game::weaponSprites = {
        {ItemID::Magnum, "weapons/Magnum.png"},
        {ItemID::CowboyPistol, "weapons/CowboyPistol.png"},
        {ItemID::DuelPistol, "weapons/DuelPistol.png"},
        {ItemID::Shotgun, "weapons/Shotgun.png"},
        {ItemID::Sniper, "weapons/Sniper.png"},
        {ItemID::Ak47, "weapons/Ak47.png"},
        {ItemID::Helmet, "weapons/HelmetBig.png"},
        {ItemID::Armor, "weapons/ChestplateBig.png"}};

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

        camera.update(ducksToRender, deltaTime);
        filterObjectsToRender();

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping);
        updateBlocks(enviromentRenderer);
        updateBoxes(enviromentRenderer);
        updateItemSpawns(enviromentRenderer);
        updateItems(enviromentRenderer);
        updateEffects(enviromentRenderer);  // aca se hacer marcas de bala, explosiones, rebotes y
                                            // cascaras de banana

        hudManager.check(ducks, ducksToRender, spritesMapping);
        if (transition) {
            if (gameFinished) {
                running = false;
                continue;
            }
            transition = false;
            soundManager.playEffect(Resource::get().resource(WIN_PATH));
            auto message = std::make_unique<GameMessage>(InputAction::NEXT_ROUND, 1);
            communicator.trysend(std::move(message));
            clearObjects();
            camera.noDucksArrived();

        } else {
            renderer.Present();
        }

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
    roundFinished = snapshot->roundEnded;
    setFinished = snapshot->setEnded;
    gameFinished = snapshot->gameEnded;

    std::ranges::transform(snapshot->ducks, std::back_inserter(ducks),
                           [](DuckData& duck) { return std::move(duck); });

    for (auto& duck: snapshot->ducks)
        if (!duck.extraData.test(DuckData::Flag::Index::IsDead))
            ducksToRender.push_back(std::move(duck));

    std::ranges::transform(snapshot->blockPositions, std::back_inserter(blocks),
                           [](SizedObjectData& block) { return std::move(block); });
    std::ranges::transform(snapshot->itemSpawnerPositions, std::back_inserter(itemSpawns),
                           [](SizedObjectData& itemSpawner) { return std::move(itemSpawner); });
    std::ranges::transform(snapshot->boxPositions, std::back_inserter(boxes),
                           [](SizedObjectData& box) { return std::move(box); });
    std::ranges::transform(snapshot->itemPositions, std::back_inserter(items),
                           [](ItemData& item) { return std::move(item); });
    std::ranges::transform(snapshot->explosionPositions, std::back_inserter(explosions),
                       [](SizedObjectData& explosion) { return std::move(explosion); });
}

void Game::filterObjectsToRender() {
    const Rectangle& viewRect = camera.getViewRect();

    for (SizedObjectData& block: blocks)
        if (viewRect.overlaps(block.rectangle))
            blocksToRender.push_back(std::move(block));

    for (SizedObjectData& itemSpawn: itemSpawns)
        if (viewRect.overlaps(itemSpawn.rectangle))
            itemSpawnsToRender.push_back(std::move(itemSpawn));

    for (SizedObjectData& box: boxes)
        if (viewRect.overlaps(box.rectangle))
            boxesToRender.push_back(std::move(box));

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
                           duck.extraData[DuckData::Flag::Index::IsMoving],
                           duck.extraData[DuckData::Flag::Index::Helmet],
                           duck.extraData[DuckData::Flag::Index::Armor],
                           duck.extraData[DuckData::Flag::Index::IsShooting],
                           duck.extraData[DuckData::Flag::Index::LookingUp],
                           flipped,
                           hasGun,
                           duck.extraData[DuckData::Flag::Index::NoMoreBullets],
                           duck.extraData[DuckData::Flag::Index::IsDead],
                           duck.gunID,
                           duck.direction};

        soundManager.checkSounds(state);

        if (!duck.bulletsFromGun.empty())
            bulletPositions.push_back(duck.bulletsFromGun);

        spritesMapping.at(duck.duckID)->updatePosition(screenPositionX, screenPositionY);
        spritesMapping.at(duck.duckID)->setScale(scale);
        spritesMapping.at(duck.duckID)->update(state);
    }
}

void Game::updateBlocks(EnviromentRenderer& enviromentRenderer) {
    for (Rect& block: calculateObjectsPositionsAndSize(blocksToRender))
        enviromentRenderer.drawEnviroment(block, Resource::get().resource(ROCK).c_str());
}

void Game::updateItemSpawns(EnviromentRenderer& enviromentRenderer) {
    for (Rect& itemSpawn: calculateObjectsPositionsAndSize(itemSpawnsToRender))
        enviromentRenderer.drawEnviroment(itemSpawn,
                                          Resource::get().resource(WEAPON_SPAWNER).c_str());
}

void Game::updateBoxes(EnviromentRenderer& enviromentRenderer) {
    for (Rect& box: calculateObjectsPositionsAndSize(boxesToRender))
        enviromentRenderer.drawEnviroment(box, Resource::get().resource(BOX).c_str());
}

void Game::updateItems(EnviromentRenderer& enviromentRenderer) {
    std::list<Rect> rectsToDraw = calculateObjectsPositionsAndSize(itemsToRender);
    auto rectsIt = rectsToDraw.begin();
    auto itemsIt = itemsToRender.begin();

    while (rectsIt != rectsToDraw.end() && itemsIt != itemsToRender.end()) {
        enviromentRenderer.drawEnviroment(
                *rectsIt, Resource::get().resource(weaponSprites.at(itemsIt->id)).c_str());
        ++rectsIt;
        ++itemsIt;
    }
}

void Game::updateEffects(EnviromentRenderer& enviromentRenderer) {
    if (!bulletPositions.empty()) {
        std::list<Segment2D> flattenedBulletPositions;
        for (const auto& bulletList: bulletPositions) {
            flattenedBulletPositions.insert(flattenedBulletPositions.end(), bulletList.begin(),
                                            bulletList.end());
        }
        std::list<std::pair<Vector2, Vector2>> bulletPositions =
                calculateSegmentPositionsAndSize(flattenedBulletPositions);
        enviromentRenderer.drawBullets(bulletPositions);
    }

    for (Rect& explosion: calculateObjectsPositionsAndSize(explosions)) {
        enviromentRenderer.drawEnviroment(explosion,
                                          Resource::get().resource(EXPLOSION).c_str());
        //play sound
    }
}

    // y aca dibujo rebotes, explosiones y cascara
    // usando UNA lista sola de posiciones generales y filtrando usando un enum y/o map ?

std::list<std::pair<Vector2, Vector2>> Game::calculateSegmentPositionsAndSize(
        std::list<Segment2D>& segments) {
    std::list<std::pair<Vector2, Vector2>> positionsToDraw;

    for (auto& segment: segments) {
        Segment2D cutSegment = segment.cut(20.0f);
        const float positionScaleX =
                static_cast<float>(window_width) / camera.getViewRect().size().x();
        const float positionScaleY =
                static_cast<float>(window_height) / camera.getViewRect().size().y();

        const float startX =
                (cutSegment.start().x() - camera.getViewRect().center().x()) * positionScaleX +
                static_cast<float>(window_width) / 2;
        const float startY =
                (cutSegment.start().y() - camera.getViewRect().center().y()) * positionScaleY +
                static_cast<float>(window_height) / 2;
        const float endX =
                (cutSegment.end().x() - camera.getViewRect().center().x()) * positionScaleX +
                static_cast<float>(window_width) / 2;
        const float endY =
                (cutSegment.end().y() - camera.getViewRect().center().y()) * positionScaleY +
                static_cast<float>(window_height) / 2;

        positionsToDraw.emplace_back(Vector2(startX, startY), Vector2(endX, endY));
    }

    return positionsToDraw;
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

    spritesMapping.emplace(
            DuckData::Id::White,
            std::make_unique<SpriteManager>(Resource::get().resource(whiteSheet),
                                            Resource::get().resource(whiteFeathers), renderer));
    spritesMapping.emplace(
            DuckData::Id::Orange,
            std::make_unique<SpriteManager>(Resource::get().resource(orangeSheet),
                                            Resource::get().resource(orangeFeathers), renderer));
    spritesMapping.emplace(
            DuckData::Id::Yellow,
            std::make_unique<SpriteManager>(Resource::get().resource(yellowSheet),
                                            Resource::get().resource(yellowFeathers), renderer));
    spritesMapping.emplace(
            DuckData::Id::Grey,
            std::make_unique<SpriteManager>(Resource::get().resource(greySheet),
                                            Resource::get().resource(greyFeathers), renderer));

    return spritesMapping;
}

void Game::clearObjects() {
    ducks.clear();
    ducksToRender.clear();
    blocks.clear();
    blocksToRender.clear();
    itemSpawns.clear();
    itemSpawnsToRender.clear();
    items.clear();
    itemsToRender.clear();
    boxes.clear();
    boxesToRender.clear();
    bulletPositions.clear();
    explosions.clear();
}

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    IMG_Quit();
    SDL_Quit();
}
