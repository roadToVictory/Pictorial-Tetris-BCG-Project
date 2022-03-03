#include "Game.h"
#include "Play.h"
#include "Settings.h"
#include "Menu.h"
#include "Gauge.h"

Settings::Settings() {
   Game &view = Game::getInstanceOfGame();
    const int width = view.getWidthOfGameWindow();
    const int height = view.getHeightOfGameWindow();

    _options.push_back(new SettingButtons("Picture", width / 2.f - 800, height*0.2, 300, 300, 40));
    _options.push_back(new SettingButtons("Blocks:", {"1", "4","9","16", "25", "36", "49", "64"}, width / 2.f - 500, height * 0.57, 60, 60, 25));
    _options.push_back(new Gauge("Speed:", width / 2.f - 320, height * 0.7, 250, 50, 30));
    _options.push_back(new  SettingButtons("", { "Start" }, width / 2.f - 125, height * 0.85, 250, 60, 25));
    _selected = 0;
    _options[0]->highlightSelectedSetting();
    _options[0]->selectSetting(0);
    _options[1]->selectSetting(0);
    _options[3]->selectSetting(0);
}

void Settings::eventListener(sf::Event &event) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                Game::getGameController().setNewGameLevel(std::make_unique<Menu>());
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                selectLeftSettingOption();
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                selectRightSettingOption();
                break;
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                selectPreviousSettingOption();
                break;
            case sf::Keyboard::S:case sf::Keyboard::Down:
                selectNextSettingOption();
                break;
            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                if(_selected==3)enterAllSettings();
                break;
            default:
                break;
        }
    }
}

void Settings::updateCurrentStateOfCurrentGameLevel(float dtime) {}

void Settings::renderCurrentStateOfCurrentGameLevel() {
    Game &view = Game::getInstanceOfGame();
    sf::RenderTarget &target = view.getRenderedWindow();
    target.clear(Game::getInstanceOfGame().getColorOfBackground());

    sf::Text title("Settings", view.getTextFont(), 40);
    title.setFillColor(view.getColorOfText());
    title.setPosition(
            (view.getWidthOfGameWindow() - title.getLocalBounds().width) / 2.f,
            view.getHeightOfGameWindow() * 0.1f);
    target.draw(title);

    for (auto field : _options)
        target.draw(*field);
}

void Settings::selectNextSettingOption() {
    _options[_selected]->unhighlightSelectedSetting();
    _selected++;
    if (_selected == _options.size())_selected--;
    _options[_selected]->highlightSelectedSetting();
    _isCurrentLevelUpdated = true;
}

void Settings::selectPreviousSettingOption() {
    _options[_selected]->unhighlightSelectedSetting();
    _selected--;
    if (_selected == - 1)_selected++;
    _options[_selected]->highlightSelectedSetting();
    _isCurrentLevelUpdated = true;
}

void Settings::selectLeftSettingOption() {
    _options[_selected]->selectLeftSetting();
    _isCurrentLevelUpdated = true;
}

void Settings::selectRightSettingOption() {
    _options[_selected]->selectRightSetting();
    _isCurrentLevelUpdated = true;
}

void Settings::enterAllSettings() {
    Config& config = Game::getConfig();
    Game& view = Game::getInstanceOfGame();
    view.selected=_options[0]->getSelectedSetting();
    config.setNumberOfBlocksPerPictureSide(_options[1]->getSelectedSetting() + 1);
    config.level = _options[2]->getSelectedSetting();
    Game::getGameController().setNewGameLevel(std::make_unique<Play>());
    
}
