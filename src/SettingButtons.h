#pragma once
#include <iostream>
#include <vector>

#include "SFML/System/String.hpp"
#include <SFML/Graphics/Text.hpp>
#include "SFML/Graphics/Drawable.hpp"

#include "Button.h"


/*
*	@brief Klasa reprezentuje zestaw przyciskow, uzywanych w projekcie to zaznaczenia odpowiednich ustawien.
*/
class SettingButtons: public sf::Drawable
{
	public:
		/**
		 * @brief 1. Konstruktor zestawu przyciskow.
		 *
		 * @param name Tekst wyswietlany przy zestawie przyciskow.
		 * @param posx Pozycja x w pikselach.
		 * @param posy Pozycja y w pikselach.
		 * @param sizex Szerokosæ pojedynczego przycisku.
		 * @param sizey Wysokosæ pojedynczego przycisku.
		 * @param padding Odstepy pomiedzy przyciskami w zestwie.
		 */
		SettingButtons(std::string name, int posx, int posy, int sizex, int sizey, int padding);
		/**
		 * @brief 2. Konstruktor zestwau przyciskow.
		 *
		 * @param name Tekst wyswietlany przy zestawie przyciskow.
		 * @param opt Wektor stringow przechowujacy nazwy przyciskow, ktore tworzymy.
		 * @param posx Pozycja x w pikselach.
		 * @param posy Pozycja y w pikselach.
		 * @param sizex Szerokosæ pojedynczego przycisku.
		 * @param sizey Wysokosæ pojedynczego przycisku.
		 * @param padding Odstepy pomiedzy przyciskami w zestwie.
		 */
		SettingButtons(std::string name,std::vector<std::string> opt, int posx, int posy, int sizex, int sizey, int padding);
		/**
		 * @brief Metoda pozwalajaca na zaznaczenie wybranego przycisku.
		 * @param Indeks elementu, ktory ma byæ zaznaczony.
		 */
		virtual void selectSetting(int x);
		/**
		 * @brief Metoda przesuwa zaznaczenie przycisku na nastepny od lewej.
		 */
		virtual void selectRightSetting();
		/**
		 * @brief Metoda przesuwa zaznaczenie przycisku na nastepny od prawej.
		 */
		virtual void selectLeftSetting();
		/**
		 * @brief Metoda zwracajaca indeks aktywnej opcji.
		 * @return Indeks aktywnej opcji.
		 */
		virtual int getSelectedSetting() const;
		/**
		 * @brief Metoda zaznaczajaca zestaw przyciskow jako aktywny.
		 */
		void highlightSelectedSetting();
		/**
		 * @brief Metoda zaznaczajaca zestaw przyciskow jako nieaktywny.
		 */
		void unhighlightSelectedSetting();
	protected:
		int _posx;
		int _posy;
		int _selected;
		sf::RectangleShape _high;
		sf::Text _name;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		std::vector<Button *> _options;
};

