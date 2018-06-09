#include "stdafx.h"
#include "Game.h"
#include "EcranAcceuil.h"
#include "MainMenu.h"
#include "SecondMenu.h"
#include "QuestionMenu.h"
#include "FinMenu.h"


std::string subject;
bool solo;

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(562, 700, 32), "Les 1001 Muses");
	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::ShowingSecondMenu:
	{
		ShowSecondMenu();
		break;
	}
	case Game::PlayingSolo:
	{
		ShowQuestionMenu();
		break;
	}
	case Game::PlayingMulti:
	{
		sf::Event currentEvent;
		while (_mainWindow.pollEvent(currentEvent))
		{
			_mainWindow.clear(sf::Color(255, 255, 255));
			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
			}
		}
		break;
	}
	}

}

void Game::ShowSplashScreen()
{
	EcranAcceuil splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::PlaySolo:
		_gameState = Game::ShowingSecondMenu;
		solo = true;
		break;
	case MainMenu::PlayMulti:
		_gameState = Game::ShowingSecondMenu;
		solo = false;
		break;
	}
}

void Game::ShowSecondMenu()
{
	SecondMenu secondMenu;
	SecondMenu::SecondMenuResult result = secondMenu.Show(_mainWindow);
	switch (result)
	{
	case SecondMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case SecondMenu::Back:
		_gameState = Game::ShowingMenu;
		break;
	case SecondMenu::Histoire:
		subject = "histoire";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Comedie:
		subject = "comedie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Litterature:
		subject = "litterature";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Chant:
		subject = "chant";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Musique:
		subject = "musique";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Tragedie:
		subject = "tragedie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Astrologie:
		subject = "astrologie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Rhetorique:
		subject = "rhetorique";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	case SecondMenu::Danse:
		subject = "danse";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) { _gameState = Game::PlayingMulti; }
		break;
	}
}

void Game::ShowQuestionMenu()
{
	QuestionMenu questionMenu;
	int score = questionMenu.Show(_mainWindow, subject);
	FinMenu finMenu;
	FinMenu::FinMenuResult result = finMenu.Show(_mainWindow, score);
	switch (result)
	{
	case FinMenu::Autre:
		_gameState = Game::ShowingSecondMenu;
		break;
	case FinMenu::Recommencer:
		ShowQuestionMenu();
		break;
	case FinMenu::Exit:
		_gameState = Game::Exiting;
		break;


	}
}



