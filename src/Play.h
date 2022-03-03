#pragma once

#include <stack>
#include <vector>
#include <array>
#include "Level.h"
#include "Game.h"

/**
 * @brief Klasa reprezentuje glowny widok gry odpowiadajacy za sama gre.
 */
class Play : public Level {
public:
    /**
     * @brief Konstruktor Gry.
     */
    Play();

    /**
     * @brief Metoda odpowiedzialna za rejstrownie zdarzen klawiatury.
     * @param event Zdarzenie klawiatury.
     */
    void eventListener(sf::Event &event) override;

    /**
     * @brief Metoda mktualizuje stan gry.
     * @param dt Czas renderowania poprzedniej klatki gry.
     */
    void updateCurrentStateOfCurrentGameLevel(float dt) override;

    /**
     * @brief Metoda renderuje aktualny stan gry.
     */
    void renderCurrentStateOfCurrentGameLevel() override;

private:
    void placeGrayPicture(Game& view, const sf::Image &greyBackgroundImage);
    void placePictureToBeAssembled(Game& view);
    void cut();
    sf::Color convertColorToGrayscale(const sf::Color &color);
    sf::Sprite getFragmentOfPicture(int x, int y);
    void rotateBlockToLeft();
    void rotateBlockToRight();

    float _leftBegin = Game::getInstanceOfGame().getWidthOfGameWindow() * 0.075f;
    float _topBegin = Game::getInstanceOfGame().getHeightOfGameWindow() * 0.30f;
    double _elementSiteLen;
    bool _doubleSpeed = false;

    sf::Image image  = Game::getInstanceOfGame().getTextureOfGivenImageNumber().copyToImage();
    sf::Texture _greyBackgroundTexture;
    sf::Texture _rightTexture;
    sf::Sprite _greyBackgroundSprite;
    sf::Sprite _rightSprite;
    sf::Sprite _current;

    std::vector<std::stack<sf::Sprite>> _unplaced;
    std::vector<int> _stackHeight;
    std::vector<sf::Sprite> _placed;

    bool _isCurrentPlaced = true;
    int _currentColumn;
    int _position;
    int _rotation = 0;
};
