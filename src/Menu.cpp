#include "Game.h"
#include <iostream>
#include "Menu.h"
#include "Settings.h"

Menu::Menu() {
    Game &view = Game::getInstanceOfGame();
    const int width = view.getWidthOfGameWindow();
    const int height = view.getHeightOfGameWindow();
    const int butt_width = 300;
    const int butt_heigh = 60;
    const int top_margin = height * 0.02f;

    int startHPos = (height - 3 * (butt_heigh + top_margin)) / 2;
    int startWPos = (width - butt_width) / 2;

    for (int i = 0; i < 3;++i) {
        _buttons.emplace_back(butt_width, butt_heigh);
        _buttons[i].setPositionOfTheButton(startWPos, startHPos);
        startHPos += butt_heigh + top_margin;
    }

    _buttons[0].setStringForText("START");
    _buttons[1].setStringForText("MUTE MUSIC");
    _buttons[2].setStringForText("EXIT");
    _buttons[0].selectThisButton();
}

void Menu::eventListener(sf::Event &event) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        switch (event.key.code) {

            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                selectPrevious();
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                selectNext();
                break;
            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                enter();
                break;
            case sf::Keyboard::Escape:
                Game::getInstanceOfGame().getRenderedWindow().close();
                break;
            default:
                break;
        }
    }
}

void Menu::updateCurrentStateOfCurrentGameLevel(float) {
    if (isSoundMuted) Game::getInstanceOfGame().setVolumeOfSound(15);
}

void Menu::renderCurrentStateOfCurrentGameLevel() {
    Game &view = Game::getInstanceOfGame();
    sf::RenderTarget &target = view.getRenderedWindow();
    target.clear(Game::getInstanceOfGame().getColorOfBackground());
    sf::Texture t;
    t.loadFromFile("data/images/city.png");
    sf::Sprite s(t);
    s.setScale(static_cast<float>(view.getWidthOfGameWindow())/1920, static_cast<float>(view.getHeightOfGameWindow()) / 1080);
    target.draw(s);
    sf::Text title(view.TITLE, view.getTextFont(), 80);
    title.setFillColor(view.getColorOfText());
    title.setPosition(
            (view.getWidthOfGameWindow() - title.getLocalBounds().width) / 2,
            view.getHeightOfGameWindow() * 0.1);
    target.draw(title);

    for (auto &button : _buttons)
        target.draw(button);

    sf::Text message(std::string(31, ' ') + "Controls:\n" + 
        std::string(17, ' ') + "LEFT/A  - move left\n" + 
        std::string(17, ' ') + "RIGHT/D  - move right\n" + 
        std::string(17, ' ') + "DOWN/S - speed up \n" + 
        std::string(18, ' ') + "UP/W - slow down\n" +
        std::string(25, ' ') + "Q, E - rotate\n" +
        std::string(21, ' ') + "ENTER - select\n" +
        std::string(20, ' ') + "ESC - back / exit \n\n", view.getTextFont(), 15);
    message.setFillColor(sf::Color::Black);
    message.setPosition(
        (view.getWidthOfGameWindow() - message.getLocalBounds().width) / 100.f,
        (view.getHeightOfGameWindow() - message.getLocalBounds().height) *0.08);

    target.draw(message);

    sf::Text contract(std::string(215, ' ') + "Created by:\n" + 
        std::string(207, ' ') + "Ryszard Borzych\n" + 
        std::string(207, ' ') + "Sebastian Konik\n" +
        std::string(207, ' ') + "Damian Koperstynski", view.getTextFont(), 18);
        contract.setFillColor(sf::Color::Black);
        contract.setPosition(view.getWidthOfGameWindow()*0.98 - contract.getLocalBounds().width,(view.getHeightOfGameWindow() - contract.getLocalBounds().height) * 0.08);
        int x = view.getWidthOfGameWindow() - contract.getLocalBounds().width;
    target.draw(contract);

}

void Menu::selectNext() {
    _buttons[_selected].unselectThisButton();
    _selected = (_selected + 1) % _buttons.size();
    _buttons[_selected].selectThisButton();
    _isCurrentLevelUpdated = true;
}

void Menu::selectPrevious() {
    _buttons[_selected].unselectThisButton();
    if (--_selected < 0) _selected += _buttons.size();
    _buttons[_selected].selectThisButton();
    _isCurrentLevelUpdated = true;
}

bool Menu::isSoundMuted = true;

void Menu::enter() {
    switch (_selected) {
        case 0:
            Game::getGameController().setNewGameLevel(std::make_unique<Settings>());
            break;
        case 1:
            if (isSoundMuted) {
                Game::getInstanceOfGame().setVolumeOfSound(0);
                isSoundMuted = false;
                break;
            }
            isSoundMuted = true;
            Game::getInstanceOfGame().setVolumeOfSound(15);
            break;
        case 2:
            Game::getInstanceOfGame().getRenderedWindow().close();
            break;
        default:
            break;
    }
}

