#include "stdafx.h"
#include "FinMultiMenu.h"


FinMultiMenu::FinMultiMenu()
{
}


FinMultiMenu::FinMultiMenuResult FinMultiMenu::Show(sf::RenderWindow& window, const int score, const int scoreAdversaire)
{

	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses-menu-fin.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//Recommencer menu item coordinates
	MenuItem recommencerButton;
	recommencerButton.rect.left = 121;
	recommencerButton.rect.top = 437;
	recommencerButton.rect.width = 309;
	recommencerButton.rect.height = 33;
	recommencerButton.action = Recommencer;

	//Histoire menu item coordinates
	MenuItem AutreButton;
	AutreButton.rect.left = 93;
	AutreButton.rect.top = 546;
	AutreButton.rect.width = 356;
	AutreButton.rect.height = 33;
	AutreButton.action = Autre;

	_menuItems.push_back(recommencerButton);
	_menuItems.push_back(AutreButton);

	//affichage score
	sf::Font font;
	font.loadFromFile("C:/Dev/JIN4/JIN4/font/DIOGENES.ttf");

	sf::Text scoreAff;
	scoreAff.setFont(font);
	scoreAff.setCharacterSize(90);
	scoreAff.setFillColor(sf::Color::White);
	scoreAff.setStyle(sf::Text::Regular);
	scoreAff.setPosition(240, 250);
	scoreAff.setString(std::to_string(score));

	//affichage winOrLose
	sf::Text winOrLose;
	winOrLose.setFont(font);
	winOrLose.setCharacterSize(30);
	winOrLose.setFillColor(sf::Color::White);
	winOrLose.setStyle(sf::Text::Regular);
	winOrLose.setPosition(240, 272);
	if (score > scoreAdversaire)
		winOrLose.setString(L"Gagné");
	if (score < scoreAdversaire)
		winOrLose.setString(L"Lol Perdu");

	window.draw(sprite);
	window.draw(scoreAff);
	window.draw(winOrLose);

	window.display();

	return GetMenuResponse(window);
}

FinMultiMenu::FinMultiMenuResult FinMultiMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;

		int gauche = menuItemRect.left;
		int droite = menuItemRect.left + menuItemRect.width;
		int haut = menuItemRect.top;
		int bas = menuItemRect.height + menuItemRect.top;

		if (bas > y && haut < y && droite > x && gauche < x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

FinMultiMenu::FinMultiMenuResult  FinMultiMenu::GetMenuResponse(sf::RenderWindow& window)
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
