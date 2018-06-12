#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include <pugixml.hpp>
#include "NetworkLogic.h"


class QuestionMultiMenu
{
public:
	QuestionMultiMenu(Game *game);
	enum QuestionMultiMenuResultRep { Rate, Reponse1, Reponse2, Reponse3, Quitter };
	sf::Text QuestionMultiShow(std::vector<pugi::xml_node> &node, const int numeroQuestion);

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		QuestionMultiMenuResultRep action;
	};

	int Show(sf::RenderWindow& window, const std::string categorieString);

private:
	Game * mGame;
	int NombreQuestions(const std::string categorieString);

	QuestionMultiMenuResultRep GetMenuResponse(sf::RenderWindow& window);
	QuestionMultiMenuResultRep HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;

	int RetourneScore(int actualScore, QuestionMultiMenu::QuestionMultiMenuResultRep answer, std::vector<sf::Text*> ensemble, sf::Text* pointeurBonneRep);

};
