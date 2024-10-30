#include "Game.hpp"

#define SCALE 2.5f

#define DEF_WINDOW_WIDTH 1040
#define DEF_WINDOW_HEIGHT 680

#define greySheet "../../assets/sprites/duck/greyDuck.png"
#define orangeSheet "../../assets/sprites/duck/orangeDuck.png"
#define whiteSheet "../../assets/sprites/duck/whiteDuck.png"
#define yellowSheet "../../assets/sprites/duck/yellowDuck.png"

#define greyFeathers "../../assets/sprites/duck/greyDuckFeathers.png"
#define orangeFeathers "../../assets/sprites/duck/orangeDuckFeathers.png"
#define whiteFeathers "../../assets/sprites/duck/whiteDuckFeathers.png"
#define yellowFeathers "../../assets/sprites/duck/yellowDuckFeathers.png"

// Here we should just declare the classes that are use in this file. But for now a NOLINT is fine.
using namespace SDL2pp;  // NOLINT(build/namespaces)

Game::Game(ActiveSocket&& skt):
        running(true),
        window_width(DEF_WINDOW_WIDTH),
        window_height(DEF_WINDOW_HEIGHT),
        communicator(std::move(skt)),
        window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
               window_height, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED) {}

void Game::init() {
    std::unordered_map<DuckID, SpriteManager> spritesMapping = createSpritesMapping();
    SDL sdl(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Texture backgroundTexture = startBackground();
    renderer.Present();

    while(running) {
        getSnapshot();           //handle everything sended by the gameloop
        //Vector2 center = centerOfDucks();

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


        // poner en algún lado una struct de players (ducks) y asociarles una ID


        /*
        handleEvents();       // handle user input
        renderer.Clear();
        showBackground(backgroundTexture);
        update(player1);             //update ducks
        //render();         render EVERYTHING again (outside players, that are being rendered in the
        player class) SDL_Delay(33);
        */
    }


    IMG_Quit();
}

void Game::getSnapshot() {
    GameStatus snapshot;
    std::optional<GameStatus> status =
            communicator.tryrecv();  // ES UN OPTIONAL. Debo chequear que el optional me de
                                     // gamestatus usando .value. Sino si es null ya está
    if (status.has_value()) {
        snapshot = std::move(status.value());
    } else
        return;

    // aca deberia conseguir los diversos duck data hasta que en el casteo dinamico me de nullptr
    // en ese caso no habrán más ducks y ya entraré a los objetos

    // acomodarme cosas en sublistas. sublistas de patos, de armas, de bloques, objetos... etc
    // al final hago clear a cada sublista y vuelvo a obtener una nueva snapshot
    // para esto puedo mover punteros para lo que necesito

    clearObjects();
    for (auto& gameObject: snapshot.gameObjects) {
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
    snapshot.gameObjects.clear();
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

    for (auto& duck : ducks) {
        coordsX += duck->position.x();
        coordsY += duck->position.y();
    }

    if (duckCount > 0) {
        coordsX /= static_cast<float>(duckCount);
        coordsY /= static_cast<float>(duckCount);
    }

    Vector2 result(coordsX, coordsY);
    return result;

    // dividirlo por el numero por el que se multiplicó (dicho por valen etc (preguntar numero exacto))
}

void Game::clearObjects() { ducks.clear(); }

std::unordered_map<DuckID, SpriteManager> Game::createSpritesMapping() {
    std::unordered_map<DuckID, SpriteManager> spritesMapping;

    // Create textures and add to the map
    Texture whiteTexture(renderer, whiteSheet);
    Texture whiteFeathersTexture(renderer, whiteFeathers);
    spritesMapping.emplace(DuckID::White,
                           SpriteManager(whiteSheet, whiteFeathers, renderer, whiteTexture,
                                         whiteFeathersTexture, window_width, window_height));

    Texture orangeTexture(renderer, orangeSheet);
    Texture orangeFeathersTexture(renderer, orangeFeathers);
    spritesMapping.emplace(DuckID::Orange,
                           SpriteManager(orangeSheet, orangeFeathers, renderer, orangeTexture,
                                         orangeFeathersTexture, window_width, window_height));

    Texture yellowTexture(renderer, yellowSheet);
    Texture yellowFeathersTexture(renderer, yellowFeathers);
    spritesMapping.emplace(DuckID::Yellow,
                           SpriteManager(yellowSheet, yellowFeathers, renderer, yellowTexture,
                                         yellowFeathersTexture, window_width, window_height));

    Texture greyTexture(renderer, greySheet);
    Texture greyFeathersTexture(renderer, greyFeathers);
    spritesMapping.emplace(DuckID::Grey,
                           SpriteManager(greySheet, greyFeathers, renderer, greyTexture,
                                         greyFeathersTexture, window_width, window_height));

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


void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMappingPressed.find(scancode);
            if (it != keyMappingPressed.end()) {
                InputAction m_key = it->second;
                GameMessage message(m_key);
                communicator.trysend(message);
            }

        } else if (event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            auto it = keyMappingReleased.find(scancode);
            if (it != keyMappingReleased.end()) {
                InputAction m_key = it->second;
                GameMessage message(m_key);
                communicator.trysend(message);
            }

            // MOUSE EVENTS ETC...? MULTIPLES TECLAS?

        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

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
