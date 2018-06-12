#include "stdafx.h"
#include "QuestionMultiMenu.h"
#include <iostream>
#include "Game.h"


QuestionMultiMenu::QuestionMultiMenu(Game *game) :
	mGame(game){
}

int QuestionMultiMenu::NombreQuestions(const std::string categorieString)
{
	int nombreQuestionsTotalesParCat�gorie = 0;

	//chargement du fichier
	pugi::xml_document doc;

	doc.load_file("C:/Dev/JIN4/JIN4/Questions.xml");

	pugi::xml_node questions = doc.child("document");
	pugi::xml_node categorie = questions.child(categorieString.c_str());

	// recherche des nodes des questions

	for (pugi::xml_node street = categorie.child("question"); street; street = street.next_sibling("question"))
	{
		nombreQuestionsTotalesParCat�gorie++;
	}
	return nombreQuestionsTotalesParCat�gorie;
}

sf::Text QuestionMultiMenu::QuestionMultiShow(std::vector<pugi::xml_node> &node, const int numeroQuestion) {
	std::string question;
	pugi::xml_node questionNode = node[numeroQuestion];


	pugi::xml_attribute question1attr1 = (node[0]).first_attribute();


	//r�cup�ration de la question
	for (pugi::xml_attribute attr = questionNode.first_attribute(); attr; attr = attr.next_attribute())
	{
		std::string attrName = attr.name();
		std::string attrValue = attr.value();

		if (attrName == "enonce") {
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


int QuestionMultiMenu::RetourneScore(int actualScore, QuestionMultiMenu::QuestionMultiMenuResultRep answer, std::vector<sf::Text*> ensemble, sf::Text* pointeurBonneRep) {
	switch (answer)
	{
	case QuestionMultiMenu::Reponse1:
		if (ensemble[0] == pointeurBonneRep) { actualScore++; }
		break;
	case QuestionMultiMenu::Reponse2:
		if (ensemble[1] == pointeurBonneRep) { actualScore++; }
		break;
	case QuestionMultiMenu::Reponse3:
		if (ensemble[2] == pointeurBonneRep) { actualScore++; }
		break;
	default:
		break;
	}
	return actualScore;
}


int QuestionMultiMenu::Show(sf::RenderWindow& window, const std::string categorieString)
{
	sf::Text* pointeurBonneRep = NULL;

	sf::Text questionAff;

	sf::Text* reponse1 = new sf::Text;
	sf::Text* reponse2 = new sf::Text;
	sf::Text* reponse3 = new sf::Text;

	std::vector<sf::Text*> ensemble = { reponse1, reponse2, reponse3 };

	int score = 0;

	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("c:/Dev/JIN4/JIN4/images/the_muses-menu-question.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//PlaySolo menu item coordinates
	MenuItem reponse1Button;
	reponse1Button.rect.left = 112;
	reponse1Button.rect.top = 213;
	reponse1Button.rect.width = 333;
	reponse1Button.rect.height = 93;
	reponse1Button.action = Reponse1;

	//PlayMulti menu item coordinates
	MenuItem reponse2Button;
	reponse2Button.rect.left = 112;
	reponse2Button.rect.top = 351;
	reponse2Button.rect.width = 333;
	reponse2Button.rect.height = 93;
	reponse2Button.action = Reponse2;

	//Exit menu item coordinates
	MenuItem reponse3Button;
	reponse3Button.rect.left = 112;
	reponse3Button.rect.top = 492;
	reponse3Button.rect.width = 333;
	reponse3Button.rect.height = 93;
	reponse3Button.action = Reponse3;

	_menuItems.push_back(reponse1Button);
	_menuItems.push_back(reponse2Button);
	_menuItems.push_back(reponse3Button);

	//determination du nombre de questions possible
	int nombreQuestionsTotalesParCat�gorie = NombreQuestions(categorieString);

	// GoFetch
	std::vector<pugi::xml_node> nodes;

	//choix al�atoire des questions
	std::vector<std::string> choix;


	if (nombreQuestionsTotalesParCat�gorie < 5) {
		for (int i = 0; i < 5; i++) {
			choix.push_back(std::to_string(rand() % nombreQuestionsTotalesParCat�gorie + 1));
		}
	}
	else {
		choix.push_back(std::to_string(rand() % nombreQuestionsTotalesParCat�gorie + 1));

		while (choix.size() != 5) {
			(mGame->mNetworkLogic).service();

			int pris = 0;
			std::string aleatoir = std::to_string(rand() % nombreQuestionsTotalesParCat�gorie + 1);
			for (auto i : choix)
				if (i != aleatoir) {
					pris++;
				}
			if (pris == choix.size()) {
				choix.push_back(aleatoir);
			}
		}
	}


	//chargement font
	sf::Font font;
	font.loadFromFile("C:/Dev/JIN4/JIN4/font/DIOGENES.ttf");

	//chargement du fichier
	pugi::xml_document doc;

	doc.load_file("C:/Dev/JIN4/JIN4/Questions.xml");

	pugi::xml_node questions = doc.child("document");
	pugi::xml_node categorie = questions.child(categorieString.c_str());

	// recherche des nodes des questions
	for (auto i : choix) {
		for (pugi::xml_node question = categorie.first_child(); question; question = question.next_sibling())
		{
			for (pugi::xml_attribute attr = question.first_attribute(); attr; attr = attr.next_attribute())
			{
				std::string attrName = attr.name();
				std::string attrValue = attr.value();

				if (attrName == "id" && attrValue == i)
				{
					nodes.push_back(question);
				}
			}
		}
	}

	//Tours
	for (int tour = 0; tour < 5; tour++) {
		//affichage question 

		std::string question;
		pugi::xml_node questionNode = nodes[tour];


		pugi::xml_attribute question1attr1 = (nodes[0]).first_attribute();


		//r�cup�ration de la question
		for (pugi::xml_attribute attr = questionNode.first_attribute(); attr; attr = attr.next_attribute())
		{
			std::string attrName = attr.name();
			std::string attrValue = attr.value();

			if (attrName == "enonce") {
				question = attrValue;
			}
		}

		//affichage de la question

		sf::Text questionAff;
		questionAff.setFont(font);
		questionAff.setCharacterSize(20);
		questionAff.setFillColor(sf::Color::Black);
		questionAff.setStyle(sf::Text::Regular);
		questionAff.setPosition(158, 39);
		questionAff.setString(question);

		//on fait le tour des caract�res du sf::Text
		for (int i = 0; i < int(questionAff.getString().getSize()); i++)
		{
			//Si le caract�re d�passe la boundingbox d�finit et que le caract�re n'est pas �gal � un retour � la ligne
			if ((questionAff.findCharacterPos(i).x >(155 + 246)) && (questionAff.getString()[i] != '\n'))
			{
				//On va chercher le dernier caract�re espace afin de faire des retour � la ligne par mot et non par caract�re
				while (questionAff.getString()[i] != ' ')--i;
				//On ajoute le caract�re de retour � la ligne en remplacent l'espace entre les deux mots par \n
				sf::String str1 = questionAff.getString().toWideString().substr(0, i);
				str1 += "\n";
				str1 += questionAff.getString().toWideString().substr(i + 1);
				questionAff.setString(str1);
			}
		}



		//affichage reponses
		int rep = 0;

		//r�cup�ration des r�ponses
		for (pugi::xml_node reponse = nodes[tour].first_child(); reponse; reponse = reponse.next_sibling())
		{
			for (pugi::xml_attribute attr = reponse.first_attribute(); attr; attr = attr.next_attribute())
			{
				std::string attrName = attr.name();
				std::string attrValue = attr.value();

				if (attrName == "valeur") {
					(*ensemble[rep]).setFont(font);
					(*ensemble[rep]).setCharacterSize(25);
					(*ensemble[rep]).setFillColor(sf::Color::Black);
					(*ensemble[rep]).setStyle(sf::Text::Regular);
					(*ensemble[rep]).setString(attrValue);

				}
				if ((attrName == "bool") && (attrValue == "true")) {
					pointeurBonneRep = ensemble[rep];
				}
			}
			rep++;
		}


		window.draw(sprite);

		(*reponse1).setPosition(187, 241);
		(*reponse2).setPosition(187, 378);
		(*reponse3).setPosition(187, 515);

		window.draw(questionAff);

		window.draw(*reponse1);
		window.draw(*reponse2);
		window.draw(*reponse3);

		window.display();

		QuestionMultiMenu::QuestionMultiMenuResultRep answer = GetMenuResponse(window);
		while (answer == Rate) {
			(mGame->mNetworkLogic).service();
			answer = GetMenuResponse(window);
		}

		score = RetourneScore(score, answer, ensemble, pointeurBonneRep);
	}
	std::cout << "Le score est " << score;
	return score;
}

QuestionMultiMenu::QuestionMultiMenuResultRep QuestionMultiMenu::HandleClick(int x, int y)
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


QuestionMultiMenu::QuestionMultiMenuResultRep  QuestionMultiMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (42 != 43)
	{

		while (window.pollEvent(menuEvent))
		{
			(mGame->mNetworkLogic).service();
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