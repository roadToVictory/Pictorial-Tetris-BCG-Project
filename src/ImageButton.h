#pragma once

#include "Button.h"

/**
 * @brief Klasa reprezentujaca przycisk bedacy obrazkiem.
 */
class ImageButton : public Button {
public:
    /**
     * @brief Konstruuje ImageButton.
     *
     * @param width Szerokos� w pikselach.
     * @param height Wysokos� w pikselach.
     * @param text Wyswietlany tekst.
     * @param size D�ugos� tekstu.
     * @param tx Textura .
    */
    ImageButton(float width, float height, const sf::String& text, unsigned int size, const sf::Texture& tx);

    /**
     * @brief Funkcja ustawiajaca wybranego obrazek jako zaznaczony.
     * @details Zmiana koloru t�a.
    */
    void selectThisButton() override;

    /**
     * @brief Funkcja ustawiajaca nie wybrany obrazek jako niezaznaczone.
     * @details Default'owy kolor t�a.
    */
    void unselectThisButton() override;
};
