#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
#include "pugixml.hpp"


class Questions
{
public:
	Questions();
	~Questions();
	sf::Text QuestionShow(std::vector<pugi::xml_node> node, const std::string categorieString, const int numeroQuestion);
	sf::Text* ReponseShow(std::vector<pugi::xml_node> node, const std::string categorieString, const int numeroQuestion, const int numeroRep, sf::Text* pointeurBonneRep);
	std::vector<pugi::xml_node> GoFetch(const std::string categorieString);
	struct ReponsesStructure {
		std::vector<sf::Text> reponses;
		std::vector<bool> reponsesBool;
	};


private:
	int nombreQuestionsTotalesParCatégorie;
};

