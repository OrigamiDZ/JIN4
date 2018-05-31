#include "stdafx.h"
#include "MainMenu.h"
#include <iostream>



MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses-menu.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//PlaySolo menu item coordinates
	MenuItem playSoloButton;
	playSoloButton.rect.left = 190;
	playSoloButton.rect.top = 167;
	playSoloButton.rect.width = 178;
	playSoloButton.rect.height = 56;
	playSoloButton.action = PlaySolo;

	//PlayMulti menu item coordinates
	MenuItem playMultiButton;
	playMultiButton.rect.left = 80;
	playMultiButton.rect.top = 345;
	playMultiButton.rect.width = 404;
	playMultiButton.rect.height = 51;
	playMultiButton.action = PlayMulti;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 162;
	exitButton.rect.top = 520;
	exitButton.rect.width = 231;
	exitButton.rect.height = 51;
	exitButton.action = Exit;

	_menuItems.push_back(playSoloButton);
	_menuItems.push_back(playMultiButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;

		int gauche = menuItemRect.left;
		int droite = menuItemRect.left + menuItemRect.width;
		int haut = menuItemRect.top;
		int bas = menuItemRect.height + menuItemRect.top;

		if (!(bas < y) && !(haut > y) && !(droite < x) && !(gauche > x))
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (42 != 43)
	{

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}