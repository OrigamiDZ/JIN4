#include "stdafx.h"
#include "QuestionMenu.h"
#include <iostream>

QuestionMenu::QuestionMenu()
{
}


QuestionMenu::~QuestionMenu()
{
}

std::vector<pugi::xml_node> QuestionMenu::GoFetch(const std::string categorieString) {

	std::vector<pugi::xml_node> result;

	//choix aléatoire des questions
	std::vector<std::string> choix;
	for (int i = 0; i < 5; i++) {
		choix.push_back(std::to_string(rand() % nombreQuestionsTotalesParCatégorie + 1));
	}

	//chargement du fichier
	pugi::xml_document doc;

	doc.load_file("C:/Dev/JIN4/JIN4/Questions.xml");

	pugi::xml_node questions = doc.child("document");
	pugi::xml_node categorie = questions.child(categorieString.c_str());

	// recherche des nodes des questions
	for (pugi::xml_node question = categorie.first_child(); question; question = question.next_sibling())
	{
		for (pugi::xml_attribute attr = question.first_attribute(); attr; attr = attr.next_attribute())
		{
			std::string attrName = attr.name();
			std::string attrValue = attr.value();
			for (auto i : choix) {
				if (attrName.compare("id") && attrValue.compare(i))
				{
					result.push_back(question);
				}
			}
		}
	}

	return result;
}

sf::Text QuestionMenu::QuestionShow(std::vector<pugi::xml_node> node, const int numeroQuestion) {
	std::string question;

	//récupération de la question
	for (pugi::xml_attribute attr = node[numeroQuestion].first_attribute(); attr; attr = attr.next_attribute())
	{
		std::string attrName = attr.name();
		std::string attrValue = attr.value();

		if (attrName.compare("enonce")) {
			question = attrValue;
		}
	}

	//affichage de la question
	sf::Font font;
	font.loadFromFile("C:/Dev/JIN4/JIN4/font/DAYROM__.ttf");
	sf::Text questionAff;
	questionAff.setFont(font);
	questionAff.setCharacterSize(30);
	questionAff.setFillColor(sf::Color::White);
	questionAff.setStyle(sf::Text::Regular);
	questionAff.setString(question);

	return questionAff;
}

sf::Text* QuestionMenu::ReponseShow(std::vector<pugi::xml_node> node, const int numeroQuestion, const int numeroRep, sf::Text* pointeurBonneRep) {
	int i = 0;
	sf::Text* pointeurReponseAff = NULL;


	//récupération des réponses
	for (pugi::xml_node reponse = node[numeroQuestion].first_child(); reponse; reponse = reponse.next_sibling())
	{
		if (i == numeroRep) {
			for (pugi::xml_attribute attr = reponse.first_attribute(); attr; attr = attr.next_attribute())
			{
				std::string attrName = attr.name();
				std::string attrValue = attr.value();

				if (attrName.compare("valeur")) {
					sf::Font font;
					font.loadFromFile("C:/Dev/JIN4/JIN4/font/DAYROM__.ttf");
					(*pointeurReponseAff).setFont(font);
					(*pointeurReponseAff).setCharacterSize(25);
					(*pointeurReponseAff).setFillColor(sf::Color::White);
					(*pointeurReponseAff).setStyle(sf::Text::Regular);
					(*pointeurReponseAff).setString(attrValue);

				}
				if (attrName.compare("bool") && attrValue.compare("true")) {
					pointeurBonneRep = pointeurReponseAff;
				}
			}
		}
	}
	return pointeurReponseAff;
}


int QuestionMenu::RetourneScore(int actualScore, QuestionMenu::QuestionMenuResultRep answer, std::vector<sf::Text*> ensemble, sf::Text* pointeurBonneRep) {
	switch (answer)
	{
	case QuestionMenu::Reponse1:
		if (ensemble[0] == pointeurBonneRep) { actualScore++; }
		break;
	case QuestionMenu::Reponse2:
		if (ensemble[1] == pointeurBonneRep) { actualScore++; }
		break;
	case QuestionMenu::Reponse3:
		if (ensemble[2] == pointeurBonneRep) { actualScore++; }
		break;
	default:
		break;
	}
	return actualScore;
}


QuestionMenu::QuestionMenuResult QuestionMenu::Show(sf::RenderWindow& window, const std::string categorieString)
{
	sf::Text* pointeurBonneRep = NULL;

	sf::Text question;

	sf::Text* reponse1 = new sf::Text;
	sf::Text* reponse2 = new sf::Text;
	sf::Text* reponse3 = new sf::Text;

	std::vector<sf::Text*> ensemble = { reponse1, reponse2, reponse3 };

	int score = 0;

	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses-menu.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//PlaySolo menu item coordinates
	MenuItem reponse1Button;
	reponse1Button.rect.left = 190;
	reponse1Button.rect.top = 167;
	reponse1Button.rect.width = 178;
	reponse1Button.rect.height = 56;
	reponse1Button.action = Reponse1;

	//PlayMulti menu item coordinates
	MenuItem reponse2Button;
	reponse2Button.rect.left = 80;
	reponse2Button.rect.top = 345;
	reponse2Button.rect.width = 404;
	reponse2Button.rect.height = 51;
	reponse2Button.action = Reponse2;

	//Exit menu item coordinates
	MenuItem reponse3Button;
	reponse3Button.rect.left = 162;
	reponse3Button.rect.top = 520;
	reponse3Button.rect.width = 231;
	reponse3Button.rect.height = 51;
	reponse3Button.action = Reponse3;

	_menuItems.push_back(reponse1Button);
	_menuItems.push_back(reponse2Button);
	_menuItems.push_back(reponse3Button);


	std::vector<pugi::xml_node> node = GoFetch(categorieString);
	for (int tour = 0; tour < 5; tour++) {
		//affichage question 
		question = QuestionShow(node, tour);
		question.setPosition(10, 20);

		//affichage reponses
		for (int rep = 0; rep < 3; rep++) {
			ensemble[rep] = ReponseShow(node, tour, rep, pointeurBonneRep);
		}
		(*reponse1).setPosition(50, 100);
		(*reponse2).setPosition(50, 200);
		(*reponse3).setPosition(50, 300);


		window.draw(sprite);
		window.display();

		QuestionMenu::QuestionMenuResultRep answer = GetMenuResponse(window);
		while (GetMenuResponse(window) == Rate) {
			answer = GetMenuResponse(window);
		}

		score = RetourneScore(score, answer, ensemble, pointeurBonneRep);
	}
	std::cout << "Le score est " << score;
	return Exit;
}

QuestionMenu::QuestionMenuResultRep QuestionMenu::HandleClick(int x, int y)
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

	return Rate;
}


QuestionMenu::QuestionMenuResultRep  QuestionMenu::GetMenuResponse(sf::RenderWindow& window)
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
				return Quitter;
			}
		}
	}
}