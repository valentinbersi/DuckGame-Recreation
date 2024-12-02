
#include "CommandFactory.h"

#include "CheatCommand.h"
#include "InteractCommand.h"
#include "MovementCommand.h"
#include "NextRoundCommand.h"
#include "ShootCommand.h"

HashMap<InputAction, std::function<std::unique_ptr<Command>(PlayerID id)>> CommandFactory::factory{
        {InputAction::LEFT_PRESSED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::LEFT_PRESSED);
         }},
        {InputAction::RIGHT_PRESSED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::RIGHT_PRESSED);
         }},
        {InputAction::UP_PRESSED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::UP_PRESSED);
         }},
        {InputAction::DOWN_PRESSED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::DOWN_PRESSED);
         }},
        {InputAction::JUMP_PRESSED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::JUMP_PRESSED);
         }},
        {InputAction::LEFT_RELEASED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::LEFT_RELEASED);
         }},
        {InputAction::RIGHT_RELEASED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::RIGHT_RELEASED);
         }},
        {InputAction::UP_RELEASED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::UP_RELEASED);
         }},
        {InputAction::DOWN_RELEASED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::DOWN_RELEASED);
         }},
        {InputAction::JUMP_RELEASED,
         [](PlayerID id) {
             return std::make_unique<MovementCommand>(id, InputAction::JUMP_RELEASED);
         }},
        {InputAction::ACTION_PRESSED,
         [](PlayerID id) { return std::make_unique<InteractCommand>(id); }},

        {InputAction::ACTION_RELEASED,
         [](PlayerID id) { return std::make_unique<InteractCommand>(id); }},

        {InputAction::SHOOT_PRESSED,
         [](PlayerID id) {
             return std::make_unique<ShootCommand>(id, InputAction::SHOOT_PRESSED);
         }},
        {InputAction::SHOOT_RELEASED,
         [](PlayerID id) {
             return std::make_unique<ShootCommand>(id, InputAction::SHOOT_RELEASED);
         }},

        {InputAction::NEXT_ROUND,
         [](PlayerID id) { return std::make_unique<NextRoundCommand>(id); }},

        {InputAction::END_ROUND_CHEAT,
         [](PlayerID id) {
             return std::make_unique<CheatCommand>(id, InputAction::END_ROUND_CHEAT);
         }},

        {InputAction::END_GAME_CHEAT, [](PlayerID id) {
             return std::make_unique<CheatCommand>(id, InputAction::END_GAME_CHEAT);
         }}};

std::unique_ptr<Command> CommandFactory::createCommand(const InputAction input,
                                                       const PlayerID PlayerID) {
    const auto function = factory.find(input);
    if (function == factory.end())
        throw std::invalid_argument("Not valid");

    return function->second(PlayerID);
}
