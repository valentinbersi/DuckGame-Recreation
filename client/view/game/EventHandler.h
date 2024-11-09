#pragma once

#include "Communicator.h"
#include "GameMessage.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "DuckData.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>
#include <memory>
#include <list>

class EventHandler {

public:
    EventHandler(SDL2pp::Window& window, int& window_width, int& window_height, bool& twoPlayersLocal, Communicator& communicator,
                 std::list<std::unique_ptr<DuckData>>& ducks, Camera& camera, bool& running);
    ~EventHandler() = default;

    void handleEvents();

private:
    void handleScreenEvents(SDL_Event& event, bool isKeyDown, SDL_Scancode& scancode);
    void handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown);
    void setFullscreen(bool fullscreen);
    bool isFullscreen();

    SDL2pp::Window& window;
    bool& twoPlayersLocal;
    Communicator& communicator;
    int& window_width;
    int& window_height;
    std::list<std::unique_ptr<DuckData>>& ducks;
    Camera& camera;
    bool& running;

    std::unordered_map<SDL_Scancode, bool> keyStates;
    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressed = {
        {SDL_SCANCODE_W, InputAction::UP_PRESSED},
        {SDL_SCANCODE_S, InputAction::DOWN_PRESSED},
        {SDL_SCANCODE_A, InputAction::LEFT_PRESSED},
        {SDL_SCANCODE_D, InputAction::RIGHT_PRESSED},
        {SDL_SCANCODE_E, InputAction::ACTION_PRESSED},
        {SDL_SCANCODE_SPACE, InputAction::JUMP_PRESSED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleased = {
        {SDL_SCANCODE_W, InputAction::UP_RELEASED},
        {SDL_SCANCODE_S, InputAction::DOWN_RELEASED},
        {SDL_SCANCODE_A, InputAction::LEFT_RELEASED},
        {SDL_SCANCODE_D, InputAction::RIGHT_RELEASED},
        {SDL_SCANCODE_E, InputAction::ACTION_RELEASED},
        {SDL_SCANCODE_SPACE, InputAction::JUMP_RELEASED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressedPlayer2 = {
        {SDL_SCANCODE_UP, InputAction::UP_PRESSED},
        {SDL_SCANCODE_DOWN, InputAction::DOWN_PRESSED},
        {SDL_SCANCODE_LEFT, InputAction::LEFT_PRESSED},
        {SDL_SCANCODE_RIGHT, InputAction::RIGHT_PRESSED},
        {SDL_SCANCODE_RCTRL, InputAction::ACTION_PRESSED},
        {SDL_SCANCODE_RSHIFT, InputAction::JUMP_PRESSED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleasedPlayer2 = {
        {SDL_SCANCODE_UP, InputAction::UP_RELEASED},
        {SDL_SCANCODE_DOWN, InputAction::DOWN_RELEASED},
        {SDL_SCANCODE_LEFT, InputAction::LEFT_RELEASED},
        {SDL_SCANCODE_RIGHT, InputAction::RIGHT_RELEASED},
        {SDL_SCANCODE_RCTRL, InputAction::ACTION_RELEASED},
        {SDL_SCANCODE_RSHIFT, InputAction::JUMP_RELEASED}
    };
};
