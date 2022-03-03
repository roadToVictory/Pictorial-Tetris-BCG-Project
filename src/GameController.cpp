#include "Game.h"
#include "Level.h"
#include "GameController.h"

void GameController::eventListener(sf::Event &event) {
    _currentLevel->eventListener(event);
}

void GameController::updateCurrentGameLevel(float time) {
    _currentLevel->updateCurrentStateOfCurrentGameLevel(time);
}

void GameController::renderCurrentGameLevel() {
    _currentLevel->renderCurrentStateOfCurrentGameLevel();
}


void GameController::setNewGameLevel(std::unique_ptr<Level> state) {
    _currentLevel = std::move(state);
}
