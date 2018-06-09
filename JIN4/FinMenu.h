#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
class FinMenu
{
public:
	FinMenu();
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
	FinMenuResult GetMenuResponse(sf::RenderWindow& window);
	FinMenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

