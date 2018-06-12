#include "stdafx.h"
#include "Game.h"
#include "EcranAcceuil.h"
#include "MainMenu.h"
#include "SecondMenu.h"
#include "QuestionMenu.h"
#include "QuestionMultiMenu.h"
#include "FinMenu.h"
#include "windows.h"
#include <iostream>
#include "FinMultiMenu.h"


static const ExitGames::Common::JString appID = L"774e251d-8a12-444d-88c0-96130444aba0"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static ExitGames::Common::JString gameName = L"TP_SIR";


bool solo;

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

Game::Game()
	: mNetworkLogic(appID, appVersion, this)

{
	mNetworkLogic.connect();
	mNetworkLogic.joinOrCreateRoom(gameName);
	mPlayerNumber = mNetworkLogic.getNumber();
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
	mNetworkLogic.disconnect();
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
	mNetworkLogic.service();
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
		ShowQuestionMenu();
		break;
	}
	}

}

void Game::ShowSplashScreen()
{
	EcranAcceuil splashScreen(this);
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu(this);
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
		solo = false;
		mNetworkLogic.service();
		if (mPlayerNumber == 1) {
			while (!twoPlayers) {
				Sleep(1500);
				mNetworkLogic.service();
			}
			std::cout << "Out de la boucle !" << std::endl;
			ShowSecondMenu();
		}
		else {
			std::cout << "Le player 2 est arrivé";
			subject = "";
			while (subject == "") {
				Sleep(1500);
				mNetworkLogic.service();
			}
			std::cout << "Le player 2 est sorti";
			_gameState = Game::PlayingMulti;
		}
		break;
	}
}

void Game::ShowSecondMenu()
{
	SecondMenu secondMenu(this);
	std::cout << "Dans SecondMenu !" << std::endl;

	SecondMenu::SecondMenuResult result = secondMenu.Show(_mainWindow);
	std::cout << "Second Menu Out !" << std::endl;

	switch (result)
	{
	case SecondMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case SecondMenu::Back:
		_gameState = Game::ShowingMenu;
		break;
	case SecondMenu::Litterature:
		subject = "litterature";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(1);
		}
		break;
	case SecondMenu::Histoire:
		subject = "histoire";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			mNetworkLogic.sendSubject(2);
			_gameState = Game::PlayingMulti; 
		}
		break;
	case SecondMenu::Chant:
		subject = "chant";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(3);
		}
		break;
	case SecondMenu::Musique:
		subject = "musique";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(4);
		}
		break;
	case SecondMenu::Tragedie:
		subject = "tragedie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(5);
		}
		break;
	case SecondMenu::Comedie:
		subject = "comedie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(6);
		}
		break;
	case SecondMenu::Danse:
		subject = "danse";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(7);
		}
		break;
	case SecondMenu::Rhetorique:
		subject = "rhetorique";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(8);
		}
		break;
	case SecondMenu::Astrologie:
		subject = "astrologie";
		if (solo) { _gameState = Game::PlayingSolo; }
		else if (!(solo)) {
			_gameState = Game::PlayingMulti;
			mNetworkLogic.sendSubject(9);
		}
		break;
	}
}

void Game::ShowQuestionMenu()
{
	QuestionMenu questionMenu(this);
	int score = questionMenu.Show(_mainWindow, subject);
	FinMenu finMenu(this);
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

void Game::ShowQuestionMultiMenu()
{
	QuestionMultiMenu questionMultiMenu(this);
	int score = questionMultiMenu.Show(_mainWindow, subject);
	if (mPlayerNumber == 1) {
		mNetworkLogic.sendScore(score);
	}
	else {
		while (scoreAdversaire == 0) {
			mNetworkLogic.service();
		}
	}
	FinMultiMenu finMultiMenu(this);
	FinMultiMenu::FinMultiMenuResult result = finMultiMenu.Show(_mainWindow, score, scoreAdversaire);
	switch (result)
	{
	case FinMenu::Autre:
		_gameState = Game::ShowingMenu;
		break;
	case FinMenu::Recommencer:
		solo = false;
		mNetworkLogic.service();
		if (mPlayerNumber == 1) {
			while (!twoPlayers) {
				Sleep(1500);
				mNetworkLogic.service();
			}
			std::cout << "Out de la boucle !" << std::endl;
			ShowSecondMenu();
		}
		else {
			std::cout << "Le player 2 est arrivé";
			subject = "";
			while (subject == "") {
				Sleep(1500);
				mNetworkLogic.service();
			}
			std::cout << "Le player 2 est sorti";
			_gameState = Game::PlayingMulti;
		}
		break;
	case FinMenu::Exit:
		_gameState = Game::Exiting;
		break;
	}
}