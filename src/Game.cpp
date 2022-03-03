#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Game.h"

const std::string Game::TITLE = "Picture Tetris";
int Game::selected = 0;

Game::Game() {
    int height = sf::VideoMode().getDesktopMode().height * 0.93;
    int width = sf::VideoMode().getDesktopMode().width;
    _desktop = sf::VideoMode(width, height);
    _window = std::make_unique<sf::RenderWindow>(_desktop, Game::TITLE);
    _window->setFramerateLimit(60);
    _window->setPosition(sf::Vector2i(-8,0));

    if (!_font.loadFromFile("data/Orbitron-VariableFont_wght.ttf"))
        throw std::runtime_error("cannot load font");

    for (unsigned int i = 0; i < IMAGES_COUNT; ++i) {
        loadImageFromFile(i);
    }
    transformImagesToTextures();

}

Game &Game::getInstanceOfGame() {
    static Game game;
    return game;
}

Config &Game::getConfig() {
    return Game::getInstanceOfGame()._config;
}

GameController &Game::getGameController() {
    return Game::getInstanceOfGame()._gameController;
}

sf::RenderWindow& Game::getRenderedWindow() {
    return *_window;
}

sf::Font& Game::getTextFont() {
    return _font;
}

void Game::loadImageFromFile(unsigned int idx) {
    _img[idx].loadFromFile("data/images/" + std::to_string(idx) + ".jpg");
}
sf::Texture& Game::getTextureOfGivenImageNumber(int n) {
    return _textures[n];
}

void Game::transformImagesToTextures() {
    for (int i = 0; i < 4; i++) {
        if (!_textures[i].loadFromImage(_img[i]))
            throw std::runtime_error("Image loading ERROR");
    }
}

sf::Sprite Game::transformTextureToSpriteWithResizing(sf::Texture& texture, float width, float height) {
    float target = width / height;
    float current = static_cast<float>(texture.getSize().x) / texture.getSize().y;
    sf::Sprite sprite(texture);

    if (current > target) {
        float scale = height / texture.getSize().y;
        sprite.setTextureRect(sf::IntRect((texture.getSize().x - texture.getSize().y * target) / 2, 0, texture.getSize().y * target,texture.getSize().y));
        sprite.setScale(scale, scale);
    }
    else {
        float scale = width / texture.getSize().x;
        sprite.setTextureRect(sf::IntRect(0, (texture.getSize().y - texture.getSize().x * 1 / target) / 2.f, texture.getSize().x, texture.getSize().x * 1 / target));
        sprite.setScale(scale, scale);
    }

    return sprite;
}

unsigned int Game::getHeightOfGameWindow() const {
    return _desktop.height;
}

unsigned int Game::getWidthOfGameWindow() const {
    return _desktop.width;
}

const sf::Color& Game::getColorOfBackground() const {
    return COLOR_BACKGROUND;
}

const sf::Color& Game::getColorOfText() const {
    return COLOR_TEXT;
}

const sf::Color& Game::getHighlightColor() const
{
    return HIGHLIGHT_COLOR;
}

void Game::setVolumeOfSound(int val)
{
    _bMusic.setVolume(val);
}

void Game::playWinSoundWithVolumeOf(int val)
{
    if (!val) {
        _winMusic.stop();
    }
    else {
        _winMusic.setVolume(val);
        _winMusic.setLoop(true);
        _winMusic.play();
    }
}

void Game::runProgram() {
    srand((time(0)));
    _bMusic.openFromFile("data/sound.wav");
    _winMusic.openFromFile("data/win.wav");
    _bMusic.setVolume(15);
    _bMusic.setLoop(true);
    _bMusic.play();

    _gameController.setNewGameLevel(std::make_unique<Menu>());
    sf::Clock clock;
    clock.restart();
    while ((*this).getRenderedWindow().isOpen()) {
        eventListener();
        _gameController.updateCurrentGameLevel(clock.restart().asSeconds());
        _gameController.renderCurrentGameLevel();
        (*this).getRenderedWindow().display();
    }
}

void Game::eventListener() {
    sf::Event event;
    while ((*this).getRenderedWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            (*this).getRenderedWindow().close();
        _gameController.eventListener(event);
    }
}