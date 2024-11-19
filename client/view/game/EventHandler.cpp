#include "EventHandler.h"

EventHandler::EventHandler(SDL2pp::Window& window, int& window_width, int& window_height,
                           bool& twoPlayersLocal, Communicator& communicator,
                           std::list<std::unique_ptr<DuckData>>& ducks, Camera& camera,
                           bool& running):
        window(window),
        twoPlayersLocal(twoPlayersLocal),
        communicator(communicator),
        window_width(window_width),
        window_height(window_height),
        ducks(ducks),
        camera(camera),
        running(running) {}

void EventHandler::handleEvents() {
    SDL_Event event;
    bool scaleChanged = false;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            SDL_Scancode scancode = event.key.keysym.scancode;
            bool isKeyDown = event.type == SDL_KEYDOWN;
            handleKeyEvent(scancode, isKeyDown);
            handleScreenEvents(event, isKeyDown, scancode);

        } else if (event.type == SDL_QUIT) {
            running = false;

        } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            scaleChanged = true;
        }
    }

    if (scaleChanged)
        camera.update(ducks);
}

void EventHandler::handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown) {
    keyStates[scancode] = isKeyDown;
    const auto& keyMapping = isKeyDown ? keyMappingPressed : keyMappingReleased;
    auto it = keyMapping.find(scancode);
    if (it != keyMapping.end()) {
        InputAction m_key = it->second;
        auto message = std::make_unique<GameMessage>(m_key, 1);
        communicator.trysend(std::move(message));
    }

    if (twoPlayersLocal) {
        const auto& keyMappingPlayer2 =
                isKeyDown ? keyMappingPressedPlayer2 : keyMappingReleasedPlayer2;
        auto it2 = keyMappingPlayer2.find(scancode);
        if (it2 != keyMappingPlayer2.end()) {
            InputAction m_key = it2->second;
            auto message = std::make_unique<GameMessage>(m_key, 2);
            communicator.trysend(std::move(message));
        }
    }
}

void EventHandler::handleScreenEvents(SDL_Event& event, bool isKeyDown, SDL_Scancode& scancode) {
    if (isKeyDown && scancode == SDL_SCANCODE_F11) {
        isFullscreen() ? setFullscreen(false) : setFullscreen(true);
    } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_GetWindowSize(window.Get(), &window_width, &window_height);
    }
}

bool EventHandler::isFullscreen() {
    Uint32 flags = SDL_GetWindowFlags(window.Get());
    return (flags & SDL_WINDOW_FULLSCREEN) || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void EventHandler::setFullscreen(bool fullscreen) {
    if (fullscreen) {
        SDL_SetWindowFullscreen(window.Get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(window.Get(), 0);
    }
    SDL_GetWindowSize(window.Get(), &window_width, &window_height);
}
