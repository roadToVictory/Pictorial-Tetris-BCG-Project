#pragma once

#include <memory>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "GameController.h"
#include "Config.h"
#include "Game.h"

/**
 * @brief Centralna klasa w ktorej toczy sie całe działanie programu.
 * @details Klasa jest singletonem.
 */
class Game {
public:
    /**
     * @brief Metoda zwraca instancje obiektu Game.
     *
     * @return Referencja do Game.
     */
    static Game& getInstanceOfGame();

    /**
     * @brief Metoda zwraca nadane ustawienia gry.
     *
     * @return Referencja do obiektu Config.
     */
    static Config& getConfig();

    /**
     * @brief Metoda zwraca kontroler stanow gry.
     *
     * @return Referencja do GameController.
     */
    static GameController& getGameController();

    /**
    * @brief Metoda zwraca okno stworzone przy pomocy SFML.
    * 
    * @return Referencja do klasy RenderWindow (SFML class).
    */
    sf::RenderWindow& getRenderedWindow();

    /**
    * @brief Metoda zwraca czcionke wykorzystywana w grze.
    * @return Referencja do Font (SFML class).
    */
    sf::Font& getTextFont();

    /**
     * @brief Metoda zwraca kolor tła.
     * @return Referencja do kolor tła (SFML class).
     */
    const sf::Color& getColorOfBackground() const;

    /**
     * @brief Metoda zwraca kolor tekstu wykorzystywanego w grze.
     * @return Referencja do koloru napisow (SFML class).
    */
    const sf::Color& getColorOfText() const;

    /**
    * @brief Metoda zwraca kolor podswietlanej opcji.
    * @return Referencja do koloru podswietlenia (SFML class).
   */
    const sf::Color& getHighlightColor() const;

    /**
     * @brief Metoda wczytujaca dany obrazek z pliku.
     * @details Obrazki sa przechowywane w katalogu data. Ich nazwa to numer indeksu, ktory beda zajmować w tablicy
     *
     * @param Dodatnia wartosć reprezentujaca indeks obrazka
     */
    void loadImageFromFile(unsigned int idx);

    /**
     * @brief Metoda redukuje wczytane obrazki na tekstury.
     * @details Metoda robi to z wszystkimi wczytanymi obrazkami.
     *
     */
    void transformImagesToTextures();

    /**
     * @brief Metoda zamieniajaca texture na sprite o zadanych wymiarach.
     *
     * @param texture Tekstura wejsciowa.
     * @param width Wyjsciowa szerokosć tekstury wyrazona w pikselach.
     * @param height Wyjsciowa wysokosć tekstury wyrazona w pikselach.
     * @return Obiekt Sprite na podstawie wejsciowej texture.
     */
    sf::Sprite transformTextureToSpriteWithResizing(sf::Texture& texture, float width, float height);

    /**
     * @brief Metoda stała zwracajaca szerokosć okna gry.
     *
     * @return Szerokosć okna wyrazona w dodatniej liczbie pikseli.
     */
    unsigned int getWidthOfGameWindow() const;

    /**
     * @brief Metoda stała zwracajaca wysokosć okna gry.
     *
     * @return Wysokosć okna wyrazona w dodatniej liczbie pikseli.
     */
    unsigned int getHeightOfGameWindow() const;

    /**
     * @brief Zwraca texture obrazka wczytanego do pamieci o wybranym indeksie.
     * @details Domyslny numer indeksu to ten ktory, ktory obrazek zostal wybrany.
     * 
     * @param int Indeks tablicy zawierajacej textury.
     * @return Referencja do Tekstury (SFML class)
     */
    sf::Texture& getTextureOfGivenImageNumber(int n = selected);

    /**
     * @brief Metoda inicjujca całe działanie programu.
     */
    void runProgram();

    /**
    * @brief Metoda sterujaca głosnoscia muzyki w grze.
    * @param Wartosć dzwieku w wartosciach całkowitych z przedziału 0-100.
    */
    void setVolumeOfSound(int val);

    /**
    * @brief Uruchomienie dźwieku przy zwyciestwie gry.
    * @param Wartosć dzwieku w wartosciach calkowitych z przedzialu 0-100.
    */
    void playWinSoundWithVolumeOf(int val);

    /**
    * @brief Zmienna statyczna przechowujaca liczbe obrazkow.
    */
    static const unsigned int IMAGES_COUNT = 4;

    /**
     * @brief Statyczny string przechowujacy tytuł gry.
     */
    static const std::string TITLE;

    /**
    * @brief Zmienna przechowujaca czas pojedynczej gry.
    */
    float gameTime = 0;

    /**
    * @brief Zmienna statyczna przechowujaca numer wybranego obrazka.
    */
    static int selected;
private:
    Game();
    Game(const Game &game) = delete;
    void operator=(const Game &game) = delete;
    void eventListener();

    const sf::Color COLOR_BACKGROUND{ 255, 222, 194 };
    const sf::Color COLOR_TEXT{ 10, 90, 255 };
    const sf::Color HIGHLIGHT_COLOR{100,180,220};
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Texture _texture;
    sf::Music _bMusic;
    sf::Music _winMusic;
    sf::Image _img[IMAGES_COUNT];
    sf::Texture _textures[IMAGES_COUNT];

    sf::Font _font;
    sf::VideoMode _desktop;

    Config _config;
    GameController _gameController;
    
};