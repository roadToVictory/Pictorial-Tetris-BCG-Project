#include "Level.h"
#include "Game.h"
#include "Menu.h"
#include "GameOver.h"


GameOver::GameOver() {
    if(Menu::isSoundMuted)
        Game::getInstanceOfGame().playWinSoundWithVolumeOf(50);
    Config& config = Game::getConfig();
    _result = 100 * (config.level + 1) * config.getsetNumberOfBlocksPerPictureSide() - Game::getInstanceOfGame().gameTime;
}

void GameOver::eventListener(sf::Event &event) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        if ( event.key.code == sf::Keyboard::Enter) {
            Game::getInstanceOfGame().playWinSoundWithVolumeOf(0);
            Game::getGameController().setNewGameLevel(std::make_unique<Menu>());
        }
    }
}

void GameOver::updateCurrentStateOfCurrentGameLevel(float) {
    Game::getInstanceOfGame().gameTime = 0.0;
}

void GameOver::renderCurrentStateOfCurrentGameLevel() {
    Game &view = Game::getInstanceOfGame();
    view.setVolumeOfSound(0);
    sf::RenderTarget &target = view.getRenderedWindow();
    target.clear(Game::getInstanceOfGame().getColorOfBackground());

    sf::Text message(std::string("Result: ") +
                     std::to_string(_result) + "\n" +
                     "Press ENTER to continue", view.getTextFont(), 65);
    message.setFillColor(view.getColorOfText());
    message.setPosition(
            (view.getWidthOfGameWindow() - message.getLocalBounds().width) / 25.f,
            (view.getHeightOfGameWindow() - message.getLocalBounds().height) / 50.f);

    sf::Sprite endGameSprite;
    endGameSprite = view.transformTextureToSpriteWithResizing(view.getTextureOfGivenImageNumber(), view.getWidthOfGameWindow() * 0.35f, view.getWidthOfGameWindow() * 0.35f);
    endGameSprite.setPosition(Game::getInstanceOfGame().getWidthOfGameWindow()/3.f,Game::getInstanceOfGame().getWidthOfGameWindow()/6.5f);

    target.draw(endGameSprite);
    target.draw(message);
}

