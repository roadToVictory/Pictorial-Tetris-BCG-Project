#pragma once
#include "SettingButtons.h"

/**
 * @brief Klasa reprezentuje slider.
 * @details Klasa reprezentuje slider uzywany do zmiany szybkosci spadania klockow.
 */
class Gauge : public SettingButtons
{
public:
	/**
	* @brief Konstruktor Gauge.
	*
    * @param name Opis slidera.
    * @param posx Pozycja slidera na osi OX.
    * @param posy Pozycja slidera na osi OY.
    * @param sizex Rozmiar w p≥aszczyünie OX.
	* @param sizey Rozmiar w p≥aszczyünie OY.
    * @param padding Rozmiar marginesu .
	*/
	Gauge(std::string name, int posx, int posy, int sizex, int sizey, int padding);


	/**
	* @brief Pusta metoda przeciazana, przez wymog hierarchii.
	* @param x 
	*/
	void selectSetting(int x) override;

	/**
	 * @brief Metoda realizujaca przesuwanie slidera w prawo.
	 * @details Przesuwa pozycje suwaka w prawo.
	*/
	void selectRightSetting() override;

	/**
	 * @brief Metoda realizujaca przesuwanie slidera w lewo.
	 * @details Przesuwa pozycje suwaka w lewo.
	*/
	void selectLeftSetting() override;

	/**
	 * @brief Metoda zwracajaca wybrana pozycje slidera.
	 *
	 * @return Wybrana pozycje slidera.
	*/
	int getSelectedSetting() const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int _max = 0;
	int _min = 0;
	const sf::Color COLOR_DEFAULT{ 73, 215, 245 };
	const sf::Color COLOR_SELECTED{ 40, 146, 168 };
	sf::RectangleShape _bar;
	sf::RectangleShape _gauge;
};


