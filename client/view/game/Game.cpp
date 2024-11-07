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
        twoPlayersLocal(twoPlayersLocal){}

void Game::init() {
    std::unordered_map<DuckID, SpriteManager> spritesMapping = createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    renderer.Present();

    while (running) {
        getSnapshot();  // handle everything sended by the gameloop
        // Vector2 center = centerOfDucks();

        renderer.Clear();

        // corroboro que ningún duck se haya ido de la pantalla. si es así, debo quitar zoom de la
        // pantalla en otro caso, si todos los patos están a más de X pixeles de lejanía los bordes,
        // hago un zoom de Y pixeles esto lo puedo guardar en alguna variable y luego DIBUJAR EL
        // BACKGROUND acorde para esto poner una funcion a vector2 que haga un promedio de los
        // vectores

        showBackground(backgroundTexture);
        updatePlayers(spritesMapping);
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
    } else {
        return;
    }

    // aca deberia conseguir los diversos duck data hasta que en el casteo dinamico me de nullptr
    // en ese caso no habrán más ducks y ya entraré a los objetos

    // acomodarme cosas en sublistas. sublistas de patos, de armas, de bloques, objetos... etc
    // al final hago clear a cada sublista y vuelvo a obtener una nueva snapshot
    // para esto puedo mover punteros para lo que necesito

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

void Game::updatePlayers(std::unordered_map<DuckID, SpriteManager>& spritesMapping) {
    for (auto& duck: ducks) {
        DuckID duckID = duck->duckID;
        Vector2 coords = duck->position;
        spritesMapping.at(duckID).updatePosition(coords.x(), coords.y());
        spritesMapping.at(duckID).update(duck->extraData[DuckData::PLAYING_DEAD_INDEX],
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


Vector2 Game::centerOfDucks() {
    float coordsX = 0.0f;
    float coordsY = 0.0f;
    size_t duckCount = ducks.size();

    for (auto& duck: ducks) {
        coordsX += duck->position.x();
        coordsY += duck->position.y();
    }

    if (duckCount > 0) {
        coordsX /= static_cast<float>(duckCount);
        coordsY /= static_cast<float>(duckCount);
    }

    Vector2 result(coordsX, coordsY);
    return result;

    // dividirlo por el numero por el que se multiplicó (dicho por valen etc (preguntar numero
    // exacto))
}

void Game::clearObjects() { ducks.clear(); }

std::unordered_map<DuckID, SpriteManager> Game::createSpritesMapping() {
    std::unordered_map<DuckID, SpriteManager> spritesMapping;

    spritesMapping.emplace(
            DuckID::White,
            SpriteManager(whiteSheet, whiteFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Orange,
            SpriteManager(orangeSheet, orangeFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(
            DuckID::Yellow,
            SpriteManager(yellowSheet, yellowFeathers, renderer /*, window_width, window_height*/));
    spritesMapping.emplace(DuckID::Grey, SpriteManager(greySheet, greyFeathers,
                                                       renderer /*, window_width, window_height*/));

    return spritesMapping;
}

// ANOTHER FORM... (I think this is better, but i'm not sure)

/*std::unordered_map<DuckID, SpriteManager>& createSpritesMapping(SDL2pp::Renderer& renderer) {
    static std::unordered_map<DuckID, SpriteManager> spritesMapping;

    const std::vector<std::pair<DuckID, std::pair<const char*, const char*>>> duckData = {
        {DuckID::White, {whiteSheet, whiteFeathers}},
        {DuckID::Orange, {orangeSheet, orangeFeathers}},
        {DuckID::Yellow, {yellowSheet, yellowFeathers}},
        {DuckID::Grey, {greySheet, greyFeathers}}
    };

    for (const auto& data : duckData) {
        SDL2pp::Texture textureImage(renderer, data.second.first);
        SDL2pp::Texture textureFeathers(renderer, data.second.second);
        spritesMapping.emplace(data.first, SpriteManager(data.second.first, data.second.second,
renderer, textureImage, textureFeathers));
    }

    return spritesMapping;
}*/

void Game::handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown) {
    const auto& keyMapping = isKeyDown ? keyMappingPressed : keyMappingReleased;
    auto it = keyMapping.find(scancode);
    if (it != keyMapping.end()) {
        InputAction m_key = it->second;
        auto message = std::make_unique<GameMessage>(m_key);
        communicator.trysend(std::move(message));
    }

    if (twoPlayersLocal) {
        const auto& keyMappingPlayer2 = isKeyDown ? keyMappingPressedPlayer2 : keyMappingReleasedPlayer2;
        auto it2 = keyMappingPlayer2.find(scancode);
        if (it2 != keyMappingPlayer2.end()) {
            InputAction m_key = it2->second;
            auto message = std::make_unique<GameMessage>(m_key);
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


/*void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMappingPressed.find(scancode);
            if (it != keyMappingPressed.end()) {
                InputAction m_key = it->second;
                auto message = std::make_unique<GameMessage>(m_key);
                communicator.trysend(std::move(message));
            }

            if (twoPlayersLocal) {
                auto it2 = keyMappingPressedPlayer2.find(scancode);
                if (it2 != keyMappingPressedPlayer2.end()) {
                    InputAction m_key = it2->second;
                    auto message = std::make_unique<GameMessage>(m_key);
                    communicator.trysend(std::move(message));
                }
            }

        } else if (event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMappingReleased.find(scancode);
            if (it != keyMappingReleased.end()) {
                InputAction m_key = it->second;
                auto message = std::make_unique<GameMessage>(m_key);
                communicator.trysend(std::move(message));
            }

            if (twoPlayersLocal) {
                auto it2 = keyMappingReleasedPlayer2.find(scancode);
                if (it2 != keyMappingReleasedPlayer2.end()) {
                    InputAction m_key = it2->second;
                    auto message = std::make_unique<GameMessage>(m_key);
                    communicator.trysend(std::move(message));
                }
            }

        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}*/

Texture Game::startBackground() {
    SDL_Surface* rawBackgroundSurface = IMG_Load("../assets/background/background1.png");
    Surface backgroundSurface(rawBackgroundSurface);
    Texture backgroundTexture(renderer, backgroundSurface);

    showBackground(backgroundTexture);
    return backgroundTexture;
}

void Game::showBackground(Texture& backgroundTexture) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = -1000;
    dstRect.w = window_width * SCALE;
    dstRect.h = window_height * SCALE;

    // renderer.Clear();

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
