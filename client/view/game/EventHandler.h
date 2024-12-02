#pragma once

#include <list>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Communicator.h"
#include "DuckData.h"
#include "GameMessage.h"
#include "SpriteManager.h"

class EventHandler {

public:
    // Constructor
    EventHandler(SDL2pp::Window& window, int& window_width, int& window_height,
                 bool& twoPlayersLocal, Communicator& communicator, std::list<DuckData>& ducks,
                 Camera& camera, bool& running);

    // Destructor
    ~EventHandler() = default;

    // Keeps listening to KEYUP, KEYDOWN, QUIT and REZISED events of the screen.
    // After that, calls the specific handlers for each case after scanning the key.
    void handleEvents();

private:
    // Handles 'ScreenEvents', having in mid if the game is fullscreen or not.
    // Also, updates the window size variables after the change.
    void handleScreenEvents(const SDL_Event& event, bool isKeyDown, const SDL_Scancode& scancode);

    // Handles the key event, sending the message to the server using a GameMessage filled with an
    // InputAction. It works also with two players, sending the message to the server with the
    // player number.
    void handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown);

    bool isCheatActive(const std::vector<SDL_Scancode>& keys);


    // Returns if the game is fullscreen or not using SDL special flags.
    bool isFullscreen();

    // Sets the game to fullscreen if not activated (or viceversa).
    void setFullscreen(bool fullscreen);

    SDL2pp::Window& window;
    bool& twoPlayersLocal;
    Communicator& communicator;
    int& window_width;
    int& window_height;
    std::list<DuckData>& ducks;
    Camera& camera;
    bool& running;

    std::unordered_map<SDL_Scancode, bool> keyStates;

    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressed = {
            {SDL_SCANCODE_W, InputAction::UP_PRESSED},
            {SDL_SCANCODE_S, InputAction::DOWN_PRESSED},
            {SDL_SCANCODE_A, InputAction::LEFT_PRESSED},
            {SDL_SCANCODE_D, InputAction::RIGHT_PRESSED},
            {SDL_SCANCODE_E, InputAction::ACTION_PRESSED},
            {SDL_SCANCODE_SPACE, InputAction::JUMP_PRESSED},
            {SDL_SCANCODE_G, InputAction::SHOOT_PRESSED}};

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleased = {
            {SDL_SCANCODE_W, InputAction::UP_RELEASED},
            {SDL_SCANCODE_S, InputAction::DOWN_RELEASED},
            {SDL_SCANCODE_A, InputAction::LEFT_RELEASED},
            {SDL_SCANCODE_D, InputAction::RIGHT_RELEASED},
            {SDL_SCANCODE_SPACE, InputAction::JUMP_RELEASED},
            {SDL_SCANCODE_G, InputAction::SHOOT_RELEASED}};

    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressedPlayer2 = {
            {SDL_SCANCODE_UP, InputAction::UP_PRESSED},
            {SDL_SCANCODE_DOWN, InputAction::DOWN_PRESSED},
            {SDL_SCANCODE_LEFT, InputAction::LEFT_PRESSED},
            {SDL_SCANCODE_RIGHT, InputAction::RIGHT_PRESSED},
            {SDL_SCANCODE_PERIOD, InputAction::ACTION_PRESSED},
            {SDL_SCANCODE_COMMA, InputAction::JUMP_PRESSED},
            {SDL_SCANCODE_SLASH, InputAction::SHOOT_PRESSED}};

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleasedPlayer2 = {
            {SDL_SCANCODE_UP, InputAction::UP_RELEASED},
            {SDL_SCANCODE_DOWN, InputAction::DOWN_RELEASED},
            {SDL_SCANCODE_LEFT, InputAction::LEFT_RELEASED},
            {SDL_SCANCODE_RIGHT, InputAction::RIGHT_RELEASED},
            {SDL_SCANCODE_COMMA, InputAction::JUMP_RELEASED},
            {SDL_SCANCODE_SLASH, InputAction::SHOOT_RELEASED}};

    std::unordered_map<SDL_Scancode, InputAction> cheats = {
                {SDL_SCANCODE_1, InputAction::END_ROUND_CHEAT},
                {SDL_SCANCODE_2, InputAction::END_GAME_CHEAT},
                {SDL_SCANCODE_3, InputAction::AK47_CHEAT},
                {SDL_SCANCODE_4, InputAction::SHOTGUN_CHEAT},
                {SDL_SCANCODE_5, InputAction::MAGNUM_CHEAT},
                {SDL_SCANCODE_6, InputAction::COWBOYPISTOL_CHEAT},
                {SDL_SCANCODE_7, InputAction::DUELPISTOL},
                {SDL_SCANCODE_8, InputAction::SNIPER},
                {SDL_SCANCODE_9, InputAction::LASER_RIFLE},
                {SDL_SCANCODE_0, InputAction::PEWPEW},
                {SDL_SCANCODE_F1, InputAction::GRENADE},
                {SDL_SCANCODE_F2, InputAction::BANANA},
                {SDL_SCANCODE_F3, InputAction::ARMOR},
                {SDL_SCANCODE_F4, InputAction::HELMET},
                {SDL_SCANCODE_F5, InputAction::INFINITE_AMMO}};
};

