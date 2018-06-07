#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include "Questions.h"


class QuestionMenu
{
public:
	QuestionMenu();
	~QuestionMenu();
	enum QuestionMenuResultRep { Rate, Reponse1, Reponse2, Reponse3, Quitter };
	enum QuestionMenuResult { Nothing, Question1, Question2, Question3, Question4, Question5, Exit };
	sf::Text QuestionShow(std::vector<pugi::xml_node> node, const int numeroQuestion);
	sf::Text* ReponseShow(std::vector<pugi::xml_node> node, const int numeroQuestion, const int numeroRep, sf::Text* pointeurBonneRep);
	std::vector<pugi::xml_node> GoFetch(const std::string categorieString);

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		QuestionMenuResultRep action;
	};

	QuestionMenuResult Show(sf::RenderWindow& window, const std::string categorieString);

private:
	QuestionMenuResultRep GetMenuResponse(sf::RenderWindow& window);
	QuestionMenuResultRep HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
	int nombreQuestionsTotalesParCatégorie = 1;
	int RetourneScore(int actualScore, QuestionMenu::QuestionMenuResultRep answer, std::vector<sf::Text*> ensemble, sf::Text* pointeurBonneRep);
	
};
