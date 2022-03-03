#pragma once
#include "Game.h"
#include "Gauge.h"

Gauge::Gauge(std::string name, int posx, int posy, int sizex, int sizey, int padding) :SettingButtons(name, {}, posx, posy, sizex, sizey, padding){
	Game& view = Game::getInstanceOfGame();
	_bar = sf::RectangleShape(sf::Vector2f(400, 50));
	_bar.setFillColor(COLOR_DEFAULT);
	_bar.setPosition(sf::Vector2f(posx + _name.getLocalBounds().width + padding, posy));
	_gauge = sf::RectangleShape(sf::Vector2f(100, 50));
	_gauge.setFillColor(COLOR_SELECTED);
	_gauge.setPosition(sf::Vector2f(posx + _name.getLocalBounds().width + padding, posy));
	_min = posx + _name.getLocalBounds().width + 30;
	_selected = _min;
	_max = _selected + 300;
}

void Gauge::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(_high);
	target.draw(_name);
	target.draw(_bar);
	target.draw(_gauge);
}

void Gauge::selectSetting(int x) {}

void Gauge::selectRightSetting(){
	_selected += 10;
	if (_selected > _max)_selected = _max;
	_gauge.setPosition(sf::Vector2f(_selected, _posy));
}

void Gauge::selectLeftSetting(){
	_selected -= 10;
	if (_selected < _min)_selected = _min;
	_gauge.setPosition(sf::Vector2f(_selected, _posy));
}

int Gauge::getSelectedSetting() const{
	return (_selected - _min) / (_max - _min);
}
