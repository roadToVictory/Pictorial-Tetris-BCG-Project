#pragma once
#include "SFML/Graphics.hpp"

/**
 * @brief Reprezentacja abstrakcyjnego widoku gry.
 */
class Level {
public:
    /**
     * @brief Domyslny konstruktor obiektu stanu abstrakcyjnego.
     */
    Level() = default;

    /**
     * @brief Wirtualny destruktor stanu abstrakcyjnego.
     */
    virtual ~Level() {}

    /**
     * @brief Czysto abstrakcyjna metoda reagujaca na event od gracza.
     *
     * @param event Zdarzenie od gracza.
     */
    virtual void eventListener(sf::Event &event) = 0;

    /**
     * @brief Metoda aktualizuje stan. Czysto abstrakcyjna.
     *
     * @param dtime Czas renderowania i przetwarzania poprzedniej klatki.
     */
    virtual void updateCurrentStateOfCurrentGameLevel(float dtime) = 0;

    /**
     * @brief Renderuje aktualny stan. Czysto abstrakcyjna metoda.
     */
    virtual void renderCurrentStateOfCurrentGameLevel() = 0;

protected:
    /**
     * Informacja czy stan zostal zaktualizowany.
     */
    bool _isCurrentLevelUpdated = true;
};
