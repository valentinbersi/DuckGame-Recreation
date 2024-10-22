#include "GameController.h"

#include <iostream>

GameController::~GameController() = default;

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::update(float delta) { std::cout << "The game is running" << std::endl; }

void GameController::updateInternal(float delta) {}