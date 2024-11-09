#include "Game.hpp"

#define SCALE 2.5f

#define DEF_WINDOW_WIDTH 1040
#define DEF_WINDOW_HEIGHT 680

#define greySheet "../assets/player/greyDuck.png"
#define orangeSheet "../assets/player/orangeDuck.png"
#define whiteSheet "../assets/player/whiteDuck.png"
#define yellowSheet "../assets/player/yellowDuck.png"

#define greyFeathers "../assets/player/greyDuckFeathers.png"
#define orangeFeathers "../assets/player/orangeDuckFeathers.png"
#define whiteFeathers "../assets/player/whiteDuckFeathers.png"
#define yellowFeathers "../assets/player/yellowDuckFeathers.png"

// Here we should just declare the classes that are use in this file. But for now a NOLINT is fine.
using namespace SDL2pp;  // NOLINT(build/namespaces)

Game::Game(Communicator& communicator, bool& twoPlayersLocal):
        running(true),
        window_width(DEF_WINDOW_WIDTH),
        window_height(DEF_WINDOW_HEIGHT),
        communicator(communicator),
        window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
               window_height, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        twoPlayersLocal(twoPlayersLocal), camera(window_width, window_height){}

void Game::init() {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping = createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    camera.loadBackgroundSize(backgroundTexture);

    while (running) {
        getSnapshot();
        renderer.Clear();

        camera.update(ducks);
        float currentScale = camera.getScale();

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping, currentScale);
        // updateMap(snapshot);                        //acá updateo objetos, armas, equipo... etc
        renderer.Present();
        clearObjects();

        handleEvents(spritesMapping);  // y según lo que pase acá... lo envío

        SDL_Delay(33);  // 33ms = 30fps
    }

    IMG_Quit();
}

Texture Game::startBackground() {
    SDL_Surface* rawBackgroundSurface = IMG_Load("../assets/background/background1.png");
    Surface backgroundSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);
    return backgroundTexture;
}

void Game::getSnapshot() {
    std::optional<GameStatus> snapshot = communicator.tryrecv();
    if (!snapshot.has_value()) return;


    clearObjects();
    for (auto& gameObject: snapshot->gameObjects) {
        switch (gameObject->objectID) {
            case GameObjectID::Object2D: {
                auto* object2D = dynamic_cast<GameObject2DData*>(gameObject.get());
                if (object2D->object2DID == GameObject2DID::Duck) {
                    ducks.push_back(std::unique_ptr<DuckData>(
                            dynamic_cast<DuckData*>(gameObject.release())));
                }

                // if (timer)

                else {
                    // typeOfObject2D(std::unique_ptr<GameObject2DData>(static_cast<GameObject2DData*>(gameObject.release())));
                }
                break;
            }
            default:
                break;
        }
    }
}

void Game::updatePlayers(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping, float currentScale) {
    for (auto& duck: ducks) {
        DuckID duckID = duck->duckID;
        Vector2 coords = duck->position;
        spritesMapping.at(duckID)->updatePosition(coords.x() - camera.getViewRect().x, coords.y() - camera.getViewRect().y);
        spritesMapping.at(duckID)->setScale(currentScale);
        spritesMapping.at(duckID)->update(duck->extraData[DuckData::PLAYING_DEAD_INDEX],
                                         duck->extraData[DuckData::CROUCHING_INDEX],
                                         duck->extraData[DuckData::IN_AIR_INDEX],
                                         duck->extraData[DuckData::FLAPPING_INDEX],
                                         duck->extraData[DuckData::BEING_DAMAGED_INDEX],
                                         duck->extraData[DuckData::MOVING_RIGHT_INDEX],
                                         duck->extraData[DuckData::MOVING_LEFT_INDEX]);
    }
}


/*void Game::typeOfObject2D(std::unique_ptr<GameObject2DData> gameObject2D) {
    switch (gameObject2D->id()) {
        case GameObject2DID::GUN:
            weapons.push_back(?);
        break;
        case GameObject2DID::BULLET:
            bullets.push_back(?);
        break;
        case GameObject2DID::WALL:
            blocks.push_back(?);
        break;
        case GameObject2DID::TIMER:
            if (gameObject2D.timeToFinish == 0) {
                running = false;
                break;
                default:
                    break;
            }
    }
}*/

void Game::showBackground(Texture& backgroundTexture) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    dstRect.w = window_width;
    dstRect.h = window_height;

    renderer.Copy(backgroundTexture, NullOpt, dstRect);
}

std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> Game::createSpritesMapping() {
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> spritesMapping;

    spritesMapping.emplace(
            DuckID::White,
            std::make_unique<SpriteManager>(whiteSheet, whiteFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Orange,
            std::make_unique<SpriteManager>(orangeSheet, orangeFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Yellow,
            std::make_unique<SpriteManager>(yellowSheet, yellowFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(DuckID::Grey, std::make_unique<SpriteManager>(greySheet, greyFeathers,
                                                       renderer /*, window_width, window_height*/));

    return spritesMapping;
}

void Game::handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown) {
    const auto& keyMapping = isKeyDown ? keyMappingPressed : keyMappingReleased;
    auto it = keyMapping.find(scancode);
    if (it != keyMapping.end()) {
        InputAction m_key = it->second;
        auto message = std::make_unique<GameMessage>(m_key, 1);
        communicator.trysend(std::move(message));
    }

    if (twoPlayersLocal) {
        const auto& keyMappingPlayer2 = isKeyDown ? keyMappingPressedPlayer2 : keyMappingReleasedPlayer2;
        auto it2 = keyMappingPlayer2.find(scancode);
        if (it2 != keyMappingPlayer2.end()) {
            InputAction m_key = it2->second;
            auto message = std::make_unique<GameMessage>(m_key, 2);
            communicator.trysend(std::move(message));
        }
    }
}

void Game::handleEvents(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            bool isKeyDown = (event.type == SDL_KEYDOWN);
            handleKeyEvent(scancode, isKeyDown);
            handleScreenEvents(event, isKeyDown, scancode, spritesMapping);

        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Game::handleScreenEvents(SDL_Event& event, bool isKeyDown, SDL_Scancode& scancode, std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping) {
    if (isKeyDown && scancode == SDL_SCANCODE_F11) {
        if (isFullscreen(window)) {
            setFullscreen(false);
        } else {
            setFullscreen(true);
        }
    } else if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            SDL_GetWindowSize(window.Get(), &window_width, &window_height);
            camera.update(ducks);
            float currentScale = camera.getScale();
            updatePlayers(spritesMapping, currentScale);
        }
    }
}

bool Game::isFullscreen(Window& window) {
    Uint32 flags = SDL_GetWindowFlags(window.Get());
    return (flags & SDL_WINDOW_FULLSCREEN) || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Game::setFullscreen(bool fullscreen) {
    if (fullscreen) {
        SDL_SetWindowFullscreen(window.Get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(window.Get(), 0);
    }
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
}


/*void Game::selectLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);

    int randomLevel = dis(gen);

    selectedLevel = levels[randomLevel];
}*/

void Game::clearObjects() { ducks.clear(); }

Game::~Game() {
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    SDL_Quit();
}
