#pragma once
#include "Game.h"
#include "SettingButtons.h"
#include "ImageButton.h"

SettingButtons::SettingButtons(std::string name,std::vector<std::string> opt, int posx, int posy, int sizex, int sizey, int padding) : _posx(posx), _posy(posy), _selected(-1)
{
	Game& view = Game::getInstanceOfGame();
	_name=sf::Text(name, view.getTextFont(), 40);
	_name.setFillColor(view.getColorOfText());
	_name.setPosition(_posx, _posy);
	_high = sf::RectangleShape(sf::Vector2f(0, 0));
	_high.setFillColor(view.getHighlightColor());
	_high.setPosition(sf::Vector2f(posx-20,posy-10));
	for (int i = 0; i < opt.size(); i++)
	{
		_options.push_back(new Button(sizex, sizey, opt[i]));
		_options[_options.size() - 1]->setPositionOfTheButton(_posx + _name.getLocalBounds().width +
			padding + i * (padding + sizex), _posy);
	}
}
SettingButtons::SettingButtons(std::string name, int posx, int posy, int sizex, int sizey, int padding) : _posx(posx), _posy(posy), _selected(-1)
{
	Game& view = Game::getInstanceOfGame();
	_name = sf::Text(name, view.getTextFont(), 40);
	_name.setFillColor(view.getColorOfText());
	_name.setPosition(_posx, _posy);
	_high = sf::RectangleShape(sf::Vector2f(0, 0));
	_high.setFillColor(view.getHighlightColor());
	_high.setPosition(sf::Vector2f(posx - 20, posy - 10));
	for (int i = 0; i < 4; i++)
	{
		_options.push_back(new ImageButton(sizex, sizey, "", 15, view.getTextureOfGivenImageNumber(i)));
		_options[_options.size()-1]->setPositionOfTheButton(_posx + _name.getLocalBounds().width +
			padding + i * (padding + sizex), _posy);
	}
}

void SettingButtons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_high);
	for (auto s : _options)
	{
		target.draw(*s);
	}
	target.draw(_name);
}

void SettingButtons::selectSetting(int x)
{
	_selected = x;
	_options[x]->selectThisButton();
}

void SettingButtons::selectRightSetting()
{
	_options[_selected]->unselectThisButton();
	_selected=(++_selected)%_options.size();
	_options[_selected]->selectThisButton();
}

void SettingButtons::selectLeftSetting()
{
	_options[_selected]->unselectThisButton();
	_selected--;
	if (_selected < 0)_selected = _options.size()-1;
	_options[_selected]->selectThisButton();
}

int SettingButtons::getSelectedSetting() const
{
	return _selected;
}

void SettingButtons::highlightSelectedSetting()
{
	_high.setSize(sf::Vector2f(100,40));
}

void SettingButtons::unhighlightSelectedSetting()
{
	_high.setSize(sf::Vector2f(0, 0));
}

