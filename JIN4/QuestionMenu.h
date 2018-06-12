#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include <pugixml.hpp>
#include "NetworkLogic.h"

class QuestionMenu
{
public:
	QuestionMenu(Game *game);
	~QuestionMenu();
	enum QuestionMenuResultRep { Rate, Reponse1, Reponse2, Reponse3, Quitter };
	sf::Text QuestionShow(std::vector<pugi::xml_node> &node, const int numeroQuestion);
	sf::Text* ReponseShow(std::vector<pugi::xml_node> &node, const int numeroQuestion, const int numeroRep, sf::Text* pointeurBonneRep);

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		QuestionMenuResultRep action;
	};

	int Show(sf::RenderWindow& window, const std::string categorieString);

private:
	Game * mGame;
	int NombreQuestions(const std::string categorieString);

	QuestionMenuResultRep GetMenuResponse(sf::RenderWindow& window);
	QuestionMenuResultRep HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
	
	int RetourneScore(int actualScore, QuestionMenu::QuestionMenuResultRep answer, std::vector<sf::Text*> ensemble, sf::Text* pointeurBonneRep);
	
};
