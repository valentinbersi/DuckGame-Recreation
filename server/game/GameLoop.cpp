#include "GameLoop.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define PREV_TICKS 0
#define FRAME_TICKS 1

double GameLoop::calculateDeltaTime() {
    const std::uint64_t frameTicks = SDL_GetTicks64();
    const std::uint64_t deltaTime = frameTicks - prevTicks;
    prevTicks = frameTicks;
    return static_cast<double>(deltaTime) / 100;
}

void GameLoop::retrieveCurrentFrameCommands() {
    currentFrameCommands = std::move(clientCommands.popAll());
}

void GameLoop::processCurrentFrameCommands() {
    while (!currentFrameCommands.empty()) {
        Command* currentCommand = currentFrameCommands.front();
        currentFrameCommands.pop();
        // currentCommand->execute(game);
    }
}

void GameLoop::broadcastGameStatus() {
    // GameStatus gameStatus = game.status();
    std::ranges::for_each(clientQueues, [/*&gameStatus*/](const auto& clientQueue) {
        clientQueue.lock()->try_push(/*gameStatus*/);
    });
}

GameLoop::GameLoop(): prevTicks(0) {}

void GameLoop::run() {
    prevTicks = SDL_GetTicks64();

    while (_keep_running) {
        double deltaTime = calculateDeltaTime();
        retrieveCurrentFrameCommands();
        processCurrentFrameCommands();
        // game.update(deltaTime);
    }
}

void GameLoop::addClient(std::uint16_t clientID,
                         std::weak_ptr<BlockingQueue<GameStatus>> clientQueue) {
    clientQueues.push_back(std::move(clientQueue));
    // game.addPlayer(clientID);
}