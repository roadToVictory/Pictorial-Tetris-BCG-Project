#pragma once

#include <memory>
#include <stack>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "Level.h"

/**
 * @brief Klasa reprezentuje kontroler stanow gry.
 * @details Klasa zarzadza przejsciami pomiedzy odpowiednimi widokami w grze.
 */
class GameController {
public:
    /**
     * @brief Metoda reagujaca na event od gracza.
     *
     * @param event Zdarzenie od gracza.
     */
    void eventListener(sf::Event &event);

    /**
     * @brief Metoda aktualizuje stan gry.
     *
     * @param time Czas renderowania i przetwarzania poprzedniej klatki.
     */
    void updateCurrentGameLevel(float time);

    /**
     * @brief Metoda renderuje aktualny widok.
     */
    void renderCurrentGameLevel();

    /**
     * @brief Metoda zamyka poprzednie widoki gry i ustawia nowy.
     *
     * @param state Nowy stan do ustawienia.
     */
    void setNewGameLevel(std::unique_ptr<Level> state);

private:
    std::unique_ptr<Level> _currentLevel;
};
