#pragma once
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

/**
 * @brief Reprezentacja przyciskow w MENU, oraz w poczatkowych ustawieniach gry.
 */
class Button : public sf::RectangleShape {
public:
    /**
     * @brief Konstruuje przycisk o zadanych parametrach rozmiaru i tekstu.
     *
     * @param width Szerokosć w pikselach
     * @param height Wysokosć w pikselach
     * @param text Wyswietlany tekst, domyslnie pusty
     * @param size Długosć tekstu
     */
    Button(float width, float height, const sf::String &text = "", unsigned int size = TEXT_SIZE);


    /**
     * @brief Metoda ustawiajaca wybrany przycisk jako zaznaczony.
     * @details Zmienia sie kolor przycisku, dla poprawy UI/UX.
     */
    virtual void selectThisButton();

    /**
     * @brief Metoda odznaczajaca przycisk.
     * @details Metoda zmienia kolor tla przycisku na defaultowy, co daje efekt odznaczenia obrazka, poprawa UI/UX.
     */
    virtual void unselectThisButton();

    /**
     * @brief Metoda ustawiajaca tekst pokazywany na przycisku.
     * @details Metoda odpowiada za automatyczne dopasowanie fontu do buttona, oraz za zapobieganie wychodzenia tekstu poza obszar przycisku.
     *
     * @param string Tekst, ktory nalezy ustawić
     */
    void setStringForText(const sf::String &string);

    /**
     * @brief Metoda zmieniajaca połozenie przycisku w oknie.
     *
     * @param x Wspołrzedna osi OX w px
     * @param y Wspołrzedna osi OY w px
     */
    void setPositionOfTheButton(float x, float y);

protected:

    /*
    *  @brief Sprawdza czy pozycja przycisku zostala ustawiona.
    */
    bool isTextPositionSet();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Text _text;

    static const sf::Color DEFAULT_COLOR;
    static const sf::Color SELECTED_COLOR;
    static const sf::Color SELECTED_TXT_COLOR;
    static const sf::Color DEFAULT_TXT_COLOR;
    static const unsigned int TEXT_SIZE;
    bool _selected = false ;
    
};
