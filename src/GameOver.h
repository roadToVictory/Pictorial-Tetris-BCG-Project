#pragma once

#include "Level.h"

/**
 * @brief Klasa reprezentujaca koniec gry.
 * @brief Klasa pokazuje graczowi wynik jaki uzyskal podczas gry.
 */
class GameOver : public Level {
public:
    /**
     * @brief Konstruktor GameOver
     */
    GameOver();

    /**
     * @brief Metoda reaguje na event od gracza.
     *
     * @param event Zdarzenie od gracza.
     */
    void eventListener(sf::Event &event) override;

    /**
     * @brief Metoda aktualizuje widok gry.
     *
     * @param dtime Czas renderowania i przetwarzania poprzedniej klatki.
     */
    void updateCurrentStateOfCurrentGameLevel(float dtime)override;

    /**
     * @brief Metoda renderuje aktualny widok gry.
     */
    void renderCurrentStateOfCurrentGameLevel() override;

private:
    int _result;
};
