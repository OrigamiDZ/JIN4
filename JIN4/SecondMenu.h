#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
class SecondMenu
{
public:
	SecondMenu();
	~SecondMenu();
	enum SecondMenuResult { Back, Nothing, Exit, Litterature, Histoire, Chant, Musique, Tragedie, Comedie, Danse, Rhetorique, Astrologie};

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		SecondMenuResult action;
	};

	SecondMenuResult Show(sf::RenderWindow& window);

private:
	SecondMenuResult GetMenuResponse(sf::RenderWindow& window);
	SecondMenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

