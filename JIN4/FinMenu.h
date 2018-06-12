#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "NetworkLogic.h"

#include <list>
class FinMenu
{
public:
	FinMenu(Game *game);
	~FinMenu();

	enum FinMenuResult { Nothing, Recommencer, Autre, Exit };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		FinMenuResult action;
	};

	FinMenuResult Show(sf::RenderWindow& window, const int score);

private:
	Game * mGame;
	FinMenuResult GetMenuResponse(sf::RenderWindow& window);
	FinMenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

