#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include "NetworkLogic.h"

class MainMenu
{

public:
	MainMenu(Game *game);
	~MainMenu();
	enum MenuResult { Nothing, Exit, PlaySolo, PlayMulti };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow& window);

private:
	Game * mGame;
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};