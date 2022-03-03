#pragma once

#include "Level.h"
#include "Button.h"
#include "SettingButtons.h"

/**
 * @brief Klasa reprezentuje stan bycia w konfiguracji gry.
 */
class Settings : public Level {
public:
    /**
     * @brief Konstruktor bezargumentowy obiektu Settings.
     */
    Settings();

    /**
     * @brief Metoda odpowiedzialna za rejstrownie zdarzen klawiatury.
     * @param event Zdarzenie klawiatury.
     */
    void eventListener(sf::Event &event) override;

    /**
     * @brief Metoda aktualizuje aktualny stan widoku menu.
     * @param dtime Czas renderowania poprzedniej klatki gry.
     */
    void updateCurrentStateOfCurrentGameLevel(float dtime) override;

    /**
     * @brief Metoda renderuje obecny stan okna gry.
     */
    void renderCurrentStateOfCurrentGameLevel() override;

private:
    void selectNextSettingOption();
    void selectPreviousSettingOption();
    void selectLeftSettingOption();
    void selectRightSettingOption();
    void enterAllSettings();

    std::vector<SettingButtons*> _options;
    int _selected = 0;
};
