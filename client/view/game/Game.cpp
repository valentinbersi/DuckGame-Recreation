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
    //renderer.Present();

    while (running) {
        getSnapshot();
        renderer.Clear();

        // corroboro que ningún duck se haya ido de la pantalla. si es así, debo quitar zoom de la
        // pantalla en otro caso, si todos los patos están a más de X pixeles de lejanía los bordes,
        // hago un zoom de Y pixeles esto lo puedo guardar en alguna variable y luego DIBUJAR EL
        // BACKGROUND acorde para esto poner una funcion a vector2 que haga un promedio de los
        // vectores

        camera.update(ducks);
        float currentScale = camera.getScale();

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping, currentScale);
        // updateMap(snapshot);                        //acá updateo objetos, armas, equipo... etc
        renderer.Present();
        clearObjects();

        handleEvents();  // y según lo que pase acá... lo envío

        SDL_Delay(33);  // 33ms = 30fps



        /*
        handleEvents();       // handle user input
        renderer.Clear();
        showBackground(backgroundTexture);
        update(player1);             //update ducks
        //render();         render EVERYTHING again (outside players, that are being rendered in the player class)
        SDL_Delay(33);
        */
    }


    IMG_Quit();
}

void Game::getSnapshot() {
    std::unique_ptr<GameStatus> snapshot;

    std::optional<std::unique_ptr<ServerMessage>> optionalMessage = communicator.tryRecvLast();
    if (optionalMessage.has_value()) {
        std::unique_ptr<ServerMessage> message = std::move(optionalMessage.value());
        snapshot = std::unique_ptr<GameStatus>(dynamic_cast<GameStatus*>(message.release()));
    } else return;


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

void Game::clearObjects() { ducks.clear(); }

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

void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            bool isKeyDown = (event.type == SDL_KEYDOWN);
            handleKeyEvent(scancode, isKeyDown);
        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

Texture Game::startBackground() {
    SDL_Surface* rawBackgroundSurface = IMG_Load("../assets/background/background1.png");
    Surface backgroundSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);
    return backgroundTexture;
}

void Game::showBackground(Texture& backgroundTexture) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    dstRect.w = window_width;
    dstRect.h = window_height;

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
    // SDL_DestroyRenderer(renderer.Get());
    // SDL_DestroyWindow(window.Get());
    SDL_Quit();
}
