#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include "NetworkLogic.h"
class FinMultiMenu
{
public:
	FinMultiMenu(Game *game);

	enum FinMultiMenuResult { Nothing, Recommencer, Autre, Exit };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		FinMultiMenuResult action;
	};

	FinMultiMenuResult Show(sf::RenderWindow& window, const int score, const int scoreAdversaire);

private:
	Game * mGame;
	FinMultiMenuResult GetMenuResponse(sf::RenderWindow& window);
	FinMultiMenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};