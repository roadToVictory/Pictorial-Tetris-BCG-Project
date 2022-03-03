#pragma once

/**
 * @brief Klasa reprezentuje konfiguracje gry.
 */
class Config {
public:
    /**
     * @brief Metoda ustawia liczbe klockow na bok obrazka.
     *
     * @param amount Liczba klockow na bok.
     */
    void setNumberOfBlocksPerPictureSide(unsigned int amount);

    /**
     * @brief Metoda zwraca liczbe klockow na bok.
     *
     * @return Liczba klockow na bok.
     */
    unsigned int getsetNumberOfBlocksPerPictureSide() const;

    /**
     * @brief Metoda zwraca ustawiana predkosc spadania blokow.
     * @details Gdy nie zostanie ustawiona predkosc blokow przez uzytkownika, by default ustawiona jest najnizsza mozliwa predkosc do wyboru.
     *
     * @return Szybkosć spadanie klockow
     */
    double getSpeedOfFallingBlocks() const;

    /**
     * @brief Aktualny poziom trudnosci gry.
     */
    int level = 0;
private:
    const float _speed = 1.5;
    unsigned int _blocks = 1;
};



