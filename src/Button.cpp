#include <SFML/System/String.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.h"
#include "Button.h"

const sf::Color Button::DEFAULT_COLOR{ 73, 215, 245 };
const sf::Color Button::SELECTED_COLOR{40, 146, 168};
const sf::Color Button::DEFAULT_TXT_COLOR{ 255, 255, 255 };
const sf::Color Button::SELECTED_TXT_COLOR{0, 0, 0};

const unsigned int Button::TEXT_SIZE = 28;

Button::Button(float width, float height, const sf::String &text, unsigned int size)
        : sf::RectangleShape(sf::Vector2f(width, height)),
          _text(text, Game::getInstanceOfGame().getTextFont(), size) {
    this->setFillColor(DEFAULT_COLOR);
    this->_text.setFillColor(DEFAULT_TXT_COLOR);
    setStringForText(text);
}

void Button::selectThisButton() {
    _selected = true;
    this->setFillColor(SELECTED_COLOR);
    _text.setFillColor(SELECTED_TXT_COLOR);
}

void Button::unselectThisButton() {
    _selected = false;
    setFillColor(DEFAULT_COLOR);
    _text.setFillColor(DEFAULT_TXT_COLOR);
}

void Button::setStringForText(const sf::String &string) {
    _text.setString(string);
    for (unsigned int i = 0; i < _text.getCharacterSize() / 2 && !isTextPositionSet() ;i++)
        _text.setCharacterSize(_text.getCharacterSize());
}

bool Button::isTextPositionSet() {
    float width = (getLocalBounds().width - _text.getLocalBounds().width) / 2.f;
    if (width < 0) return false;
    float height = (getLocalBounds().height - _text.getLocalBounds().height) / 2.f - _text.getCharacterSize() * 0.25f;
    _text.setPosition(getPosition() + sf::Vector2f(width, height));
    return true;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(static_cast<sf::RectangleShape>(*this), states);
    target.draw(_text, states);
}

void Button::setPositionOfTheButton(float x, float y) {
    Transformable::setPosition(x, y);
    isTextPositionSet();
}
