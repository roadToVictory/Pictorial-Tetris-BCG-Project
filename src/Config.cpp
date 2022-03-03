#include "Game.h"
#include "Config.h"

void Config::setNumberOfBlocksPerPictureSide(unsigned int amount) {
     _blocks = amount;
}

unsigned int Config::getsetNumberOfBlocksPerPictureSide() const {
    return _blocks;
}

double Config::getSpeedOfFallingBlocks() const {
    return _speed * (level + 0.5) * Game::getInstanceOfGame().getHeightOfGameWindow() / 6.0;
}
