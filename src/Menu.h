#pragma once

#include "Level.h"
#include "Button.h"

/**
 * @brief Klasa reprezentuje widok MENU głownego programu.
 */
class Menu : public Level {
public:
    /**
     * @brief Konstruuje Menu
     */
    Menu();

    /**
     * @brief Metoda reaguje na event od gracza.
     *
     * @param event Zdarzenie od gracza.
     */
    void eventListener(sf::Event &event) override;

    /**
     * @brief Metoda aktualizuje stan.
     *
     * @param dtime Czas renderowania i przetwarzania poprzedniej klatki.
     */
    void updateCurrentStateOfCurrentGameLevel(float dtime) override;

    /**
    * @brief Metoda renderuje aktualny stan.
    */
    void renderCurrentStateOfCurrentGameLevel() override;

    /**
     * @brief Czy dźwiek jest wyciszony.
    */
    static bool isSoundMuted;

private:
    void selectNext();
    void selectPrevious();
    void enter();
    std::vector<Button> _buttons;
    int _selected=0;
    
};
