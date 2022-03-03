#include "ImageButton.h"

ImageButton::ImageButton(float width, float height, const sf::String& text,unsigned int size, const sf::Texture& tx): Button(width,height,text)
{
    setStringForText(text);
    this->setTexture(&tx);
    setFillColor(sf::Color::White);
}

void ImageButton::selectThisButton() {
    _selected = true;
    this->setFillColor(SELECTED_COLOR);
}

void ImageButton::unselectThisButton() {
    _selected = false;
    setFillColor(sf::Color::White);
}