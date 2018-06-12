#include "stdafx.h"
#include "SecondMenu.h"


SecondMenu::SecondMenu()
{
}


SecondMenu::~SecondMenu()
{
}

SecondMenu::SecondMenuResult SecondMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses-menu-second.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//Litterature menu item coordinates
	MenuItem litteratureButton;
	litteratureButton.rect.left = 158;
	litteratureButton.rect.top = 76;
	litteratureButton.rect.width = 243;
	litteratureButton.rect.height = 33;
	litteratureButton.action = Litterature;

	//Histoire menu item coordinates
	MenuItem histoireButton;
	histoireButton.rect.left = 189;
	histoireButton.rect.top = 136;
	histoireButton.rect.width = 184;
	histoireButton.rect.height = 33;
	histoireButton.action = Histoire;

	//Chant menu item coordinates
	MenuItem chantButton;
	chantButton.rect.left = 206;
	chantButton.rect.top = 196;
	chantButton.rect.width = 140;
	chantButton.rect.height = 33;
	chantButton.action = Chant;

	//Musique menu item coordinates
	MenuItem musiqueButton;
	musiqueButton.rect.left = 188;
	musiqueButton.rect.top = 258;
	musiqueButton.rect.width = 179;
	musiqueButton.rect.height = 36;
	musiqueButton.action = Musique;

	//Tragedie menu item coordinates
	MenuItem tragedieButton;
	tragedieButton.rect.left = 179;
	tragedieButton.rect.top = 317;
	tragedieButton.rect.width = 193;
	tragedieButton.rect.height = 33;
	tragedieButton.action = Tragedie;

	//Comedie menu item coordinates
	MenuItem comedieButton;
	comedieButton.rect.left = 185;
	comedieButton.rect.top = 376;
	comedieButton.rect.width = 183;
	comedieButton.rect.height = 33;
	comedieButton.action = Comedie;

	//Danse menu item coordinates
	MenuItem danseButton;
	danseButton.rect.left = 212;
	danseButton.rect.top = 436;
	danseButton.rect.width = 127;
	danseButton.rect.height = 33;
	danseButton.action = Danse;

	//Rhetorique menu item coordinates
	MenuItem rhetoriqueButton;
	rhetoriqueButton.rect.left = 149;
	rhetoriqueButton.rect.top = 496;
	rhetoriqueButton.rect.width = 254;
	rhetoriqueButton.rect.height = 38;
	rhetoriqueButton.action = Rhetorique;

	//Astrologie menu item coordinates
	MenuItem astrologieButton;
	astrologieButton.rect.left = 150;
	astrologieButton.rect.top = 555;
	astrologieButton.rect.width = 248;
	astrologieButton.rect.height = 33;
	astrologieButton.action = Astrologie;

	//Back menu item coordinates
	MenuItem backButton;
	backButton.rect.left = 222;
	backButton.rect.top = 618;
	backButton.rect.width = 120;
	backButton.rect.height = 26;
	backButton.action = Back;

	_menuItems.push_back(litteratureButton);
	_menuItems.push_back(histoireButton);
	_menuItems.push_back(chantButton);
	_menuItems.push_back(musiqueButton);
	_menuItems.push_back(tragedieButton);
	_menuItems.push_back(comedieButton);
	_menuItems.push_back(danseButton);
	_menuItems.push_back(rhetoriqueButton);
	_menuItems.push_back(astrologieButton);
	_menuItems.push_back(backButton);


	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

SecondMenu::SecondMenuResult SecondMenu::HandleClick(int x, int y)
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

SecondMenu::SecondMenuResult  SecondMenu::GetMenuResponse(sf::RenderWindow& window)
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
